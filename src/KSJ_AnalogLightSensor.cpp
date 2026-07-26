#include "KSJ_AnalogLightSensor.h"

namespace KSJ
{

AnalogLightSensor::AnalogLightSensor(
    uint8_t pin,
    const AnalogLightConfig& config
)
    : _pin(pin),
      _config(config),
      _refreshTimer(config.refreshIntervalMs),
      _available(false),
      _hasNewReading(false)
{
}

bool AnalogLightSensor::begin()
{
    pinMode(_pin, INPUT);
    analogReadResolution(12);

    _available = calibrationValid();

    if (_available)
    {
        _refreshTimer.triggerImmediately();
    }

    return _available;
}

void AnalogLightSensor::update(
    uint32_t nowMs
)
{
    if (!_available)
    {
        return;
    }

    if (!_refreshTimer.isReady(nowMs))
    {
        return;
    }

    readSensor(nowMs);
}

void AnalogLightSensor::readSensor(
    uint32_t nowMs
)
{
    const int rawRead =
        analogRead(_pin);

    const bool rawValid =
        rawRead >= 0 &&
        rawRead <= 4095;

    _reading.rawValid =
        rawValid;

    _reading.measuredAtMs =
        nowMs;

    if (!rawValid)
    {
        _reading.rawValue = 0;
        _reading.lightPercent = NAN;
        _reading.lightPercentValid = false;
        _hasNewReading = true;
        return;
    }

    _reading.rawValue =
        static_cast<uint16_t>(
            rawRead
        );

    _reading.lightPercent =
        calculateLightPercent(
            _reading.rawValue
        );

    _reading.lightPercentValid =
        !isnan(
            _reading.lightPercent
        );

    _hasNewReading = true;
}

float AnalogLightSensor::calculateLightPercent(
    uint16_t rawValue
) const
{
    if (!calibrationValid())
    {
        return NAN;
    }

    const float raw =
        static_cast<float>(
            rawValue
        );

    const float dark =
        static_cast<float>(
            _config.darkRawValue
        );

    const float bright =
        static_cast<float>(
            _config.brightRawValue
        );

    float normalized = 0.0F;

    if (_config.higherRawIsBrighter)
    {
        normalized =
            (raw - dark) /
            (bright - dark);
    }
    else
    {
        normalized =
            (dark - raw) /
            (dark - bright);
    }

    normalized = constrain(
        normalized,
        0.0F,
        1.0F
    );

    return normalized * 100.0F;
}

bool AnalogLightSensor::calibrationValid() const
{
    if (
        _config.darkRawValue ==
        _config.brightRawValue
    )
    {
        return false;
    }

    if (_config.higherRawIsBrighter)
    {
        return
            _config.brightRawValue >
            _config.darkRawValue;
    }

    return
        _config.darkRawValue >
        _config.brightRawValue;
}

bool AnalogLightSensor::isAvailable() const
{
    return _available;
}

bool AnalogLightSensor::hasNewReading() const
{
    return _hasNewReading;
}

void AnalogLightSensor::clearNewReadingFlag()
{
    _hasNewReading = false;
}

const LightReading&
AnalogLightSensor::reading() const
{
    return _reading;
}

void AnalogLightSensor::setConfig(
    const AnalogLightConfig& config
)
{
    _config = config;

    _refreshTimer.setInterval(
        config.refreshIntervalMs
    );

    _available =
        calibrationValid();

    if (_available)
    {
        _refreshTimer.triggerImmediately();
    }
}

const AnalogLightConfig&
AnalogLightSensor::config() const
{
    return _config;
}

uint8_t AnalogLightSensor::pin() const
{
    return _pin;
}

}
