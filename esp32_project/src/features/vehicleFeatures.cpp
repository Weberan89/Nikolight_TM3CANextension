
/*
    @file vehicle_Features.cpp
    @author Andreas Weber
    @brief Implementation of vehicle features
*/

#include "vehicleFeatures.hpp"

void VehicleFeatures::goThrough(void){
    enAnimation animationAfterClimate = climate.run(currentActiveAnimation);
    enAnimation animationAfterLights = lights.run(currentActiveAnimation);
};