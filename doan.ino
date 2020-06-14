#include <ESP8266WebServer.h>
#include "EEPRomService.h"
#include "AppDebug.h"
#include "AppConfig.h"
#include "WifiService.h"

void setup() {
    Serial.begin(SERIAL_BAUD_RATE);
    ECHOLN("\nStart up...");
    WifiService.connect();
}

void loop() {
    if (WiFi.status() == WL_CONNECTED) {
        return;
    }
    WifiService.connect();
}