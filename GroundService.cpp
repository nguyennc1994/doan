#include "GroundService.h"

/**
 * constructor
 */
GroundServiceClass::GroundServiceClass()
{
}

/**
 * destructor
 */
GroundServiceClass::~GroundServiceClass()
{
}

float GroundServiceClass::getHum()
{
    return _humidity;
}

unsigned long GroundServiceClass::getRecentTime()
{
    return _recent_time;
}

void GroundServiceClass::measure()
{
    int t = analogRead(GROUND_SENSOR_PIN);
    _humidity = (1024 - t)/10.24;

    _recent_time = millis();
    String data = "{\"h\":" + String(_humidity) + "}";
    String topic = MQTT_GROUND_TOPIC;

    MqttMessage message;
    topic.toCharArray(message.topic, MQTT_TOPIC_LENGTH);
    data.toCharArray(message.data, MQTT_DATA_LENGTH);
    ECHO("[GroundServiceClass][measure] Humidity: ");
    ECHO(_humidity);
    ECHO(", recent_time: ");
    ECHOLN(_recent_time);
    MqttService.addMessage(&message);
}

void GroundServiceClass::setup()
{
}

void GroundServiceClass::loop()
{
    if ((unsigned long) (millis() - _recent_time) > GROUND_MEASURE_INTERVAL) {
        measure();
    }
}

GroundServiceClass GroundService;
