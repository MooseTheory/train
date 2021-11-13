#ifndef TRAIN_SPEED_HANDLER_H
#define TRAIN_SPEED_HANDLER_H

#include <ESP8266WebServer.h>

class TrainSpeedHandler : public RequestHandler {
 public:
  TrainSpeedHandler(const Uri& uri,
                    const uint8_t pwmPin,
                    const uint8_t in1,
                    const uint8_t in2)
      : _uri(uri.clone()), speed(0), pwmPin(pwmPin), in1(in1), in2(in2) {}

  bool handle(ESP8266WebServer& server,
              HTTPMethod requestMethod,
              const String& requestUri) override;
  bool canHandle(HTTPMethod requestMethod, const String& requestUri) override;

  int getSpeed();
  void setSpeed(const int newSpeed);

 protected:
  Uri* _uri;
  int speed;
  uint8_t pwmPin, in1, in2;
  unsigned long lastChangedMillis;

 private:
  const String jsonPrefix = "{\"success\": true, \"speed\": ";
  const String jsonPostfix = "}";

  bool handlePost(ESP8266WebServer& server,
                  HTTPMethod requestMethod,
                  const String& requestUri);
  bool handleGet(ESP8266WebServer& server,
                 HTTPMethod requestMethod,
                 const String& requestUri);
};

#endif
