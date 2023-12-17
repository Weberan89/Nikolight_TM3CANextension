/*
    @file vehicle_features.hpp
    @author Andreas Weber
    @brief 
*/

#include "climate.hpp"

enum enAnimation
{
    ANIMATION_NONE,
    ANIMATION_CLIMATE,

};

class VehicleFeatures
{
    
private:
    enAnimation activeAnimation;
    ClimateState climate;

public:
    void goThrough();

    VehicleFeatures() : activeAnimation(ANIMATION_NONE){};
};
