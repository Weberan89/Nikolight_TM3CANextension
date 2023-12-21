/*
    @file canTransceiver.hpp
    @author Andreas Weber
    @brief 
*/

#include <Arduino.h>
#include <ESP32CAN.h>
#include <CAN_config.h>

#include "stdTypes.h"
#include "canConfiguration.hpp"

CAN_device_t VEHICLE_CAN_cfg;               // CAN Config
CAN_device_t CHASSIS_CAN_cfg;               // CAN Config
const int rx_queue_size = 10;       // Receive Queue size


CanTransceiver::vehicleDataReceived()
{
  CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Receive next CAN frame from queue
  if (xQueueReceive(VEHICLE_CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) 
  {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      printf("New standard frame");
    }
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
     }
      printf("\n");
  }
}

CanTransceiver::chassisDataReceived()
{
  CAN_frame_t rx_frame;

  unsigned long currentMillis = millis();

  // Receive next CAN frame from queue
  if (xQueueReceive(CHASSIS_CAN_cfg.rx_queue, &rx_frame, 3 * portTICK_PERIOD_MS) == pdTRUE) 
  {

    if (rx_frame.FIR.B.FF == CAN_frame_std) {
      printf("New standard frame");
    }
      printf(" from 0x%08X, DLC %d, Data ", rx_frame.MsgID,  rx_frame.FIR.B.DLC);
      for (int i = 0; i < rx_frame.FIR.B.DLC; i++) {
        printf("0x%02X ", rx_frame.data.u8[i]);
     }
      printf("\n");
  }
}


class CanTransceiver
{

  public:
    void init_VehicleCAN(void);
    void vehicleDataReceived();
    
    void init_ChassisCAN(void);
    void chassisDataReceived();
};


void CanTransceiver::init_VehicleCAN()
{
  VEHICLE_CAN_cfg.speed = BAUDRATE_VEHICLE_CAN;
  VEHICLE_CAN_cfg.tx_pin_id = PIN_VEHICLE_CAN_TX;
  VEHICLE_CAN_cfg.rx_pin_id = PIN_VEHICLE_CAN_RX;
  VEHICLE_CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
};

void CanTransceiver::init_VehicleCAN()
{
  CHASSIS_CAN_cfg.speed = BAUDRATE_CHASSIS_CAN;
  CHASSIS_CAN_cfg.tx_pin_id = PIN_CHASSIS_CAN_TX;
  CHASSIS_CAN_cfg.rx_pin_id = PIN_CHASSIS_CAN_RX;
  CHASSIS_CAN_cfg.rx_queue = xQueueCreate(rx_queue_size, sizeof(CAN_frame_t));
  // Init CAN Module
  ESP32Can.CANInit();
};
