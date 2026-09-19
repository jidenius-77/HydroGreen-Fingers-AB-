#pragma once

struct MeasurementData {
    unsigned long timestampMs = 0;
    float airInsideC = 0.0f;
    float airOutsideC = 0.0f;
    float waterC = 0.0f;
    float humidityInsidePct = 0.0f;
    bool valid = false;
};
