#ifndef LAMP_SERVICE_H_
#define LAMP_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "AppDebug.h"
#include "MqttService.h"

#define LAMP_PIN D5
#define LAMP_SIGNAL_ON LOW
#define LAMP_SIGNAL_OFF HIGH
#define STATUS_ON (1)
#define STATUS_OFF (0)

class LampServiceClass
{
public:
    LampServiceClass();
    ~LampServiceClass();
    void setup();
    void loop();
    void changeStatus(unsigned int status);
    void incrementTimeOn(unsigned long plushTime);
    unsigned int getStatus();
    unsigned long getRecentTime();

protected:
    unsigned long _recent_time = 0;
    unsigned int _status = STATUS_OFF;
    unsigned long _timeOn = 0;
};

extern LampServiceClass LampService;

#endif /* LAMP_SERVICE_H_ */
