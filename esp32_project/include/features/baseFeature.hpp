/*
    @file base_feature.hpp
    @author Andreas Weber
    @brief Definition of base class for feautres, features shall be inherited from this base class
*/

#include "stdTypes.h"

class BaseFeature
{
    protected:
        bool init_state;
        bool feature_active;
        ui64 run_time;

    public:
        BaseFeature() : init_state(false),
            feature_active(false), run_time(0u) {};

        bool get_init_state(void) { return init_state; };

        enAnimation run(void) 
        { 
            init_state = false;
            return enAnimation::ANIMATION_NONE;
        };

        // Getter
        bool getFeatureActiveStatus() { return feature_active; };
        bool getFeatureReadyStatus() { return init_state; };
        bool getFeatureRuntime() { return run_time; };
};
