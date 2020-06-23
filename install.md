# require library
- https://github.com/adafruit/DHT-sensor-library
- https://arduinojson.org/v6
- https://github.com/knolleary/pubsubclient/tree/v2.8

# mosquito

# test
mosquitto_pub -h localhost -t pump_topic -m "{\"t\":12}"
