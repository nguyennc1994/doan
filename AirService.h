#ifndef AIR_SERVICE_H_
#define AIR_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "AppDebug.h"
#include "MqttService.h"

#define DHT_PIN D2
#define DHT_TYPE DHT11
#define AIR_MEASURE_INTERVAL (30000)

class AirServiceClass
{
public:
    AirServiceClass();
    ~AirServiceClass();
    void measure();
    void loop();
    void setup();
    float getTem();
    float getHum();
    unsigned long getRecentTime();

protected:
    unsigned long _recent_time = 0;
    float _temperature = 0;
    float _humidity = 0;
    DHT* dht = new DHT(DHT_PIN, DHT11);
};

extern AirServiceClass AirService;

#endif /* AIR_SERVICE_H_ */
