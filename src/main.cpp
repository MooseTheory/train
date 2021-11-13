#include <Arduino.h>
// #include <ESP8266WiFi.h>
// #include <WiFiClient.h>

#include "staticHtml.h"
#include "train.h"

const int port = 80;
const uint8_t pwmEnable = D0;
const uint8_t in1 = D1;
const uint8_t in2 = D2;
const uint8_t soundRelayPin = 3;
const unsigned long automaticShutoffMillis = 5 * 60 * 1000;

Train* train;

void setup() {
  train = new Train(port, pwmEnable, in1, in2, soundRelayPin,
                    automaticShutoffMillis);
}

void loop() {
  train->handleClient();
}
