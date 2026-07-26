#pragma once

#include <Arduino.h>
#include <math.h>

namespace KSJ
{

struct LightReading
{
    uint16_t rawValue = 0;

    float lightPercent = NAN;

    bool rawValid = false;
    bool lightPercentValid = false;

    uint32_t measuredAtMs = 0;
};

}