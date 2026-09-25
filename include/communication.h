#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <MQTT.h>

#include "measurement_data.h"

class Communication {
public:
    bool begin();

    // Körs kontinuerligt för att hålla MQTT-anslutningen aktiv.
    void loop();

    // Omvandlar en komplett mätning till JSON.
    static String toJson(const MeasurementData& data);

    // Skickar mätningen via Serial och MQTT.
    void send(const MeasurementData& data);

private:
    WiFiClient networkClient;
    MQTTClient mqttClient;

    bool connectWifi();
    bool connectMqtt();
};
