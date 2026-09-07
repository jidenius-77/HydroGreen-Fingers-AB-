#pragma once

#include "measurement_data.h"

class Communication {
public:
    bool begin();
    void send(const MeasurementData& data);
};
