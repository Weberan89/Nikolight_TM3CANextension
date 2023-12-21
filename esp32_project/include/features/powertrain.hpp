/*
    @file powertrain.hpp
    @author Andreas Weber
    @brief Definition of powertrain class
*/
#include "stdTypes.h"
#include "extensionConfiguration.hpp"
#include "baseFeature.hpp"

class PowertrainState : public BaseFeature
{
    private:
#ifdef FEATURE_POWERTRAIN_TORQUE
        ui16 currentTorque_last;
        ui16 currentTorque_new;
        ui16 maxTorque_last;
        ui16 maxTorque_new;
        bool currentTorqueIncrease_b;
        bool currentTorqueDecrease_b;
#endif // FEATURE_POWERTRAIN_TORQUE

#ifdef FEATURE_POWERTRAIN_ACCELERATION_PEDAL
        ui16 currentAcceleration_last;
        ui16 currentAcceleration_new;
        bool currentAccelerationIncrease_b;
        bool currentAccelerationDecrease_b;
#endif // FEATURE_POWERTRAIN_ACCELERATION_PEDAL

        ui64 run_time;

public:

#ifdef FEATURE_POWERTRAIN_TORQUE
        void updateCurrentTorque(ui16 new_value);
        void updateMaxTorque(ui16 new_value);
        ui8 getCurrentTorquePerc(void) { return static_cast<ui8>( currentTorque_new / maxTorque_new ); };
#endif // FEATURE_POWERTRAIN_TORQUE

#ifdef FEATURE_POWERTRAIN_ACCELERATION_PEDAL
        void updateCurrentAcceleration(ui16 new_value);
        ui8 getCurrentAcceleration(void) { return currentAcceleration_new; };
#endif // FEATURE_POWERTRAIN_ACCELERATION_PEDAL

        enAnimation run(enAnimation currentActiveAnimation);

        PowertrainState() :
#ifdef FEATURE_POWERTRAIN_TORQUE
            currentTorque_last(UINT16_MAX),
            currentTorque_new(UINT16_MAX),
            maxTorque_last(UINT16_MAX),
            maxTorque_new(UINT16_MAX),
            currentTorqueIncrease_b(false),
            currentTorqueDecrease_b(false),
#endif // FEATURE_POWERTRAIN_TORQUE
#ifdef FEATURE_POWERTRAIN_ACCELERATION_PEDAL
            currentAcceleration_last(UINT16_MAX),
            currentAcceleration_new(UINT16_MAX),
            currentAccelerationIncrease_b(false),
            currentAccelerationDecrease_b(false),
#endif // FEATURE_POWERTRAIN_ACCELERATION_PEDAL
            run_time(0u)
            {
#if defined(FEATURE_POWERTRAIN_TORQUE) || defined(FEATURE_POWERTRAIN_ACCELERATION_PEDAL)
                feature_active = true;
#else
                feature_active = false;
#endif 
                init_state = true;
            };
};
