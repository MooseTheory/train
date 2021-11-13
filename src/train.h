#ifndef Train_h
#define Train_h

#include <Arduino.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

class Train {
 private:
  ESP8266WebServer server;
  uint8_t pwmPin, in1, in2;
  int port, speed;
  bool doSound;
  unsigned long timeoutMillis;
  String serverIP;

 public:
  Train(const int httpPort,
        const uint8_t motorPwmPin,
        const uint8_t motorIn1,
        const uint8_t motorIn2,
        const uint8_t soundRelayPin,
        const unsigned long timeoutMillis);
  void setupRoutes();
  void setSpeed(const int newSpeed);
  int getSpeed();
  void setIsPlayingSound(const bool newDoSound);
  boolean isPlayingSound();
  void handleRoot();
  void handleClient();
};

#endif
