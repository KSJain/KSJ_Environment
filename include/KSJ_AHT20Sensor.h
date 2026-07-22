#pragma once

#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_AHTX0.h>

#include "EnvironmentReading.h"
#include "IEnvironmentSensor.h"
#include "IntervalTimer.h"

namespace KSJ
{

class AHT20Sensor final
    : public IEnvironmentSensor
{
public:
    explicit AHT20Sensor(
        TwoWire& wire = Wire,
        uint32_t refreshIntervalMs = 2000
    );

    bool begin() override;

    void update(
        uint32_t nowMs
    ) override;

    bool isAvailable() const override;

    bool hasNewReading() const override;

    void clearNewReadingFlag() override;

    const EnvironmentReading&
        reading() const override;

    void setRefreshInterval(
        uint32_t intervalMs
    );

private:
    void readSensor(
        uint32_t nowMs
    );

    TwoWire& _wire;
    Adafruit_AHTX0 _sensor;

    IntervalTimer _refreshTimer;
    EnvironmentReading _reading;

    bool _available;
    bool _hasNewReading;
};

}