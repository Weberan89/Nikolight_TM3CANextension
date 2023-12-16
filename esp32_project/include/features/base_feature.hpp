/*
    @file base_feature.hpp
    @author Andreas Weber
    @brief Definition of base class for feautres, features shall be inherited from this base class
*/

#include "std_types.h"

class BaseFeature
{
    protected:
        bool init_state;
        bool feature_active;
        uint64_t run_time;

    public:
        BaseFeature() : init_state(false),
            feature_active(false), run_time(0u) {};

        bool get_init_state(void) { return init_state; };

        void run(void) { init_state = false; };

        // Getter
        bool getFeatureActiveStatus() { return feature_active; };
        bool getFeatureReadyStatus() { return init_state; };
        bool getFeatureRuntime() { return run_time; };
};
