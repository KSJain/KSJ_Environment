#pragma once

#include <Arduino.h>
#include <Wire.h>

#include <Adafruit_BMP280.h>

#include "EnvironmentReading.h"
#include "IEnvironmentSensor.h"
#include "IntervalTimer.h"

namespace KSJ
{

class BMP280Sensor final
    : public IEnvironmentSensor
{
public:
    explicit BMP280Sensor(
        uint32_t refreshIntervalMs = 1000
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

    uint8_t detectedAddress() const;

    void setRefreshInterval(
        uint32_t intervalMs
    );

private:
    bool beginAtAddress(
        uint8_t address
    );

    void readSensor(
        uint32_t nowMs
    );

    Adafruit_BMP280 _sensor;

    IntervalTimer _refreshTimer;
    EnvironmentReading _reading;

    uint8_t _detectedAddress;

    bool _available;
    bool _hasNewReading;
};

}