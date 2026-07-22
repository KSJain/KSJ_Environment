#include "KSJ_AHT20Sensor.h"

namespace KSJ
{

AHT20Sensor::AHT20Sensor(
    TwoWire& wire,
    uint32_t refreshIntervalMs
)
    : _wire(wire),
      _refreshTimer(refreshIntervalMs),
      _available(false),
      _hasNewReading(false)
{
}

bool AHT20Sensor::begin()
{
    _available = _sensor.begin(
        &_wire
    );

    if (_available)
    {
        _refreshTimer.triggerImmediately();
    }

    return _available;
}

void AHT20Sensor::update(
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

void AHT20Sensor::readSensor(
    uint32_t nowMs
)
{
    sensors_event_t humidityEvent;
    sensors_event_t temperatureEvent;

    _sensor.getEvent(
        &humidityEvent,
        &temperatureEvent
    );

    const float temperatureC =
        temperatureEvent.temperature;

    const float humidityPercent =
        humidityEvent.relative_humidity;

    _reading.temperatureC =
        temperatureC;

    _reading.humidityPercent =
        humidityPercent;

    _reading.temperatureValid =
        !isnan(temperatureC);

    _reading.humidityValid =
        !isnan(humidityPercent);

    _reading.measuredAtMs =
        nowMs;

    _hasNewReading = true;
}

bool AHT20Sensor::isAvailable() const
{
    return _available;
}

bool AHT20Sensor::hasNewReading() const
{
    return _hasNewReading;
}

void AHT20Sensor::clearNewReadingFlag()
{
    _hasNewReading = false;
}

const EnvironmentReading&
AHT20Sensor::reading() const
{
    return _reading;
}

void AHT20Sensor::setRefreshInterval(
    uint32_t intervalMs
)
{
    _refreshTimer.setInterval(
        intervalMs
    );
}

}