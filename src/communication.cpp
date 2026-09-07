#include <Arduino.h>
#include "communication.h"

bool Communication::begin() {
    Serial.begin(115200);
    delay(300);
    return true;
}

void Communication::send(const MeasurementData& data) {
    Serial.print("{\"timestamp_ms\":");
    Serial.print(data.timestampMs);
    Serial.print(",\"air_inside_c\":");
    Serial.print(data.airInsideC, 2);
    Serial.print(",\"air_outside_c\":");
    Serial.print(data.airOutsideC, 2);
    Serial.print(",\"water_c\":");
    Serial.print(data.waterC, 2);
    Serial.print(",\"humidity_inside_pct\":");
    Serial.print(data.humidityInsidePct, 2);
    Serial.print(",\"valid\":");
    Serial.print(data.valid ? "true" : "false");
    Serial.println("}");
}
