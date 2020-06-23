#include "LampService.h"

/**
 * constructor
 */
LampServiceClass::LampServiceClass()
{
}

/**
 * destructor
 */
LampServiceClass::~LampServiceClass()
{
}

void LampServiceClass::setup()
{
    pinMode(LAMP_PIN, OUTPUT);
}

unsigned int LampServiceClass::getStatus()
{
    return _status;
}

unsigned long LampServiceClass::getRecentTime()
{
    return _recent_time;
}

void LampServiceClass::changeStatus(unsigned int status)
{
    _status = status;
    if (_status == STATUS_ON) {
        ECHOLN("[LampServiceClass][changeStatus] Lamp is on");
        digitalWrite(LAMP_PIN, LAMP_SIGNAL_ON);
    } else {
        ECHOLN("[LampServiceClass][changeStatus] Lamp is off");
        digitalWrite(LAMP_PIN, LAMP_SIGNAL_OFF);
    }
}

void LampServiceClass::incrementTimeOn(unsigned long time)
{
    if (_timeOn == 0) {
        _recent_time = millis();
    }
    _timeOn += time;

    ECHO("[LampServiceClass][incrementTimeOn] Time: ");
    ECHOLN(_timeOn);
}

void LampServiceClass::loop()
{
    if (_timeOn) {
        if (_status == STATUS_OFF) {
            changeStatus(STATUS_ON);
            return;
        }

        if ((unsigned long) (millis() - _recent_time) > _timeOn) {
            _timeOn = 0;
            changeStatus(STATUS_OFF);
        }
    }
}

LampServiceClass LampService;
