/*
    @file vehicle_features.hpp
    @author Andreas Weber
    @brief 
*/

#include "climate.hpp"
#include "lights.hpp"

class VehicleFeatures
{
    
private:
    enAnimation currentActiveAnimation;
    ClimateState climate;
    LightState lights;

public:
    void goThrough();

    VehicleFeatures() : currentActiveAnimation(enAnimation::ANIMATION_NONE){};
};
