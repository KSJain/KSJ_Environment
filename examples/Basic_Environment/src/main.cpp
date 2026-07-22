#include <Arduino.h>
#include <Wire.h>

#include <KSJ_AHT20Sensor.h>
#include <KSJ_BMP280Sensor.h>

namespace Pins
{
    constexpr uint8_t SDA = 21;
    constexpr uint8_t SCL = 22;
}

KSJ::AHT20Sensor aht20(
    Wire,
    2000
);

KSJ::BMP280Sensor bmp280(
    1000
);

void printAht20Reading()
{
    const KSJ::EnvironmentReading&
        reading = aht20.reading();

    Serial.println();
    Serial.println("AHT20");

    if (reading.temperatureValid)
    {
        Serial.print("Temperature: ");
        Serial.print(
            reading.temperatureC,
            2
        );
        Serial.println(" C");
    }

    if (reading.humidityValid)
    {
        Serial.print("Humidity:    ");
        Serial.print(
            reading.humidityPercent,
            2
        );
        Serial.println(" %");
    }

    Serial.print("Measured at: ");
    Serial.print(
        reading.measuredAtMs
    );
    Serial.println(" ms");
}

void printBmp280Reading()
{
    const KSJ::EnvironmentReading&
        reading = bmp280.reading();

    Serial.println();
    Serial.println("BMP280");

    if (reading.temperatureValid)
    {
        Serial.print("Temperature: ");
        Serial.print(
            reading.temperatureC,
            2
        );
        Serial.println(" C");
    }

    if (reading.pressureValid)
    {
        Serial.print("Pressure:    ");
        Serial.print(
            reading.pressureHpa,
            2
        );
        Serial.println(" hPa");
    }

    Serial.print("Measured at: ");
    Serial.print(
        reading.measuredAtMs
    );
    Serial.println(" ms");
}

void setup()
{
    Serial.begin(115200);
    delay(300);

    Wire.begin(
        Pins::SDA,
        Pins::SCL
    );

    Serial.println();
    Serial.println(
        "KSJ_Environment Basic_Environment"
    );

    const bool aht20Ready =
        aht20.begin();

    const bool bmp280Ready =
        bmp280.begin();

    Serial.print("AHT20:  ");
    Serial.println(
        aht20Ready
            ? "READY"
            : "NOT FOUND"
    );

    Serial.print("BMP280: ");
    Serial.println(
        bmp280Ready
            ? "READY"
            : "NOT FOUND"
    );

    if (bmp280Ready)
    {
        Serial.print(
            "BMP280 address: 0x"
        );

        Serial.println(
            bmp280.detectedAddress(),
            HEX
        );
    }
}

void loop()
{
    const uint32_t nowMs =
        millis();

    aht20.update(nowMs);
    bmp280.update(nowMs);

    if (aht20.hasNewReading())
    {
        printAht20Reading();
        aht20.clearNewReadingFlag();
    }

    if (bmp280.hasNewReading())
    {
        printBmp280Reading();
        bmp280.clearNewReadingFlag();
    }
}