#include <ESP8266WebServer.h>
#include "AppDebug.h"
#include "AppConfig.h"
#include "WifiService.h"
#include "AirService.h"
#include "MqttService.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    AirService.setup();
    MqttService.setup();
    ECHOLN("\nStart up...");
    WifiService.connect();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        AirService.loop();
        MqttService.loop();
        return;
    }
    WifiService.connect();
}
