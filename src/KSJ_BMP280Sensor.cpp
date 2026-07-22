#include "KSJ_BMP280Sensor.h"

namespace KSJ
{

namespace
{
    constexpr uint8_t PRIMARY_ADDRESS =
        0x76;

    constexpr uint8_t SECONDARY_ADDRESS =
        0x77;
}

BMP280Sensor::BMP280Sensor(
    uint32_t refreshIntervalMs
)
    : _refreshTimer(refreshIntervalMs),
      _detectedAddress(0),
      _available(false),
      _hasNewReading(false)
{
}

bool BMP280Sensor::begin()
{
    _available =
        beginAtAddress(PRIMARY_ADDRESS) ||
        beginAtAddress(SECONDARY_ADDRESS);

    if (_available)
    {
        _refreshTimer.triggerImmediately();
    }

    return _available;
}

bool BMP280Sensor::beginAtAddress(
    uint8_t address
)
{
    if (!_sensor.begin(
        address,
        BMP280_CHIPID
    ))
    {
        return false;
    }

    _detectedAddress = address;

    _sensor.setSampling(
        Adafruit_BMP280::MODE_NORMAL,
        Adafruit_BMP280::SAMPLING_X2,
        Adafruit_BMP280::SAMPLING_X16,
        Adafruit_BMP280::FILTER_X16,
        Adafruit_BMP280::STANDBY_MS_500
    );

    return true;
}
void BMP280Sensor::update(
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

void BMP280Sensor::readSensor(
    uint32_t nowMs
)
{
    const float temperatureC =
        _sensor.readTemperature();

    const float pressureHpa =
        _sensor.readPressure() / 100.0F;

    _reading.temperatureC =
        temperatureC;

    _reading.pressureHpa =
        pressureHpa;

    _reading.temperatureValid =
        !isnan(temperatureC);

    _reading.pressureValid =
        !isnan(pressureHpa);

    _reading.measuredAtMs =
        nowMs;

    _hasNewReading = true;
}

bool BMP280Sensor::isAvailable() const
{
    return _available;
}

bool BMP280Sensor::hasNewReading() const
{
    return _hasNewReading;
}

void BMP280Sensor::clearNewReadingFlag()
{
    _hasNewReading = false;
}

const EnvironmentReading&
BMP280Sensor::reading() const
{
    return _reading;
}

uint8_t BMP280Sensor::detectedAddress() const
{
    return _detectedAddress;
}

void BMP280Sensor::setRefreshInterval(
    uint32_t intervalMs
)
{
    _refreshTimer.setInterval(
        intervalMs
    );
}

}