#pragma once

#include <Arduino.h>
#include "measurement_data.h"

class Communication {
public:
    bool begin();

    // Omvandlar en komplett mätning till ett strukturerat JSON-format.
    static String toJson(const MeasurementData& data);

    // Skickar den formaterade mätningen via aktuell kommunikationskanal.
    void send(const MeasurementData& data);
};
