/*
    @file climate.cpp
    @author Andreas Weber
    @brief Implementation of climate class
*/

#include "climate.hpp"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Target temperature
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE

/// @brief This function is used to update the local target temperature in case the CAN message was received
/// @param new_temp newly received target temperature for climate control
void ClimateState::updateTargetTemperature( int new_temp )
{
    // Update newly received value
    targetTemperature_last = targetTemperature_now;
    targetTemperature_now = new_temp;
    
    // Check if target value was received before
    if ( ( init_state ) 
        && targetTemperature_last != INT16_MAX
        && targetTemperature_now != INT16_MAX
    )
    {
        // If new temperature is above old temperature, set information for hot animation
        if ( targetTemperature_now > targetTemperature_last )
        {
            targetTemperatureChange_ms = 0u;
            targetTemperatureIncrease_b = true;
            targetTemperatureDecrease_b = false;
        }
        // If new temperature is below old temperature, start cold animation
        else if ( targetTemperature_now < targetTemperature_last )
        {
            targetTemperatureChange_ms = 0u;
            targetTemperatureIncrease_b = false;
            targetTemperatureDecrease_b = true;
        }
        else
        {
            // Nothing to do, since other functionality will be done in feature->run()
        }
    }
}

#endif // FEATURE_CLIMATE_TARGET_TEMPERATURE
            
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Current Temperature
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE

/// @brief This function is used to update the estimated current temperature in case the CAN message was received
/// @param new_temp newly received temperature estimation
void ClimateState::updateCurrentTemperature( int new_temp )
{
    // Update newly received value
    currentTemperature_last = currentTemperature_now;
    currentTemperature_now = new_temp;
    
    // Check if current value was received before
    if ( ( init_state ) 
        && currentTemperature_last != INT16_MAX
        && currentTemperature_now != INT16_MAX
    )
    {
        // If new temperature is above old temperature, set information for hot animation
        if ( currentTemperature_now > currentTemperature_last )
        {
            currentTemperatureChange_ms = 0u;
            currentTemperatureIncrease_b = true;
            currentTemperatureDecrease_b = false;
        }
        // If new temperature is below old temperature, start cold animation
        else if ( currentTemperature_now < currentTemperature_last )
        {
            currentTemperatureChange_ms = 0u;
            currentTemperatureIncrease_b = false;
            currentTemperatureDecrease_b = true;
        }
        else
        {
            // Nothing to do, since other functionality will be done in feature->run()
        }
    }
}

#endif // FEATURE_CLIMATE_CURRENT_TEMPERATURE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Climate States - run method
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief This function is the run method to calculate the cyclic update of the feature climate
/// @param void
enAnimation ClimateState::run(enAnimation currentActiveAnimation)
{
    enAnimation locAnimation = enAnimation::ANIMATION_NONE;

    // If feature is not initialized or inactive do nothing
    if ( !init_state ||  !feature_active )
    {
        // Climate feature is not active or initialized yet, return current active animation
        return currentActiveAnimation;
    }
    run_time+=CYCLE_TIME_FEATURE;

#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE
    targetTemperatureChange_ms++;

    // If target temperature increase is active 
    if ( targetTemperatureIncrease_b )
    {
        // If animation time is not already at max. animation time and also no higher priority animation of climate is active
        if ( ( targetTemperatureChange_ms <= C_ANIMATION_TIME_CLIMATE_TARGET_HOT ) 
          && ( locAnimation < ANIMATION_CLIMATE_TARGET_HOT ) )
        {
            locAnimation = ANIMATION_CLIMATE_TARGET_HOT;
        }
        else
        {
            // reset information about temp. increase
            targetTemperatureIncrease_b = false;

            // If current animation is target temperature hot, then reset
            if ( currentActiveAnimation == ANIMATION_CLIMATE_TARGET_HOT )
            {
                currentActiveAnimation = enAnimation::ANIMATION_NONE;
            }
        }
    }
    
    // If target temperature decrease is active 
    if ( targetTemperatureDecrease_b )
    {
        // If animation time is not already at max. animation time and also no higher priority animation of climate is active
        if ( ( targetTemperatureChange_ms <= C_ANIMATION_TIME_CLIMATE_TARGET_COLD ) 
          && ( locAnimation < ANIMATION_CLIMATE_TARGET_COLD ) )
        {
            locAnimation = ANIMATION_CLIMATE_TARGET_COLD;
        }
        else
        {
            // reset information about temp. decrease
            targetTemperatureDecrease_b = false;

            // If current animation is target temperature cold, then reset
            if ( currentActiveAnimation == ANIMATION_CLIMATE_TARGET_COLD )
            {
                currentActiveAnimation = enAnimation::ANIMATION_NONE;
            }
        }
    }
#endif

#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE
    currentTemperatureChange_ms++;

    // If current temperature increase is active
    if ( currentTemperatureIncrease_b )
    {
        // If animation time is not already at max. animation time and also no higher priority animation of climate is active
        if ( ( currentTemperatureChange_ms <= C_ANIMATION_TIME_CLIMATE_CURRENT_HOT ) 
          && ( locAnimation < ANIMATION_CLIMATE_CURRENT_HOT ) )
        {
            locAnimation = ANIMATION_CLIMATE_CURRENT_HOT;
        }
        else
        {
            // reset information about temp. increase
            currentTemperatureIncrease_b = false;

            // If current animation is current temperature hot, then reset
            if ( currentActiveAnimation == ANIMATION_CLIMATE_CURRENT_HOT )
            {
                currentActiveAnimation = enAnimation::ANIMATION_NONE;
            }
        }
    }

    // If current temperature decrease is active 
    if ( currentTemperatureDecrease_b )
    {
        // If animation time is not already at max. animation time and also no higher priority animation of climate is active
        if ( ( currentTemperatureChange_ms <= C_ANIMATION_TIME_CLIMATE_CURRENT_COLD ) 
          && ( locAnimation < ANIMATION_CLIMATE_CURRENT_COLD ) )
        {
            locAnimation = ANIMATION_CLIMATE_CURRENT_COLD;
        }
        else
        {
            // reset information about temp. decrease
            currentTemperatureDecrease_b = false;

            // If current animation is current temperature cold, then reset
            if ( currentActiveAnimation == ANIMATION_CLIMATE_CURRENT_COLD )
            {
                currentActiveAnimation = enAnimation::ANIMATION_NONE;
            }
        }
    }
#endif

    if (locAnimation >= currentActiveAnimation)
        return locAnimation;

    return currentActiveAnimation;
};
