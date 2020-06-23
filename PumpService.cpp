#include "PumpService.h"

/**
 * constructor
 */
PumpServiceClass::PumpServiceClass()
{
}

/**
 * destructor
 */
PumpServiceClass::~PumpServiceClass()
{
}

void PumpServiceClass::setup()
{
    pinMode(PUMP_PIN, OUTPUT);
}

unsigned int PumpServiceClass::getStatus()
{
    return _status;
}

unsigned long PumpServiceClass::getRecentTime()
{
    return _recent_time;
}

void PumpServiceClass::changeStatus(unsigned int status)
{
    _status = status;
    if (_status == STATUS_ON) {
        ECHOLN("[PumpServiceClass][changeStatus] Pump is on");
        digitalWrite(PUMP_PIN, PUMP_SIGNAL_ON);
    } else {
        ECHOLN("[PumpServiceClass][changeStatus] Pump is off");
        digitalWrite(PUMP_PIN, PUMP_SIGNAL_OFF);
    }
}

void PumpServiceClass::incrementTimeOn(unsigned long time)
{
    if (_timeOn == 0) {
        _recent_time = millis();
    }
    _timeOn += time;

    ECHO("[PumpServiceClass][incrementTimeOn] Time: ");
    ECHOLN(_timeOn);
}

void PumpServiceClass::loop()
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

PumpServiceClass PumpService;
