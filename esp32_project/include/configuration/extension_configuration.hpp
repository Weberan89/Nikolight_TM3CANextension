/*
    @file extension_configuration.hpp
    @author Andreas Weber
    @brief File to configure which features shall be active

    This file is intended to list all features and the 
    possibility to either activate or deactivate each 
    individual feature.

    - "#define FEATURE_LIGHT_STATUS_TURN_INDICATOR" would lead to having this feature active
    - "//#define FEATURE_LIGHT_STATUS_TURN_INDICATOR" or removing the line will disable the feature
*/


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ADAS Features (Chassis CAN, ID399, DAS_status)
#define FEATURE_ADAS_BLIND_SPOT_WARNING             // DAS_blindSpotRearLeft, DAS_blindSpotRearRight
#define FEATURE_ADAS_LANE_DEPARTURE_WARNING         // DAS_laneDepartureWarning (1 = Left low, 3 = Left high, 2 = Right low, 4 = right high)
#define FEATURE_ADAS_FRONT_COLLISION_WARNING        // DAS_forwardCollisionWarning
#define FEATURE_ADAS_SIDE_COLLISION_WARNING         // DAS_sideCollisionWarning, DAS_sideCollisionInhibit, DAS_sideCollisionAvoid
#define FEATURE_ADAS_AUTOPILOT                      // DAS_autopilotState, DAS_autopilotHandsOnState
#define FEATURE_ADAS_SPEED_LIMIT_FUSED              // DAS_fusedSpeedLimit
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LIGHT FEATURES
// Vehicle CAN, ID3F5, VCFRONT_lighting
#define FEATURE_LIGHT_STATUS_TURN_INDICATOR         // VCFRONT_indicatorLeftRequest, VCFRONT_indicatorRightRequest
#define FEATURE_LIGHT_STATUS_HAZARD                 // VCFRONT_hazardLightRequest
#define FEATURE_LIGHT_STATUS_LOWBEAM_CHANGE         // VCFRONT_lowBeamLeftStatus, VCFRONT_lowBeamRightStatus
#define FEATURE_LIGHT_STATUS_HIGHBEAM_CHANGE        // VCFRONT_highBeamLeftStatus, VCFRONT_highBeamRightStatus
#define FEATURE_LIGHT_STATUS_FRONT_FOG              // VCFRONT_fogLeftStatus, VCFRONT_fogRightStatus

// Vehicle CAN, ID3E3, VCRIGHT_lightStatus
#define FEATURE_LIGHT_STATUS_BRAKING                // VCRIGHT_brakeLightStatus
#define FEATURE_LIGHT_STATUS_FRONT_BACK             // VCRIGHT_rearFogLightStatus
#define FEATURE_LIGHT_STATUS_REVERSE                // VCRIGHT_reverseLightStatus
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Climate Features
// Vehicle CAN, ID243, VCRIGHT_hvacStatus
#define FEATURE_CLIMATE_TARGET_TEMPERATURE          // VCRIGHT_hvacDuctTargetLeft, VCRIGHT_hvacDuctTargetRight
#define FEATURE_CLIMATE_CURRENT_TEMPERATURE         // VCRIGHT_hvacCabinTempEst
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Powertrain Features
// Vehicle CAN, ID186, DIF_torque
#define FEATURE_POWERTRAIN_TORQUE                   // DIF_torqueActual

// Vehicle CAN, ID118, DriveSystemStatus
#define FEATURE_POWERTRAIN_ACCELERATION_PEDAL       // DI_accelPedalPos
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// More advanced configuration
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define C_TEMPERATURE_MIN     -20     // -20°C
#define C_TEMPERATURE_MAX      40     //  40°C
#define C_TEMPERATURE_RANGE   (C_TEMPERATURE_MAX-C_TEMPERATURE_MIN)

// Animation time
#define C_ANIMATION_TIME_CLIMATE_TARGET_HOT     1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_TARGET_COLD    1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_CURRENT_HOT    1000    // 1sec.
#define C_ANIMATION_TIME_CLIMATE_CURRENT_COLD   1000    // 1sec.
