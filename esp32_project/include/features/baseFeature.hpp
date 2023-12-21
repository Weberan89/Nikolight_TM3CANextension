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


        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        //  Check Status
        // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        /// @brief This function is to check if the light state shall overwrite or end the animation
        /// @param curAnimation is a pointer to the current active animation
        /// @param animation2Check shall be the animation which is currently checked light state
        /// @param activationSwitch is a pointer to the activation switch of the currently checked light state
        /// @param animationTime is a pointer to the timer which indicates how long the animation is already running
        /// @param curAnimation indicates how long the animation shall last
        enAnimation checkStatus( enAnimation * curAnimation, enAnimation animation2Check, bool * activationSwitch, ui16 * animationTime, ui16 animationTimeEnd )
        {
            if (*activationSwitch)
            {
                if ( ( *animationTime < animationTimeEnd ) 
                && ( *curAnimation < animation2Check ) 
        #ifdef NO_ANIMATION_INTERRUPTION
                // No interrupt of animation wanted
                && ( *curAnimation == enAnimation::ANIMATION_NONE )
        #endif // NO_ANIMATION_INTERRUPTION
                )
                {            
                    *curAnimation = animation2Check;
                    *animationTime = *animationTime + CYCLE_TIME_FEATURE;
                }
                else
                {
                    // reset information about low beam active
                    *activationSwitch = false;

                    // If current animation is low beam active, then reset
                    if ( *curAnimation == animation2Check )
                    {
                        *curAnimation = enAnimation::ANIMATION_NONE;
                        *animationTime = UINT16_MAX;
                    }
                }
            }
        };
};
