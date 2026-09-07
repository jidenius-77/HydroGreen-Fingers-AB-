#include <Arduino.h>
#include "sensor_manager.h"

bool SensorManager::begin() {
    // TODO: Initiera gruppens riktiga sensorer här.
    return true;
}

MeasurementData SensorManager::read() {
    MeasurementData data{};
    data.timestampMs = millis();

#if USE_SIMULATED_SENSORS
    // Endast för tidig utveckling. Ska ersättas med riktiga sensorvärden.
    const float drift = static_cast<float>((millis() / 1000UL) % 10UL) * 0.1f;
    data.airInsideC = 22.0f + drift;
    data.airOutsideC = 20.0f + drift * 0.5f;
    data.waterC = 19.0f + drift * 0.2f;
    data.humidityInsidePct = 55.0f + drift;
#else
    // TODO: Läs riktiga sensorer.
    data.airInsideC = 0.0f;
    data.airOutsideC = 0.0f;
    data.waterC = 0.0f;
    data.humidityInsidePct = 0.0f;
#endif

    data.valid = true;
    return data;
}
