/*
    @file canDecoder.hpp
    @author Andreas Weber
    @brief File implements the decoding for relevant CAN signals

    Information for implementation was gathered from DBC files.
*/

#include "extensionConfiguration.hpp"

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Chassis CAN
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef CAN_CHASSIS_AVAILABLE
void decodeDasStatus(){};
#endif // CAN_CHASSIS_AVAILABLE


// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Vehicle CAN
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef CAN_VEHICLE_AVAILABLE
void decodeVcfrontLight(){};
void decodeVcrightLight(){};
void decodeHvacRight(){};
void decodeDifTorque(){};
void decodeDriveSystem(){};
#endif // CAN_VEHICLE_AVAILABLE
