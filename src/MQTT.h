#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#include "settings.h"






struct SubscribedChannel {
  String * topic;
  void (*callback)(byte *, unsigned int);
};




void MQTT_publish(const char * topic, String str);
void MQTT_publish(const char * topic, const char * msg);
void MQTT_loop();
void MQTT_setup();
