#pragma once

#include <Arduino.h>

#include "EnvironmentReading.h"

namespace KSJ
{

class IEnvironmentSensor
{
public:
    virtual ~IEnvironmentSensor() = default;

    virtual bool begin() = 0;

    virtual void update(
        uint32_t nowMs
    ) = 0;

    virtual bool isAvailable() const = 0;

    virtual bool hasNewReading() const = 0;

    virtual void clearNewReadingFlag() = 0;

    virtual const EnvironmentReading&
        reading() const = 0;
};

}