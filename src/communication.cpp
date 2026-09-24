#include <Arduino.h>
#include "communication.h"

bool Communication::begin() {
    Serial.begin(115200);
    delay(300);
    return true;
}

String Communication::toJson(const MeasurementData& data) {
    String json;
    json.reserve(160);

    json += "{\"timestamp_ms\":";
    json += String(data.timestampMs);

    json += ",\"air_inside_c\":";
    json += String(data.airInsideC, 2);

    json += ",\"air_outside_c\":";
    json += String(data.airOutsideC, 2);

    json += ",\"water_c\":";
    json += String(data.waterC, 2);

    json += ",\"humidity_inside_pct\":";
    json += String(data.humidityInsidePct, 2);

    json += ",\"valid\":";
    json += (data.valid ? "true" : "false");

    json += "}";

    return json;
}

void Communication::send(const MeasurementData& data) {
    Serial.println(toJson(data));
}
