/*
    @file lights.cpp
    @author Andreas Weber
    @brief Implementation of light state class
*/

#include "lights.hpp"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Turn indicator
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
void LightState::setLeftTurnIndicatorState(bool new_state)
{
    if (new_state == leftTurnIndicatorActive_b)
        return;

    // State is not equal to previous state
    leftTurnIndicatorActive_b = new_state;
    TurnIndicatorActive_ms = 0u;

    // If left turn indicator is active, right must be inactive
    if (new_state)
        rightTurnIndicatorActive_b = false;    
};

void LightState::setRightTurnIndicatorState(bool new_state)
{
    if (new_state == rightTurnIndicatorActive_b)
        return;

    // State is not equal to previous state
    rightTurnIndicatorActive_b = new_state;
    TurnIndicatorActive_ms = 0u;

    // If right turn indicator is active, left must be inactive
    if (new_state)
        leftTurnIndicatorActive_b = false;    
};
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Hazard indication
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_LIGHT_STATUS_HAZARD
void LightState::setHazardIndicatorState(bool new_state)
{
    if (new_state == hazardIndicatorActive_b)
        return;
    
    // State is not equal to previous state
    hazardIndicatorActive_b = new_state;
    hazardIndicatorActive_ms = 0u;

    // If hazard is active, turn indicator must be inactive
    if (new_state)
    {
#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
        setLeftTurnIndicatorState(false);
        setRightTurnIndicatorState(false);
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR
    }
};
#endif // FEATURE_LIGHT_STATUS_HAZARD

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  LowBeam State
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
void LightState::setLowBeamState(bool new_state)
{
    // If no state change
    if (new_state == lowBeamActivated_b)
        return;
    
    // State is not equal to previous state
    lowBeamActivated_b = new_state;
    lowBeamActivated_ms = 0u;

    // If lowbeam is active, highbeam indicator shall be inactive
    if (new_state)
    {
#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
        setHighBeamState(false);
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
    }
};
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  HighBeam State
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
void LightState::setHighBeamState(bool new_state)
{
    // If no state change
    if (new_state == highBeamActivated_b)
        return;
    
    // State is not equal to previous state
    highBeamActivated_b = new_state;
    highBeamActivated_ms = 0u;

    // If highbeam is active, lowbeam indicator shall be inactive
    if (new_state)
    {
#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
        setLowBeamState(false);
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
    }    
};
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Fog State
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef FEATURE_LIGHT_STATUS_FOG_FRONT
void LightState::setFogFrontLightState(bool new_state)
{
    // If no state change
    if (new_state == fogFrontLightActivated_b)
        return;
    
    // State is not equal to previous state
    fogFrontLightActivated_b = new_state;
    fogLightActivated_ms = 0u;
};
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT

#ifdef FEATURE_LIGHT_STATUS_FOG_REAR
void LightState::setFogRearLightState(bool new_state)
{
    // If no state change
    if (new_state == fogRearLightActivated_b)
        return;
    
    // State is not equal to previous state
    fogRearLightActivated_b = new_state;
    fogLightActivated_ms = 0u;
};
#endif // FEATURE_LIGHT_STATUS_FOG_REAR


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Light State - run method
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief This function is the run method to check if any light state shall activate an animation
/// @param currentActiveAnimation will be the current active animation
enAnimation LightState::run(enAnimation currentActiveAnimation)
{
    enAnimation locAnimation = enAnimation::ANIMATION_NONE;
    
    // If feature is not initialized or inactive do nothing
    if (!init_state || !feature_active)
    {
        // Light feature is not active or initialized yet, return current active animation
        return currentActiveAnimation;
    }
    run_time+=CYCLE_TIME_FEATURE;
    
#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
    // Call check status for right and left turn indication
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_TURN_RIGHT, &rightTurnIndicatorActive_b, &TurnIndicatorActive_ms, C_ANIMATION_TIME_LIGHT_TURN_INDICATOR);
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_TURN_LEFT, &leftTurnIndicatorActive_b, &TurnIndicatorActive_ms, C_ANIMATION_TIME_LIGHT_TURN_INDICATOR);
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR
    
#ifdef FEATURE_LIGHT_STATUS_HAZARD
    // Call check status for hazard light
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_HAZARD, &hazardIndicatorActive_b, &hazardIndicatorActive_ms, C_ANIMATION_TIME_LIGHT_HAZARD);
#endif // FEATURE_LIGHT_STATUS_HAZARD

#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
    // Call check status for lowbeam state
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_LOW_BEAM, &lowBeamActivated_b, &lowBeamActivated_ms, C_ANIMATION_TIME_LIGHT_LOW_BEAM);
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
    // Call check status for highbeam state
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_HIGH_BEAM, &highBeamActivated_b, &highBeamActivated_ms, C_ANIMATION_TIME_LIGHT_HIGH_BEAM);
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_FOG_FRONT
    // Call check status for fog front state
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_FOG_FRONT, &fogFrontLightActivated_b, &fogLightActivated_ms, C_ANIMATION_TIME_LIGHT_FOG_FRONT);
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT
#ifdef FEATURE_LIGHT_STATUS_FOG_REAR
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_FOG_REAR, &fogRearLightActivated_b, &fogLightActivated_ms, C_ANIMATION_TIME_LIGHT_FOG_REAR);
#endif // FEATURE_LIGHT_STATUS_FOG_REAR

#ifdef FEATURE_LIGHT_STATUS_BRAKING
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_BRAKING, &brakingIndicatorActive_b, &brakingIndicatorActive_ms, C_ANIMATION_TIME_LIGHT_BRAKING);
#endif // FEATURE_LIGHT_STATUS_BRAKING

#ifdef FEATURE_LIGHT_STATUS_REVERSE
    locAnimation = checkStatus(&locAnimation, enAnimation::ANIMATION_LIGHT_REVERSE, &reverseIndicatorActive_b, &reverseIndicatorActive_ms, C_ANIMATION_TIME_LIGHT_REVERSE);
#endif // FEATURE_LIGHT_STATUS_REVERSE

    return locAnimation;
}

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  Check Status
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/// @brief This function is to check if the light state shall overwrite or end the animation
/// @param curAnimation is a pointer to the current active animation
/// @param animation2Check shall be the animation which is currently checked light state
/// @param activationSwitch is a pointer to the activation switch of the currently checked light state
/// @param animationTime is a pointer to the timer which indicates how long the animation is already running
/// @param curAnimation indicates how long the animation shall last
enAnimation LightState::checkStatus( enAnimation * curAnimation, enAnimation animation2Check, bool * activationSwitch, ui16 * animationTime, ui16 animationTimeEnd )
{
    if (*activationSwitch)
    {
        if ( ( *animationTime < animationTimeEnd ) 
          && ( *curAnimation < animation2Check ) 
#ifdef NO_ANIMATION_INTERRUPTION
          // No interrupt of animation wanted
          && ( *curAnimation == enAnimation::ANIMATION_NONE )
#endif // NO_ANIMATION_INTERRUPTION
          )
        {            
            *curAnimation = animation2Check;
        }
        else
        {
            // reset information about low beam active
            *activationSwitch = false;

            // If current animation is low beam active, then reset
            if ( *curAnimation == animation2Check )
            {
                *curAnimation = enAnimation::ANIMATION_NONE;
            }
        }
    }

}