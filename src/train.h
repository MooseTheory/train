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

// void setSpeed(const int newSpeed) {
//   if (speed != 0) {
//     // stop first
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, LOW);
//     analogWrite(pwmEnable, 0);
//     delay(1000);
//   }
//   // set the new speed
//   bool isReverse = (newSpeed < 0);
//   speed = isReverse ? newSpeed * -1 : newSpeed;
//   if (isReverse) {
//     // Go backwards
//     digitalWrite(in1, HIGH);
//     digitalWrite(in2, LOW);
//   } else {
//     // Go forwards
//     digitalWrite(in1, LOW);
//     digitalWrite(in2, HIGH);
//   }
//   analogWrite(pwmEnable, speed);
//   lastChangeMillis = millis();
//   delay(20);
// }

// void setSound(const bool newDoSound) {
//   // Do the sound
//   doSound = newDoSound;
//   if (doSound) {
//     digitalWrite(soundRelayPin, HIGH);
//   } else {
//     digitalWrite(soundRelayPin, LOW);
//   }
//   lastChangeMillis = millis();
//   delay(20);
// }
