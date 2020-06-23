#include <ESP8266WebServer.h>
#include "AppDebug.h"
#include "AppConfig.h"
#include "WifiService.h"
#include "AirService.h"
#include "GroundService.h"
#include "LampService.h"
#include "PumpService.h"
#include "MqttService.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    AirService.setup();
    GroundService.setup();
    LampService.setup();
    PumpService.setup();
    MqttService.setup();
    ECHOLN("\nStart up...");
    WifiService.connect();
}

void loop() {
    LampService.loop();
    PumpService.loop();
    AirService.loop();
    GroundService.loop();

    if (WiFi.status() == WL_CONNECTED) {
        MqttService.loop();
        return;
    }
    WifiService.connect();
}
