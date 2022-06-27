#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const char* SSID = "TP-LINK_AP_54B65E";
const char* MQTT_SERVER = "broker.hivemq.com";

WiFiClient cameraDrone;
PubSubClient Client(cameraDrone);

char mensagem[100];
WiFiClient CLIENT;
PubSubClient MQTT(CLIENT);

void setupWifi() {
  WiFi.begin(SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
}

void setup() {
  Serial.begin(115200);
  setupWifi();
}

void loop() {

}
