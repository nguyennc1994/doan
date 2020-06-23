#ifndef MQTT_SERVICE_H_
#define MQTT_SERVICE_H_

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "AppDebug.h"
#include "cppQueue.h"

// #define MQTT_HOST "192.168.1.13"
#define MQTT_HOST "192.168.3.101"
#define MQTT_PORT (1883)
#define MQTT_AIR_TOPIC "air_topic"
#define MQTT_GROUND_TOPIC "ground_topic"
#define MQTT_PUMP_TOPIC "pump_topic"
#define MQTT_LAMP_TOPIC "lamp_topic"
#define MAX_PUBLISH_LENGTH (5)
#define	IMPLEMENTATION	FIFO
typedef struct structMqttMessage {
	char topic[15];
	char data[50];
} MqttMessage;

extern void MCallback(char *topic, unsigned char *payload, unsigned int length);

class MqttServiceClass
{
public:
    MqttServiceClass();
    ~MqttServiceClass();
    void setup();
    void loop();
    void addMessage(MqttMessage * message);

protected:
    void reconnect();
    void publish();

    WiFiClient _espClient;
    PubSubClient * _mqttClient = new PubSubClient(_espClient);
    unsigned int _publishMessageCount = 0;
    Queue *_messageQueue = new Queue(sizeof(MqttMessage), MAX_PUBLISH_LENGTH, IMPLEMENTATION);
};

extern MqttServiceClass MqttService;

#endif /* MQTT_SERVICE_H_ */
