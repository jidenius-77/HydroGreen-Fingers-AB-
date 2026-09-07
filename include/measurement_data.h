#pragma once

struct MeasurementData {
    unsigned long timestampMs;
    float airInsideC;
    float airOutsideC;
    float waterC;
    float humidityInsidePct;
    bool valid;
};
