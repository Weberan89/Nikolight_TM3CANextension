/*
    @file canTransceiver.hpp
    @author Andreas Weber
    @brief 
*/

#include <ESP32CAN.h>
#include <CAN_config.h>

#include "stdTypes.h"
#include "canConfiguration.hpp"

class CanTransceiver
{
  private:
    CAN_device_t VEHICLE_CAN_cfg;       // CAN Config
    CAN_device_t CHASSIS_CAN_cfg;       // CAN Config
    const int rx_queue_size = 10;       // Receive Queue size

#ifdef CAN_VEHICLE_AVAILABLE
    bool swDeactivateVehicleCAN;
    ui32 lastReceivedVehicleCANMsg;
    
    void setVehicleCANDeactivationState(bool new_state);
    void initVehicleCAN(void);
    void vehicleDataReceived(int packetSize);
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE    
    bool swDeactivateChassisCAN;
    ui32 lastReceivedChassisCANMsg;
    
    void setChassisCANDeactivationState(bool new_state);
    void initChassisCAN(void);
    void chassisDataReceived(int packetSize);
#endif // CAN_CHASSIS_AVAILABLE
    
    ui32 interruptCounter;

  public:

    CanTransceiver() : 
#ifdef CAN_VEHICLE_AVAILABLE
      swDeactivateVehicleCAN(false),
      swDeactivateVehicleCAN(UINT32_MAX),
#endif // CAN_VEHICLE_AVAILABLE
#ifdef CAN_CHASSIS_AVAILABLE
      swDeactivateChassisCAN(false),
      lastReceivedChassisCANMsg(UINT32_MAX),
#endif // CAN_CHASSIS_AVAILABLE
      interruptCounter(0u)
      {};

    void init();
    void run();
};

