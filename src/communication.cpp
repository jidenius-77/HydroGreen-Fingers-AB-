#include <Arduino.h>
#include "communication.h"
#include "secrets.h"

namespace {
    constexpr const char* MQTT_BROKER = "broker.hivemq.com";
    constexpr int MQTT_PORT = 1883;
    constexpr const char* MQTT_TOPIC = "microhydros/measurement";

    constexpr unsigned long WIFI_TIMEOUT_MS = 10000;
    constexpr unsigned long MQTT_TIMEOUT_MS = 10000;
}

bool Communication::begin() {
    Serial.begin(115200);
    delay(300);

    mqttClient.begin(MQTT_BROKER, MQTT_PORT, networkClient);

    if (!connectWifi()) {
        Serial.println("ERROR: Wi-Fi connection failed");
        return false;
    }

    if (!connectMqtt()) {
        Serial.println("ERROR: MQTT connection failed");
        return false;
    }

    return true;
}

void Communication::loop() {
    if (mqttClient.connected()) {
        mqttClient.loop();
    }
}

bool Communication::connectWifi() {
    Serial.print("Connecting to Wi-Fi");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    const unsigned long startMs = millis();

    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startMs >= WIFI_TIMEOUT_MS) {
            Serial.println();
            Serial.println("ERROR: Wi-Fi connection timeout");
            return false;
        }

        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("Wi-Fi connected");

    return true;
}

bool Communication::connectMqtt() {
    Serial.print("Connecting to MQTT");

    const String clientId =
        "microhydros-" +
        String(static_cast<uint32_t>(ESP.getEfuseMac()), HEX);

    const unsigned long startMs = millis();

    while (!mqttClient.connect(clientId.c_str())) {
        if (millis() - startMs >= MQTT_TIMEOUT_MS) {
            Serial.println();
            Serial.println("ERROR: MQTT connection timeout");
            return false;
        }

        Serial.print(".");
        delay(500);
    }

    Serial.println();
    Serial.println("MQTT connected");

    return true;
}

String Communication::toJson(const MeasurementData& data) {
    String json;
    json.reserve(160);

    json += "{\"timestamp_ms\":";
    json += String(data.timestampMs);

    json += ",\"air_inside_c\":";
    json += String(data.airInsideC, 2);

    json += ",\"air_outside_c\":";
    json += String(data.airOutsideC, 2);

    json += ",\"water_c\":";
    json += String(data.waterC, 2);

    json += ",\"humidity_inside_pct\":";
    json += String(data.humidityInsidePct, 2);

    json += ",\"valid\":";
    json += (data.valid ? "true" : "false");

    json += "}";

    return json;
}

void Communication::send(const MeasurementData& data) {
    const String payload = toJson(data);

    // Serial behålls för lokal debug och verifiering.
    Serial.println(payload);

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WARNING: Wi-Fi disconnected");

        if (!connectWifi()) {
            return;
        }
    }

    if (!mqttClient.connected()) {
        Serial.println("WARNING: MQTT disconnected");

        if (!connectMqtt()) {
            return;
        }
    }

    if (!mqttClient.publish(MQTT_TOPIC, payload)) {
        Serial.println("ERROR: MQTT publish failed");
    }
}
