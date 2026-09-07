#pragma once

#include "measurement_data.h"

class Validator {
public:
    static bool isValid(const MeasurementData& data);
};
