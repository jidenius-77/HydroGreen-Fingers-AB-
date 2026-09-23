#include <unity.h>
#include "validator.h"

// Giltig basmätning enligt D08. Varje test ändrar exakt ett fält.
static MeasurementData baseMeasurement() {
    MeasurementData d;
    d.timestampMs = 1000;
    d.airInsideC = 22.0f;
    d.airOutsideC = 15.0f;
    d.waterC = 20.0f;
    d.humidityInsidePct = 55.0f;
    return d;
}

void setUp(void) {}
void tearDown(void) {}

// TC-01: alla varden inom granserna
void test_valid_measurement_passes() {
    TEST_ASSERT_TRUE(Validator::isValid(baseMeasurement()));
}

// TC-02: luftfuktighet over 100 procent (D08)
void test_humidity_above_max_fails() {
    MeasurementData d = baseMeasurement();
    d.humidityInsidePct = 101.0f;
    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-03: exakt pa ovre gransen ska accepteras
void test_humidity_at_max_passes() {
    MeasurementData d = baseMeasurement();
    d.humidityInsidePct = 100.0f;
    TEST_ASSERT_TRUE(Validator::isValid(d));
}

int main(int, char**) {
    UNITY_BEGIN();
    RUN_TEST(test_valid_measurement_passes);
    RUN_TEST(test_humidity_above_max_fails);
    RUN_TEST(test_humidity_at_max_passes);
    return UNITY_END();
}