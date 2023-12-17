/*
    @file climate.hpp
    @author Andreas Weber
    @brief Definition of climate class
*/
#include "std_types.h"
#include "extension_configuration.hpp"
#include "base_feature.hpp"

#define C_TARGET_TEMP_INITIALIZED    1 << 0
#define C_CURRENT_TEMP_INITIALIZED   1 << 1
#define C_ALL_INITIALIZED            (C_TARGET_TEMP_INITIALIZED | C_CURRENT_TEMP_INITIALIZED)

class ClimateState : public BaseFeature
{
    private:
#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE
        // Target temperature
        si16 targetTemperature_last;
        si16 targetTemperature_now;
        ui16 targetTemperatureChange_ms;
        bool targetTemperatureIncrease_b;
        bool targetTemperatureDecrease_b;
#endif

#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE
        // Current temperature
        si16 currentTemperature_last;
        si16 currentTemperature_now;
        ui16 currentTemperatureChange_ms;
        bool currentTemperatureIncrease_b;
        bool currentTemperatureDecrease_b;
#endif

    public:

#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE
        void updateTargetTemperature(int new_temp);
        si16 getTargetTemperature() { return targetTemperature_now; };
        ui8 getCurrentTemperaturePerc() { return static_cast<ui8>( (currentTemperature_now - C_TEMPERATURE_MIN) / C_TEMPERATURE_RANGE ); };
#endif // FEATURE_CLIMATE_TARGET_TEMPERATURE

#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE
        void updateCurrentTemperature(int new_temp);
        si16 getCurrentTemperature() { return currentTemperature_now; };
        ui8 getTargetTemperaturePerc() { return static_cast<ui8>( (targetTemperature_now - C_TEMPERATURE_MIN) / C_TEMPERATURE_RANGE ); };
#endif // FEATURE_CLIMATE_CURRENT_TEMPERATURE

        void run();

        ClimateState() :
#ifdef FEATURE_CLIMATE_TARGET_TEMPERATURE
            targetTemperature_last(INT16_MAX),
            targetTemperature_now(INT16_MAX),
            targetTemperatureChange_ms(UINT16_MAX),
            targetTemperatureIncrease_b(false),
            targetTemperatureDecrease_b(false),
#endif // FEATURE_CLIMATE_TARGET_TEMPERATURE
#ifdef FEATURE_CLIMATE_CURRENT_TEMPERATURE
            currentTemperature_last(INT16_MAX),
            currentTemperature_now(INT16_MAX),
            currentTemperatureChange_ms(UINT16_MAX),
            currentTemperatureIncrease_b(false),
            currentTemperatureDecrease_b(false)
#endif // FEATURE_CLIMATE_CURRENT_TEMPERATURE
            {
#if defined(FEATURE_CLIMATE_TARGET_TEMPERATURE) || defined(FEATURE_CLIMATE_CURRENT_TEMPERATURE)
                feature_active = true;
                init_state = true;
#endif 
            };
};