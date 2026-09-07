#include "validator.h"

namespace {
    bool inRange(float value, float minValue, float maxValue) {
        return value >= minValue && value <= maxValue;
    }
}

bool Validator::isValid(const MeasurementData& data) {
    // Dessa är prototypgränser, inte värden angivna av kunden.
    // Gruppen ska senare verifiera och motivera lämpliga gränser.
    const bool airInsideOk = inRange(data.airInsideC, -20.0f, 60.0f);
    const bool airOutsideOk = inRange(data.airOutsideC, -30.0f, 60.0f);
    const bool waterOk = inRange(data.waterC, 0.0f, 50.0f);
    const bool humidityOk = inRange(data.humidityInsidePct, 0.0f, 100.0f);

    return airInsideOk && airOutsideOk && waterOk && humidityOk;
}
