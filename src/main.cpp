#include <Arduino.h>
#include "sensor_manager.h"
#include "validator.h"
#include "communication.h"

namespace {
    constexpr unsigned long MEASUREMENT_INTERVAL_MS = 5000;

    SensorManager sensors;
    Communication communication;
    unsigned long lastMeasurementMs = 0;
}

void setup() {
    communication.begin();

    if (!sensors.begin()) {
        Serial.println("ERROR: Sensor initialization failed");
    }

    Serial.println("MicroHydros started");
}

void loop() {
    const unsigned long now = millis();

    if (now - lastMeasurementMs < MEASUREMENT_INTERVAL_MS) {
        return;
    }

    lastMeasurementMs = now;

    MeasurementData data = sensors.read();
    data.valid = Validator::isValid(data);

    communication.send(data);
}
