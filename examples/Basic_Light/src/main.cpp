#include <Arduino.h>

#include <AnalogLightConfig.h>
#include <KSJ_AnalogLightSensor.h>
#include <LightReading.h>

namespace Pins
{
    constexpr uint8_t LDR = 34;
}

/*
 * These are starting values only.
 *
 * After observing your sensor:
 * - cover the LDR and record the raw value
 * - illuminate it brightly and record the raw value
 * - replace these calibration endpoints
 */
const KSJ::AnalogLightConfig lightConfig
{
    0,      // dark raw value
    4095,   // bright raw value
    true,   // higher ADC means brighter
    500     // refresh interval in milliseconds
};

KSJ::AnalogLightSensor lightSensor(
    Pins::LDR,
    lightConfig
);

void printReading(
    const KSJ::LightReading& reading
)
{
    Serial.println();
    Serial.println(
        "Light reading"
    );

    Serial.println(
        "------------------------"
    );

    if (reading.rawValid)
    {
        Serial.print("Raw ADC: ");
        Serial.println(
            reading.rawValue
        );
    }
    else
    {
        Serial.println(
            "Raw ADC: INVALID"
        );
    }

    if (reading.lightPercentValid)
    {
        Serial.print(
            "Light:   "
        );

        Serial.print(
            reading.lightPercent,
            1
        );

        Serial.println(" %");
    }
    else
    {
        Serial.println(
            "Light:   INVALID"
        );
    }

    Serial.print(
        "Measured at: "
    );

    Serial.print(
        reading.measuredAtMs
    );

    Serial.println(" ms");

    Serial.println(
        "------------------------"
    );
}

void setup()
{
    Serial.begin(115200);
    delay(300);

    Serial.println();
    Serial.println(
        "KSJ_Environment Basic_Light"
    );

    const bool ready =
        lightSensor.begin();

    Serial.print("LDR pin: ");
    Serial.println(
        lightSensor.pin()
    );

    Serial.print("Light sensor: ");

    Serial.println(
        ready
            ? "READY"
            : "INVALID CONFIG"
    );
}

void loop()
{
    const uint32_t nowMs =
        millis();

    lightSensor.update(nowMs);

    if (!lightSensor.hasNewReading())
    {
        return;
    }

    printReading(
        lightSensor.reading()
    );

    lightSensor.clearNewReadingFlag();
}