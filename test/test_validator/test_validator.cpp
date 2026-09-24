#include <unity.h>

#include "validator.h"

// Giltig basmätning enligt D08.
// Varje test ändrar exakt ett fält.
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

// TC-01: Alla värden inom gränserna ska accepteras.
void test_valid_measurement_passes() {
    TEST_ASSERT_TRUE(Validator::isValid(baseMeasurement()));
}

// TC-02: Luftfuktighet över 100 % ska nekas.
void test_humidity_above_max_fails() {
    MeasurementData d = baseMeasurement();

    d.humidityInsidePct = 101.0f;

    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-03: Exakt övre gränsen 100 % ska accepteras.
void test_humidity_at_max_passes() {
    MeasurementData d = baseMeasurement();

    d.humidityInsidePct = 100.0f;

    TEST_ASSERT_TRUE(Validator::isValid(d));
}

// TC-04: Inomhustemperatur under D08-gränsen -10 °C ska nekas.
void test_air_inside_below_min_fails() {
    MeasurementData d = baseMeasurement();

    d.airInsideC = -10.1f;

    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-05: Exakt nedre gränsen -10 °C ska accepteras.
void test_air_inside_at_min_passes() {
    MeasurementData d = baseMeasurement();

    d.airInsideC = -10.0f;

    TEST_ASSERT_TRUE(Validator::isValid(d));
}

// TC-06: Utomhustemperatur under -30 °C ska nekas.
void test_air_outside_below_min_fails() {
    MeasurementData d = baseMeasurement();
    d.airOutsideC = -30.1f;

    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-07: Exakt nedre gränsen -30 °C ska accepteras.
void test_air_outside_at_min_passes() {
    MeasurementData d = baseMeasurement();
    d.airOutsideC = -30.0f;

    TEST_ASSERT_TRUE(Validator::isValid(d));
}

// TC-08: Vattentemperatur under 0 °C ska nekas.
void test_water_below_min_fails() {
    MeasurementData d = baseMeasurement();
    d.waterC = -0.1f;

    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-09: Exakt nedre gränsen 0 °C ska accepteras.
void test_water_at_min_passes() {
    MeasurementData d = baseMeasurement();
    d.waterC = 0.0f;

    TEST_ASSERT_TRUE(Validator::isValid(d));
}

// TC-10: Luftfuktighet under 0 % ska nekas.
void test_humidity_below_min_fails() {
    MeasurementData d = baseMeasurement();
    d.humidityInsidePct = -0.1f;

    TEST_ASSERT_FALSE(Validator::isValid(d));
}

// TC-11: Exakt nedre gränsen 0 % ska accepteras.
void test_humidity_at_min_passes() {
    MeasurementData d = baseMeasurement();
    d.humidityInsidePct = 0.0f;

    TEST_ASSERT_TRUE(Validator::isValid(d));
}

// TC-13: Samtliga fyra mätvärden plus valid kan hållas i samma struktur (F6).
void test_measurement_data_holds_all_fields() {
    MeasurementData d;

    d.timestampMs = 12345;
    d.airInsideC = 21.5f;
    d.airOutsideC = 14.2f;
    d.waterC = 19.85f;
    d.humidityInsidePct = 52.3f;
    d.valid = true;

    TEST_ASSERT_EQUAL_UINT32(12345, d.timestampMs);
    TEST_ASSERT_EQUAL_FLOAT(21.5f, d.airInsideC);
    TEST_ASSERT_EQUAL_FLOAT(14.2f, d.airOutsideC);
    TEST_ASSERT_EQUAL_FLOAT(19.8f, d.waterC);
    TEST_ASSERT_EQUAL_FLOAT(52.3f, d.humidityInsidePct);
    TEST_ASSERT_TRUE(d.valid);
}

// T13b: Defaultvärden är nollställda och valid är false tills motsatsen bevisats.
void test_measurement_data_defaults_are_safe() {
    MeasurementData d;

    TEST_ASSERT_EQUAL_UINT32(0, d.timestampMs);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, d.airInsideC);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, d.airOutsideC);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, d.waterC);
    TEST_ASSERT_EQUAL_FLOAT(0.0f, d.humidityInsidePct);
    TEST_ASSERT_FALSE(d.valid);
}


int main(int, char**) {
    UNITY_BEGIN();

    RUN_TEST(test_valid_measurement_passes);
    RUN_TEST(test_humidity_above_max_fails);
    RUN_TEST(test_humidity_at_max_passes);
    RUN_TEST(test_air_inside_below_min_fails);
    RUN_TEST(test_air_inside_at_min_passes);
    RUN_TEST(test_air_outside_below_min_fails);
    RUN_TEST(test_air_outside_at_min_passes);
    RUN_TEST(test_water_below_min_fails);
    RUN_TEST(test_water_at_min_passes);
    RUN_TEST(test_humidity_below_min_fails);
    RUN_TEST(test_humidity_at_min_passes);
    RUN_TEST(test_measurement_data_holds_all_fields);
    RUN_TEST(test_measurement_data_defaults_are_safe);
    return UNITY_END();
}