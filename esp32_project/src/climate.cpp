/*
    @file climate.hpp
    @author Andreas Weber
    @brief Implementation of climate class
*/

#include "climate.hpp"

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


/// @brief This function is the run method to calculate the cyclic update of the feature climate
/// @param void
void ClimateState::run(void)
{
    // If feature is not initialized or inactive do nothing
    if (!init_state || !feature_active)
        return;

    run_time++;

#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE
    targetTemperatureChange_ms++;

    // If animation is 
    if ( (   targetTemperatureIncrease_b
         && (targetTemperatureChange_ms > C_ANIMATION_TIME_CLIMATE_TARGET_HOT)
         ) 
     ||  (   targetTemperatureDecrease_b
         && (targetTemperatureChange_ms > C_ANIMATION_TIME_CLIMATE_TARGET_COLD)
         )
    )
    {
        targetTemperatureIncrease_b = false;
        targetTemperatureDecrease_b = false; 
    }
#endif

#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE
    currentTemperatureChange_ms++;

    // If animation is 
    if ( (   currentTemperatureIncrease_b
         && (currentTemperatureChange_ms > C_ANIMATION_TIME_CLIMATE_CURRENT_HOT)
         ) 
     ||  (   currentTemperatureDecrease_b
         && (currentTemperatureChange_ms > C_ANIMATION_TIME_CLIMATE_CURRENT_COLD)
         )
    )
    {
        currentTemperatureIncrease_b = false;
        currentTemperatureDecrease_b = false; 
    }
#endif
    return;
};
