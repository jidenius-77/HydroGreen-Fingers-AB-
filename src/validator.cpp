#include "validator.h"

namespace {
    bool inRange(float value, float minValue, float maxValue) {
        return value >= minValue && value <= maxValue;
    }
}

bool Validator::isValid(const MeasurementData& data) {
    // Prototypgränser enligt beslut D08.
    // Gränserna används för teknisk rimlighetskontroll.
    const bool airInsideOk = inRange(data.airInsideC, -10.0f, 60.0f);
    const bool airOutsideOk = inRange(data.airOutsideC, -30.0f, 60.0f);
    const bool waterOk = inRange(data.waterC, 0.0f, 50.0f);
    const bool humidityOk = inRange(data.humidityInsidePct, 0.0f, 100.0f);

    return airInsideOk && airOutsideOk && waterOk && humidityOk;
}
