/*
    @file can_configuration.hpp
    @author Andreas Weber
    @brief File to configure the used CANs

    This file is used for configuration of CAN network.
*/

#define PIN_VEHICLE_CAN_TX GPIO_NUM_5
#define PIN_VEHICLE_CAN_RX GPIO_NUM_4

#define PIN_CHASSIS_CAN_TX GPIO_NUM_8
#define PIN_CHASSIS_CAN_RX GPIO_NUM_7

#define BAUDRATE_VEHICLE_CAN    500E3 // 500kBaud
#define BAUDRATE_CHASSIS_CAN    500E3 // 500kBaud