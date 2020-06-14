#include "MqttService.h"

// void callback() {

// }

/**
 * constructor
 */
MqttServiceClass::MqttServiceClass()
{
}

/**
 * destructor
 */
MqttServiceClass::~MqttServiceClass()
{
}

void MqttServiceClass::setup()
{
    _mqttClient->setServer(MQTT_HOST, MQTT_PORT);
    _mqttClient->setCallback(callback);
}

void MqttServiceClass::reconnect() {
    ECHO("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (_mqttClient->connect(clientId.c_str())) {
        ECHOLN("connected");

        _mqttClient->subscribe(MQTT_PUMP_TOPIC);
        _mqttClient->subscribe(MQTT_LAMP_TOPIC);
        return;
    }

    ECHO("failed, rc=");
    ECHO(_mqttClient->state());
}

void MqttServiceClass::addMessage(MqttMessage * message)
{
    if (_publishMessageCount < MAX_PUBLISH_LENGTH) {
        _messageQueue->push(&message);
        _publishMessageCount = _publishMessageCount + 1;
        return;
    }

    ECHOLN("[MqttServiceClass][addMessage] MAX_PUBLISH_LENGTH");
}

void MqttServiceClass::publish()
{
    if (_publishMessageCount > 0) {
        MqttMessage message;
		_messageQueue->pop(&message);
        _publishMessageCount = _publishMessageCount - 1;

        _mqttClient->publish(message.topic.c_str(), message.data.c_str());
    }
}

void MqttServiceClass::loop()
{
    if (!_mqttClient->connected()) {
        reconnect();
        return;
    }

    publish();
}

MqttServiceClass MqttService;

void callback(char *topic, unsigned char *payload, unsigned int length)
{
    ECHO("[MqttServiceClass][callback] Message arrived: [");
    ECHO(topic);
    ECHO("] ");
    for (int i = 0; i < length; i++) {
        ECHO((char) payload[i]);
    }

    ECHOLN("");
}
