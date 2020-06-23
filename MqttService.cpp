#include "MqttService.h"

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
    _mqttClient->setCallback(MCallback);
}

void MqttServiceClass::reconnect() {
    ECHOLN("Attempting MQTT connection...");

    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);

    if (_mqttClient->connect(clientId.c_str())) {
        ECHOLN("[MqttServiceClass][reconnect] MQTT Connected");

        _mqttClient->subscribe(MQTT_PUMP_TOPIC);
        _mqttClient->subscribe(MQTT_LAMP_TOPIC);
        return;
    }

    ECHO("failed, rc=");
    ECHO(_mqttClient->state());
}

void MqttServiceClass::addMessage(MqttMessage * message)
{
    FREE_HEAP();
    if (_publishMessageCount >= MQTT_MESSAGE_QUEUE_LENGTH) {
        ECHOLN("[MqttServiceClass][addMessage] MESSAGE QUEUE IS FULL");
        MqttMessage expMessage;
		_messageQueue->pop(&expMessage);
        _publishMessageCount = _publishMessageCount - 1;
    }

    ECHO("[MqttServiceClass][addMessage]:");
    ECHO(message->topic);
    ECHO(" - ");
    ECHOLN(message->data);
    _messageQueue->push(message);
    _publishMessageCount = _publishMessageCount + 1;
}

void MqttServiceClass::publish()
{
    if (_publishMessageCount > 0) {
        MqttMessage message;
		_messageQueue->pop(&message);
        _publishMessageCount = _publishMessageCount - 1;
        ECHO("[MqttServiceClass][publish]:");
        ECHO(message.topic);
        ECHO(" - ");
        ECHOLN(message.data);

        _mqttClient->publish(message.topic, message.data);
    }
}

void MqttServiceClass::loop()
{

    if (!_mqttClient->connected()) {
        reconnect();
        return;
    }
    _mqttClient->loop();

    publish();
}

MqttServiceClass MqttService;

void MCallback(char *topic, unsigned char *payload, unsigned int length)
{
    String data;
    ECHO("[MqttServiceClass][callback] Message arrived: [");
    ECHO(topic);
    ECHO("] ");
    if (MQTT_DATA_LENGTH < length) {
        ECHOLN("MAX MQTT_DATA_LENGTH");
        return;
    }

    for (int i = 0; i < length; i++) {
        data += (char) payload[i];
    }
    ECHOLN(data);

    const size_t capacity = JSON_OBJECT_SIZE(1) + 18;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, data.c_str());
    unsigned long t = doc["t"];

    if (strcmp(topic, MQTT_PUMP_TOPIC) == 0) {
        ECHOLN("MQTT_PUMP_TOPIC");
        PumpService.incrementTimeOn(t * 1000);
        return;
    }

    if (strcmp(topic, MQTT_LAMP_TOPIC) == 0) {
        ECHOLN("MQTT_LAMP_TOPIC");
        LampService.incrementTimeOn(t * 1000);
        return;
    }

    ECHOLN("");
}
