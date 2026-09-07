#pragma once

#include "measurement_data.h"

class SensorManager {
public:
    bool begin();
    MeasurementData read();
};
