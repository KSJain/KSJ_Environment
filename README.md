# KSJ_Environment

Simple, non-blocking environmental sensors for ESP32.

KSJ_Environment provides reusable wrappers around common environmental
sensors while presenting a consistent API to higher level applications.

The goal is to allow applications to think in terms of
temperature, humidity and pressure rather than individual sensor drivers.

---

## Features

- Non-blocking updates
- Configurable refresh intervals
- Timestamped measurements
- Validity checking
- Automatic sensor detection
- Common reading structure

---

## Supported Sensors

| Sensor | Status |
|---------|--------|
| AHT20 | ✅ |
| BMP280 | ✅ |
| DHT22 | Planned |
| SCD40 | Planned |
| ENS160 | Planned |

---

## Example

```cpp
KSJ::AHT20Sensor aht20(Wire, 2000);

aht20.begin();

void loop()
{
    aht20.update(millis());

    if (aht20.hasNewReading())
    {
        ...
    }
}