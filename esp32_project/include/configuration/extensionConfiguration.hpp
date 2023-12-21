/*
    @file extension_configuration.hpp
    @author Andreas Weber
    @brief File to configure which features shall be active

    This file is intended to list all features and the 
    possibility to either activate or deactivate each 
    individual feature.

    - "#define FEATURE_LIGHT_STATUS_TURN_INDICATOR" would lead to having this feature active
    - "//#define FEATURE_LIGHT_STATUS_TURN_INDICATOR" or removing the line will disable the feature

    Before going through the features make sure to check which CANs are available in your setup.
    Currently the following two CANs can be used for some features:
    
    - Vehicle CAN
    - Chassis CAN
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Define which CANs are available (comment out not available CANs)
#define CAN_VEHICLE_AVAILABLE
#define CAN_CHASSIS_AVAILABLE
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Define which Animation has highest priority (from low to high)
enum enAnimation
{
    // lowest priority
    ANIMATION_NONE,
    ANIMATION_POWERTRAIN,
    ANIMATION_CLIMATE_CURRENT_HOT,
    ANIMATION_CLIMATE_CURRENT_COLD,
    ANIMATION_CLIMATE_TARGET_HOT,
    ANIMATION_CLIMATE_TARGET_COLD,
    ANIMATION_LIGHT_FOG_REAR,
    ANIMATION_LIGHT_FOG_FRONT,
    ANIMATION_LIGHT_LOW_BEAM,
    ANIMATION_LIGHT_HIGH_BEAM,
    ANIMATION_LIGHT_TURN_LEFT,
    ANIMATION_LIGHT_TURN_RIGHT,
    ANIMATION_LIGHT_HAZARD,
    ANIMATION_LIGHT_BRAKING,
    ANIMATION_LIGHT_REVERSE,
    // highest priority
};

#define NO_ANIMATION_INTERRUPTION

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ADAS Features
#ifdef CAN_CHASSIS_AVAILABLE
    // Chassis CAN, ID399, DAS_status
    #define FEATURE_ADAS_BLIND_SPOT_WARNING             // DAS_blindSpotRearLeft, DAS_blindSpotRearRight
    #define FEATURE_ADAS_LANE_DEPARTURE_WARNING         // DAS_laneDepartureWarning (1 = Left low, 3 = Left high, 2 = Right low, 4 = right high)
    #define FEATURE_ADAS_FRONT_COLLISION_WARNING        // DAS_forwardCollisionWarning
    #define FEATURE_ADAS_SIDE_COLLISION_WARNING         // DAS_sideCollisionWarning, DAS_sideCollisionInhibit, DAS_sideCollisionAvoid
    #define FEATURE_ADAS_AUTOPILOT                      // DAS_autopilotState, DAS_autopilotHandsOnState
    #define FEATURE_ADAS_SPEED_LIMIT_FUSED              // DAS_fusedSpeedLimit
#endif // CAN_CHASSIS_AVAILABLE
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LIGHT FEATURES
#ifdef CAN_VEHICLE_AVAILABLE
    // Vehicle CAN, ID3F5, VCFRONT_lighting
    #define FEATURE_LIGHT_STATUS_TURN_INDICATOR         // VCFRONT_indicatorLeftRequest, VCFRONT_indicatorRightRequest
    #define FEATURE_LIGHT_STATUS_HAZARD                 // VCFRONT_hazardLightRequest
    #define FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE         // VCFRONT_lowBeamLeftStatus, VCFRONT_lowBeamRightStatus
    #define FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE        // VCFRONT_highBeamLeftStatus, VCFRONT_highBeamRightStatus
    #define FEATURE_LIGHT_STATUS_FOG_FRONT              // VCFRONT_fogLeftStatus, VCFRONT_fogRightStatus

    // Vehicle CAN, ID3E3, VCRIGHT_lightStatus
    #define FEATURE_LIGHT_STATUS_FOG_REAR               // VCRIGHT_rearFogLightStatus
    #define FEATURE_LIGHT_STATUS_BRAKING                // VCRIGHT_brakeLightStatus
    #define FEATURE_LIGHT_STATUS_REVERSE                // VCRIGHT_reverseLightStatus
#endif // CAN_VEHICLE_AVAILABLE
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Climate Features
#ifdef CAN_VEHICLE_AVAILABLE
    // Vehicle CAN, ID243, VCRIGHT_hvacStatus
    #define FEATURE_CLIMATE_TARGET_TEMPERATURE          // VCRIGHT_hvacDuctTargetLeft, VCRIGHT_hvacDuctTargetRight
    #define FEATURE_CLIMATE_CURRENT_TEMPERATURE         // VCRIGHT_hvacCabinTempEst
#endif // CAN_VEHICLE_AVAILABLE
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Powertrain Features
#ifdef CAN_VEHICLE_AVAILABLE
    // Vehicle CAN, ID186, DIF_torque
    #define FEATURE_POWERTRAIN_TORQUE                   // DIF_torqueActual

    // Vehicle CAN, ID118, DriveSystemStatus
    #define FEATURE_POWERTRAIN_ACCELERATION_PEDAL       // DI_accelPedalPos
#endif // CAN_VEHICLE_AVAILABLE    
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// More advanced configuration
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define C_TEMPERATURE_MIN     -20     // -20°C
#define C_TEMPERATURE_MAX      40     //  40°C
#define C_TEMPERATURE_RANGE   (C_TEMPERATURE_MAX-C_TEMPERATURE_MIN)

#define CYCLE_TIME_FEATURE  10 //10ms

// Animation time
#define C_ANIMATION_TIME_CLIMATE_TARGET_HOT     1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_TARGET_COLD    1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_CURRENT_HOT    1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_CURRENT_COLD   1000    // 1sec.

#define C_ANIMATION_TIME_LIGHT_TURN_INDICATOR   3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_HAZARD           3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_LOW_BEAM         3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_HIGH_BEAM        3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_FOG_FRONT        3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_FOG_REAR         3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_BRAKING          3000    // 3sec
#define C_ANIMATION_TIME_LIGHT_REVERSE          3000    // 3sec

#define C_ANIMATION_POWERTRAIN_TORQUE           3000    // 3sec
#define C_ANIMATION_POWERTRAIN_ACCELERATION     3000    // 3sec
