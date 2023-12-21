/*
    @file lights.hpp
    @author Andreas Weber
    @brief Definition of light status class
*/

#include "stdTypes.h"
#include "extensionConfiguration.hpp"
#include "baseFeature.hpp"

class LightState : public BaseFeature
{
private:
#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
    bool leftTurnIndicatorActive_b;
    bool rightTurnIndicatorActive_b;
    ui16 TurnIndicatorActive_ms;
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR

#ifdef FEATURE_LIGHT_STATUS_HAZARD
    bool hazardIndicatorActive_b;
    ui16 hazardIndicatorActive_ms;
#endif // FEATURE_LIGHT_STATUS_HAZARD

#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
    bool lowBeamActivated_b;
    ui16 lowBeamActivated_ms;
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
    bool highBeamActivated_b;
    ui16 highBeamActivated_ms;
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_FOG_FRONT
    bool fogFrontLightActivated_b;
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT
#ifdef FEATURE_LIGHT_STATUS_FOG_REAR
    bool fogRearLightActivated_b;
#endif // FEATURE_LIGHT_STATUS_FOG_REAR
#if  defined(FEATURE_LIGHT_STATUS_FOG_FRONT) || defined(FEATURE_LIGHT_STATUS_FOG_REAR)
    ui16 fogLightActivated_ms;
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT | FEATURE_LIGHT_STATUS_FOG_REAR

#ifdef FEATURE_LIGHT_STATUS_BRAKING
    bool brakingIndicatorActive_b;
    ui16 brakingIndicatorActive_ms;
#endif // FEATURE_LIGHT_STATUS_BRAKING

#ifdef FEATURE_LIGHT_STATUS_REVERSE
    bool reverseIndicatorActive_b;
    ui16 reverseIndicatorActive_ms;
#endif // FEATURE_LIGHT_STATUS_REVERSE

    ui64 run_time;

public:

#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
    void setLeftTurnIndicatorState(bool new_state);
    void setRightTurnIndicatorState(bool new_state);
    bool getStateLeftTurnIndicator(void) { return leftTurnIndicatorActive_b; };
    bool getStateRighTurnIndicator(void) { return rightTurnIndicatorActive_b; };
    ui16 getTimeSinceTurnIndicatorChange(void) { return TurnIndicatorActive_ms; };
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR

#ifdef FEATURE_LIGHT_STATUS_HAZARD
    void setHazardIndicatorState(bool new_state);
    bool getStateHazardIndicator(void) { return hazardIndicatorActive_b; };
    ui16 getTimeSinceHazardIndicatorChange(void) { return hazardIndicatorActive_ms; };
#endif // FEATURE_LIGHT_STATUS_HAZARD

#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
    void setLowBeamState(bool new_state);
    bool getStateLowBeam(void) { return lowBeamActivated_b; };
    ui16 getTimeSinceLowBeamChange(void) { return lowBeamActivated_ms; };
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
    void setHighBeamState(bool new_state);
    bool getStateHighBeam(void) { return highBeamActivated_b; };
    ui16 getTimeSinceHighBeamChange(void) { return highBeamActivated_ms; };
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE

#ifdef FEATURE_LIGHT_STATUS_FOG_FRONT
    void setFogFrontLightState(bool new_state);
    bool getStateFogFrontLight(void) { return fogFrontLightActivated_b; };
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT
#ifdef FEATURE_LIGHT_STATUS_FOG_REAR
    void setFogRearLightState(bool new_state);
    bool getStateFogRearLight(void) { return fogFrontLightActivated_b; };
#endif // FEATURE_LIGHT_STATUS_FOG_REAR
#if  defined(FEATURE_LIGHT_STATUS_FOG_FRONT) || defined(FEATURE_LIGHT_STATUS_FOG_REAR)
    ui16 getTimeSinceFogLightStateChange(void) { return fogLightActivated_ms; };
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT | FEATURE_LIGHT_STATUS_FOG_REAR

#ifdef FEATURE_LIGHT_STATUS_BRAKING
    void setBarkingIndicatorState(bool new_state);
    bool getStateBarkingIndicator(void) { return brakingIndicatorActive_b; };
    ui16 getTimeSinceBrakingIndicatorChange(void) { return brakingIndicatorActive_ms; };
#endif // FEATURE_LIGHT_STATUS_BRAKING

#ifdef FEATURE_LIGHT_STATUS_REVERSE
    void setReverseIndicatorState(bool new_state);
    bool getStateReverseIndicator(void) { return reverseIndicatorActive_b; };
    ui16 getTimeSinceReverseIndicatorChange(void) { return reverseIndicatorActive_ms; };
#endif // FEATURE_LIGHT_STATUS_REVERSE

    enAnimation run(enAnimation currentActiveAnimation);
    enAnimation checkStatus(enAnimation *curAnimation, enAnimation animation2Check, bool *activationSwitch, ui16 *animationTime, ui16 animationTimeEnd);

    LightState() :
#ifdef FEATURE_LIGHT_STATUS_TURN_INDICATOR
        leftTurnIndicatorActive_b(false),
        rightTurnIndicatorActive_b(false),
        TurnIndicatorActive_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_TURN_INDICATOR
#ifdef FEATURE_LIGHT_STATUS_HAZARD
        hazardIndicatorActive_b(false),
        hazardIndicatorActive_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_HAZARD
#ifdef FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
        lowBeamActivated_b(false),
        lowBeamActivated_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE
#ifdef FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
        highBeamActivated_b(false),
        highBeamActivated_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE
#ifdef FEATURE_LIGHT_STATUS_FOG_FRONT
        fogFrontLightActivated_b(false),
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT
#ifdef FEATURE_LIGHT_STATUS_FOG_REAR
        fogRearLightActivated_b(false),
#endif // FEATURE_LIGHT_STATUS_FOG_REAR
#if  defined(FEATURE_LIGHT_STATUS_FOG_FRONT) || defined(FEATURE_LIGHT_STATUS_FOG_REAR)
        fogLightActivated_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_FOG_FRONT | FEATURE_LIGHT_STATUS_FOG_REAR
#ifdef FEATURE_LIGHT_STATUS_BRAKING
        brakingIndicatorActive_b(false),
        brakingIndicatorActive_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_BRAKING
#ifdef FEATURE_LIGHT_STATUS_REVERSE
        reverseIndicatorActive_b(false),
        reverseIndicatorActive_ms(UINT16_MAX),
#endif // FEATURE_LIGHT_STATUS_REVERSE
        run_time(0u)
    {
#if defined(FEATURE_LIGHT_STATUS_TURN_INDICATOR) || defined(FEATURE_LIGHT_STATUS_HAZARD) || defined(FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE) || defined(FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE) || defined(FEATURE_LIGHT_STATUS_FOG_FRONT) 
        feature_active = true;
#else
        feature_active = false;
#endif
        init_state = true;
    };
};
