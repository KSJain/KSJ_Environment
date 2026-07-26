#pragma once

#include <Arduino.h>

#include "AnalogLightConfig.h"
#include "IntervalTimer.h"
#include "LightReading.h"

namespace KSJ
{

class AnalogLightSensor
{
public:
    AnalogLightSensor(
        uint8_t pin,
        const AnalogLightConfig& config
    );

    bool begin();

    void update(
        uint32_t nowMs
    );

    bool isAvailable() const;

    bool hasNewReading() const;

    void clearNewReadingFlag();

    const LightReading&
        reading() const;

    void setConfig(
        const AnalogLightConfig& config
    );

    const AnalogLightConfig&
        config() const;

    uint8_t pin() const;

private:
    void readSensor(
        uint32_t nowMs
    );

    float calculateLightPercent(
        uint16_t rawValue
    ) const;

    bool calibrationValid() const;

    uint8_t _pin;

    AnalogLightConfig _config;

    IntervalTimer _refreshTimer;

    LightReading _reading;

    bool _available;
    bool _hasNewReading;
};

}