#include "AirService.h"

/**
 * constructor
 */
AirServiceClass::AirServiceClass()
{
}

/**
 * destructor
 */
AirServiceClass::~AirServiceClass()
{
}

float AirServiceClass::getTem()
{
    return _temperature;
}

float AirServiceClass::getHum()
{
    return _humidity;
}

unsigned long AirServiceClass::getRecentTime()
{
    return _recent_time;
}

void AirServiceClass::measure()
{
    _humidity = dht->readHumidity();
    _temperature = dht->readTemperature();
    _recent_time = millis();
    ECHO("[AirServiceClass][measure] Humidity: ");
    ECHO(_humidity);
    ECHO(", emperature: ");
    ECHO(_temperature);
    ECHO(", recent_time: ");
    ECHOLN(_recent_time);
}

void AirServiceClass::setup()
{
    dht->begin();
}

void AirServiceClass::loop()
{
    if ((unsigned long) (millis() - _recent_time) > MEASURE_INTERVAL) {
        measure();
    }
}

AirServiceClass AirService;
