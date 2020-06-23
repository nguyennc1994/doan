#ifndef PUMP_SERVICE_H_
#define PUMP_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include "AppDebug.h"
#include "MqttService.h"

#define PUMP_PIN D5
#define PUMP_SIGNAL_ON LOW
#define PUMP_SIGNAL_OFF HIGH
#define STATUS_ON (1)
#define STATUS_OFF (0)

class PumpServiceClass
{
public:
    PumpServiceClass();
    ~PumpServiceClass();
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

extern PumpServiceClass PumpService;

#endif /* PUMP_SERVICE_H_ */
