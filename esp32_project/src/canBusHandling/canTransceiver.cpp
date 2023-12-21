/*
    @file canTransceiver.cpp
    @author Andreas Weber
    @brief Implementation of CAN network transceiver functionality
*/

#include <CAN.h>

#include "extensionConfiguration.hpp"
#include "canTransceiver.hpp"
#include "canDecoder.hpp"


// Removed "ESP32SJA1000Class CAN" from ESP32SJA1000.cpp
// Removed "MCP2515Class CAN" from MCP2515.cpp

#ifdef CAN_VEHICLE_AVAILABLE
void CanTransceiver::storeVehicleData(CanFrame * IDFrame){
    saveData(&VehicleCAN, &IDFrame);
};
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
void CanTransceiver::storeChassisData(CanFrame * IDFrame){
    saveData(&ChassisCAN, &IDFrame);
};
#endif // CAN_CHASSIS_AVAILABLE

void CanTransceiver::storeData(MCP2515Class * currentCAN, CanFrame * IDFrame){
    // Update timestamp
    &IDFrame.recTimeStamp_last = &IDFrame.recTimeStamp;
    &IDFrame.recTimeStamp = millis();

    // Get all data and store locally
    ui8 loc_idx = 0u;
    while( &currentCAN.available() & loc_idx < 8)
    {
        &IDFrame.data[loc_idx] = &currentCAN.read();
    }
};

#ifdef CAN_VEHICLE_AVAILABLE

#ifdef ARDUINO_ARCH_ESP32
    ESP32SJA1000Class VehicleCAN;
#else
    MCP2515Class VehicleCAN;
#endif

void CanTransceiver::initVehicleCAN()
{
    VehicleCAN.setPins(PIN_VEHICLE_CAN_RX, PIN_VEHICLE_CAN_TX) // Set PINs for vehicle CAN
    
    if (!VehicleCAN.begin(BAUDRATE_VEHICLE_CAN) )              // start CAN communication
    {
#ifdef DEBUGGING
        Serial.println("Starting of vehicle CAN failed.");
#endif
    }
    VehicleCAN.observe();                                      // change to listen only mode
#ifdef DEBUGGING
    Serial.println("Switched to listen only mode fore vehicle CAN.");
#endif

    VehicleCAN.onReceive(vehicleDataReceived);
#ifdef DEBUGGING
    Serial.println("Registered receive interrupt for vehicle CAN messages.");
#endif

};

CanTransceiver::vehicleDataReceived(int packetSize)
{
    // increase interrupt counter
    interruptCounter++;

    // Get current time and overwrite variable
    lastReceivedVehicleCANMsg = millis();

#ifdef DEBUGGING
    Serial.print("Vehicle CAN;");
    if (VehicleCAN.packetExtended())
    {
        Serial.print("extended");
    }
    {
        Serial.print("standard");
    }
    Serial.print("; id 0x");
    Serial.print(VehicleCAN.packetId(), HEX);
    Serial.print("; length ");
    Serial.print(packetsize);
    Serial.print("; data ");
    while( VehicleCAN.available() )
    {
        Serial.print((char)VehicleCAN.read());
    }
    Serial.println(";");
#else
    switch (VehicleCAN.packetId()) :
    {
        case CAN_VEHICLE_ID_VCFRONT_LIGHT:
            storeVehicleData(&ID3F5VCFRONT_lighting);
            break;
        case CAN_VEHICLE_ID_VCRIGHT_LIGHT:
            storeVehicleData(&ID3E3VCRIGHT_lightStatus);
            break;
        case CAN_VEHICLE_ID_VCRIGHT_HVAC:
            storeVehicleData(&ID243VCRIGHT_hvacStatus);
            break;
        case CAN_VEHICLE_ID_DIF_TORQUE:
            storeVehicleData(&ID186DIF_torque);
            break;
        case CAN_VEHICLE_ID_DRIVE_SYSTEM_STATUS:
            storeVehicleData(&ID118DriveSystemStatus);
            break;
        default:
            // message is not relevant
            VehicleCAN.flush();
    }

#endif

};
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
#ifdef ARDUINO_ARCH_ESP32
    ESP32SJA1000Class ChassisCAN;
#else
    MCP2515Class ChassisCAN;
#endif

void CanTransceiver::initChassisCAN()
{
    ChassisCAN.setPins(PIN_CHASSIS_CAN_RX, PIN_CHASSIS_CAN_TX) // Set PINs for vehicle CAN
    
    if (!ChassisCAN.begin(BAUDRATE_CHASSIS_CAN) )              // start CAN communication
    {
        Serial.println("Starting of chassis CAN failed.");
    }
    ChassisCAN.observe();                                      // change to listen only mode
    Serial.println("Switched to listen only mode fore chassis CAN.");

    ChassisCAN.onReceive(chassisDataReceived);
    Serial.println("Registered receive interrupt for vehicle CAN messages.");
};

CanTransceiver::chassisDataReceived(int packetSize)
{
    // increase interrupt counter
    interruptCounter++;

    // Get current time and overwrite variable
    lastReceivedChassisCANMsg = millis();

#ifdef DEBUGGING
    Serial.print("Chassis CAN;");
    if (ChassisCAN.packetExtended())
    {
        Serial.print("extended");
    }
    {
        Serial.print("standard");
    }
    Serial.print("; id 0x");
    Serial.print(ChassisCAN.packetId(), HEX);
    Serial.print("; length ");
    Serial.print(packetsize);
    Serial.print("; data ");
    while( ChassisCAN.available() )
    {
        Serial.print((char)ChassisCAN.read());
    }
    Serial.println(";");
#else
    switch (ChassisCAN.packetId()) :
    {
        case CAN_CHASSIS_ID_ADAS:
            storeChassisData(&ID399DAS_status);
            break;
        default:
            // message is not relevant
            ChassisCAN.flush();
    }

#endif

};
#endif // CAN_CHASSIS_AVAILABLE



CanTransceiver::init()
{
#ifdef CAN_VEHICLE_AVAILABLE
    initVehicleCAN();
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
    initChassisCAN();
#endif // CAN_CHASSIS_AVAILABLE
}



CanTransceiver::run()
{
#ifdef CAN_VEHICLE_AVAILABLE
    vehicleDataRecevied();
#endif // CAN_VEHICLE_AVAILABLE

#ifdef CAN_CHASSIS_AVAILABLE
    chassisDataReceived();
#endif // CAN_CHASSIS_AVAILABLE
}

