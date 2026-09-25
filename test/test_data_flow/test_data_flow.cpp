#include <unity.h>
#include <Arduino.h>

#include "sensor_manager.h"
#include "validator.h"

void setUp() {
    fakeMillis = 0;
}

void tearDown() {
}

void test_complete_measurement_flow() {
    SensorManager sensors;

    TEST_ASSERT_TRUE(sensors.begin());

    fakeMillis = 5000;

    MeasurementData data = sensors.read();
    data.valid = Validator::isValid(data);

    TEST_ASSERT_EQUAL_UINT32(5000, data.timestampMs);

    TEST_ASSERT_FLOAT_WITHIN(0.01f, 22.5f, data.airInsideC);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 20.25f, data.airOutsideC);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 19.1f, data.waterC);
    TEST_ASSERT_FLOAT_WITHIN(0.01f, 55.5f, data.humidityInsidePct);

    TEST_ASSERT_TRUE(data.valid);
}

void test_multiple_measurement_cycles() {
    SensorManager sensors;

    TEST_ASSERT_TRUE(sensors.begin());

    unsigned long previousTimestamp = 0;

    for (int cycle = 1; cycle <= 5; cycle++) {
        fakeMillis = static_cast<unsigned long>(cycle) * 5000UL;

        MeasurementData data = sensors.read();
        data.valid = Validator::isValid(data);

        TEST_ASSERT_EQUAL_UINT32(fakeMillis, data.timestampMs);
        TEST_ASSERT_TRUE(data.valid);

        TEST_ASSERT_TRUE(data.airInsideC >= -10.0f);
        TEST_ASSERT_TRUE(data.airInsideC <= 60.0f);

        TEST_ASSERT_TRUE(data.airOutsideC >= -30.0f);
        TEST_ASSERT_TRUE(data.airOutsideC <= 60.0f);

        TEST_ASSERT_TRUE(data.waterC >= 0.0f);
        TEST_ASSERT_TRUE(data.waterC <= 50.0f);

        TEST_ASSERT_TRUE(data.humidityInsidePct >= 0.0f);
        TEST_ASSERT_TRUE(data.humidityInsidePct <= 100.0f);

        if (cycle > 1) {
            TEST_ASSERT_TRUE(data.timestampMs > previousTimestamp);
        }

        previousTimestamp = data.timestampMs;
    }
}

int main(int, char**) {
    UNITY_BEGIN();

    RUN_TEST(test_complete_measurement_flow);
    RUN_TEST(test_multiple_measurement_cycles);

    return UNITY_END();
}