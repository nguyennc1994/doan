#ifndef GROUND_SERVICE_H_
#define GROUND_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "AppDebug.h"
#include "MqttService.h"

#define GROUND_SENSOR_PIN D3
#define GROUND_MEASURE_INTERVAL (30000)

class GroundServiceClass
{
public:
    GroundServiceClass();
    ~GroundServiceClass();
    void measure();
    void loop();
    void setup();
    float getHum();
    unsigned long getRecentTime();

protected:
    unsigned long _recent_time = 0;
    float _humidity = 0;
};

extern GroundServiceClass GroundService;

#endif /* GROUND_SERVICE_H_ */
