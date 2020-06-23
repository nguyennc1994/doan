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
    if (isnan(_humidity)) {
        _humidity = 0;
    }
    if (isnan(_temperature)) {
        _temperature = 0;
    }

    String data = "{\"h\":" + String(_humidity) + ",\"t\":" + String(_temperature) + "}";
    String topic = MQTT_AIR_TOPIC;

    MqttMessage message;
    topic.toCharArray(message.topic, MQTT_TOPIC_LENGTH);
    data.toCharArray(message.data, MQTT_DATA_LENGTH);
    ECHO("[AirServiceClass][measure] Humidity: ");
    ECHO(_humidity);
    ECHO(", Temperature: ");
    ECHO(_temperature);
    ECHO(", Recent time: ");
    ECHOLN(_recent_time);
    MqttService.addMessage(&message);
}

void AirServiceClass::setup()
{
    dht->begin();
}

void AirServiceClass::loop()
{
    if ((unsigned long) (millis() - _recent_time) > AIR_MEASURE_INTERVAL) {
        measure();
    }
}

AirServiceClass AirService;
