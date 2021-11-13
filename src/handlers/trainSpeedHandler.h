#ifndef TRAIN_SPEED_HANDLER_H
#define TRAIN_SPEED_HANDLER_H

#include <ESP8266WebServer.h>

class TrainSpeedHandler : public RequestHandler {
 public:
  TrainSpeedHandler(const Uri& uri) : _uri(uri.clone()), speed(0) {}

  bool handle(ESP8266WebServer& server,
              HTTPMethod requestMethod,
              const String& requestUri) override;
  bool canHandle(HTTPMethod requestMethod, const String& requestUri) override;

  int getSpeed();
  void setSpeed(const int newSpeed);

 protected:
  Uri* _uri;
  int speed;

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
