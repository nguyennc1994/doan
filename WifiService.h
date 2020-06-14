#ifndef WIFI_SERVICE_H_
#define WIFI_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "AppDebug.h"

#define WIFI_SSID "BE-CA"
#define WIFI_PASSWORD "12345678"

#define CONNECT_OK (1)
#define CONNECT_TIMEOUT (-1)
#define CONNECT_SUSPENDED (-2)


class WifiServiceClass
{
public:
    WifiServiceClass();
    ~WifiServiceClass();
    int connect(const String &ssid, const String &pass);
    int connect();
};

extern WifiServiceClass WifiService;

#endif /* WIFI_SERVICE_H_ */