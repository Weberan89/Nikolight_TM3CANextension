/*
    @file canTransceiver.hpp
    @author Andreas Weber
    @brief 
*/

#include <ESP32CAN.h>
#include <CAN_config.h>

#include "stdTypes.h"
#include "canConfiguration.hpp"


typedef struct {
  ui32 recTimeStamp;
  ui32 recTimeStamp_last;
	union {
		ui8 u8[8];   /*access to CAN data via 8x 8bit signals*/
		ui32 u32[2]; /*access to CAN data via 2x 32bit signals*/
		ui64 u64;    /*access to CAN data via 64bit signal*/
	} data;
} CanFrame;


class CanTransceiver
{
  private:
    
#ifdef CAN_VEHICLE_AVAILABLE
    CanFrame ID3F5VCFRONT_lighting;
    CanFrame ID3E3VCRIGHT_lightStatus;
    
    CanFrame ID243VCRIGHT_hvacStatus;
    
    CanFrame ID186DIF_torque;

    CanFrame ID118DriveSystemStatus;
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
    CanFrame ID399DAS_status;
#endif // CAN_CHASSIS_AVAILABLE

#ifdef CAN_VEHICLE_AVAILABLE
    bool swDeactivateVehicleCAN;
    ui32 lastReceivedVehicleCANMsg;
    
    void setVehicleCANDeactivationState(bool new_state);
    void initVehicleCAN(void);
    void vehicleDataReceived(int packetSize);

    void storeVehicleData(CanFrame *IDFrame);
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE    
    bool swDeactivateChassisCAN;
    ui32 lastReceivedChassisCANMsg;
    
    void setChassisCANDeactivationState(bool new_state);
    void initChassisCAN(void);
    void chassisDataReceived(int packetSize);

    void storeChassisData(CanFrame *IDFrame);
#endif // CAN_CHASSIS_AVAILABLE
    
    void storeData(MCP2515Class * currentCAN, CanFrame * IDFrame);

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
      {
#ifdef CAN_VEHICLE_AVAILABLE
        ID3F5VCFRONT_lighting.recTimeStamp = 0u;
        ID3F5VCFRONT_lighting.recTimeStamp_last = 0u;
        ID3F5VCFRONT_lighting.data = 0u;

        ID3E3VCRIGHT_lightStatus.recTimeStamp = 0u;
        ID3E3VCRIGHT_lightStatus.recTimeStamp_last = 0u;
        ID3E3VCRIGHT_lightStatus.data = 0u;
        
        ID243VCRIGHT_hvacStatus.recTimeStamp = 0u;
        ID243VCRIGHT_hvacStatus.recTimeStamp_last = 0u;
        ID243VCRIGHT_hvacStatus.data = 0u;
        
        ID186DIF_torque.recTimeStamp = 0u;
        ID186DIF_torque.recTimeStamp_last = 0u;
        ID186DIF_torque.data = 0u;

        ID118DriveSystemStatus.recTimeStamp = 0u;
        ID118DriveSystemStatus.recTimeStamp_last = 0u;
        ID118DriveSystemStatus.data = 0u;
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
    CanFrame ID399DAS_status.recTimeStamp = 0u;
    CanFrame ID399DAS_status.recTimeStamp_last = 0u;
    CanFrame ID399DAS_status.data = 0u;
#endif // CAN_CHASSIS_AVAILABLE


      };

    void init();
    void run();
};

