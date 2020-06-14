#include <ESP8266WebServer.h>
#include "AppDebug.h"
#include "AppConfig.h"
#include "WifiService.h"
#include "AirService.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    AirService.setup();
    ECHOLN("\nStart up...");
    WifiService.connect();
}

void loop() {
    AirService.loop();

    if (WiFi.status() == WL_CONNECTED) {

        return;
    }
    WifiService.connect();
}
