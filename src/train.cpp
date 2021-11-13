#include "train.h"

#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <uri/UriBraces.h>
#include "handlers/doSoundHandler.h"
#include "handlers/trainSpeedHandler.h"

Train::Train(const int httpPort,
             const uint8_t motorPwmPin,
             const uint8_t motorIn1,
             const uint8_t motorIn2,
             const uint8_t soundRelayPin,
             const unsigned long timeoutMillis)
    : server(httpPort), pwmPin(motorPwmPin), in1(motorIn1), in2(motorIn2) {
  // Enable serial for debugging
  Serial.begin(115200);

  // Setup the pins for the motor
  pinMode(motorPwmPin, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);

  // Setup the WiFi
  WiFi.mode(WIFI_STA);
  WiFiManager wm;
  // These are "Default" values if it can't reach it's last used SSID
  bool isConnected = wm.autoConnect("ChristmasTrain", "choochoo");
  if (isConnected) {
    Serial.println(F("Connected"));
  } else {
    Serial.println(F("Failed to connect, restarting"));
    ESP.restart();
  }
  Serial.println(WiFi.localIP());

  // Setup the webserver
  this->setupRoutes();
  this->server.begin();
}

void Train::handleClient() {
  server.handleClient();
}

void Train::setupRoutes() {
  server.addHandler(new TrainSpeedHandler(UriBraces("/speed/{}")));
  server.addHandler(new DoSoundHandler(UriBraces("/sound/{}")));
}

void Train::setSpeed(const int newSpeed) {}

int Train::getSpeed() {
  return this->speed;
}

void Train::setIsPlayingSound(const bool newDoSound) {}

bool Train::isPlayingSound() {
  return this->doSound;
}

void Train::handleRoot() {}
