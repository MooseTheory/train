#ifndef DO_SOUND_HANDLER_H
#define DO_SOUND_HANDLER_H

#include <ESP8266WebServer.h>

class DoSoundHandler : public RequestHandler {
 public:
  DoSoundHandler(const Uri& uri, const uint8_t relayPin) : _uri(uri.clone()), shouldPlaySound(false), soundRelayPin(relayPin) {}

  bool handle(ESP8266WebServer& server,
              HTTPMethod requestMethod,
              const String& requestUri) override;
  bool canHandle(HTTPMethod requestMethod, const String& requestUri) override;

  bool doSound();
  void setDoSound(const bool newDoSound);

 protected:
  Uri* _uri;
  bool shouldPlaySound;
  uint8_t soundRelayPin;

 private:
  const String jsonPrefix = "{\"success\": true, \"playSound\": ";
  const String jsonPostfix = "}";

  bool handlePost(ESP8266WebServer& server,
                  HTTPMethod requestMethod,
                  const String& requestUri);
  bool handleGet(ESP8266WebServer& server,
                 HTTPMethod requestMethod,
                 const String& requestUri);
};

#endif
