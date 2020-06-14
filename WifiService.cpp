#include "WifiService.h"

/**
 * constructor
 */
WifiServiceClass::WifiServiceClass()
{
}

/**
 * destructor
 */
WifiServiceClass::~WifiServiceClass()
{
}

int WifiServiceClass::connect()
{
    return connect(WIFI_SSID, WIFI_PASSWORD);
}

int WifiServiceClass::connect(const String &ssid, const String &pass)
{
    ECHO("[WifiService][connect] Wifi connect to: ");
    ECHOLN(ssid);
    ECHO("[WifiService][connect] With pass: ");
    ECHOLN(pass);
    WiFi.softAPdisconnect();
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    delay(100);
    WiFi.begin(ssid.c_str(), pass.c_str());

    int c = 0;
    ECHOLN("Waiting for Wifi to connect");
    while (c < 20) {
        if (WiFi.status() == WL_CONNECTED) {
            ECHOLN("Wifi connected!");
            ECHO("Local IP: ");
            ECHOLN(WiFi.localIP());

            return CONNECT_OK;
        }
        delay(500);
        ECHO(".");
        c++;
    }
    ECHOLN("");
    ECHOLN("Connect timed out");
    return CONNECT_TIMEOUT;
}


WifiServiceClass WifiService;
