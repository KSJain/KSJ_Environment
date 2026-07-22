#pragma once

#include <Arduino.h>
#include <math.h>

namespace KSJ
{

struct EnvironmentReading
{
    float temperatureC = NAN;
    float humidityPercent = NAN;
    float pressureHpa = NAN;

    float co2Ppm = NAN;
    float vocIndex = NAN;
    float lightPercent = NAN;

    bool temperatureValid = false;
    bool humidityValid = false;
    bool pressureValid = false;

    bool co2Valid = false;
    bool vocValid = false;
    bool lightValid = false;

    uint32_t measuredAtMs = 0;
};

}