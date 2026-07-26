#pragma once

#include <Arduino.h>

namespace KSJ
{

struct AnalogLightConfig
{
    constexpr AnalogLightConfig(
        uint16_t darkRaw,
        uint16_t brightRaw,
        bool higherIsBrighter,
        uint32_t refreshMs
    )
        : darkRawValue(darkRaw),
          brightRawValue(brightRaw),
          higherRawIsBrighter(higherIsBrighter),
          refreshIntervalMs(refreshMs)
    {
    }

    constexpr AnalogLightConfig() = default;

    uint16_t darkRawValue = 0;
    uint16_t brightRawValue = 4095;

    bool higherRawIsBrighter = true;

    uint32_t refreshIntervalMs = 500;
};

}