#include "doSoundHandler.h"

bool DoSoundHandler::canHandle(HTTPMethod requestMethod,
                               const String& requestUri) {
  if (requestMethod != HTTP_ANY) {
    return false;
  }
  return _uri->canHandle(requestUri, RequestHandler::pathArgs);
}

bool DoSoundHandler::handle(ESP8266WebServer& server,
                            HTTPMethod requestMethod,
                            const String& requestUri) {
  if (!this->canHandle(requestMethod, requestUri)) {
    return false;
  } else if (requestMethod == HTTP_POST && pathArgs.size() > 0 &&
             pathArg(0).length() > 0) {
    return handlePost(server, requestMethod, requestUri);
  } else if (requestMethod == HTTP_GET) {
    return handleGet(server, requestMethod, requestUri);
  }
  return false;
}

bool DoSoundHandler::handleGet(ESP8266WebServer& server,
                               HTTPMethod requestMethod,
                               const String& requestUri) {
  (void)server;
  server.send(200, "application/json",
              jsonPrefix + this->shouldPlaySound + jsonPostfix);
  return true;
}

bool DoSoundHandler::handlePost(ESP8266WebServer& server,
                                HTTPMethod requestMethod,
                                const String& requestUri) {
  (void)server;
  const char firstChar = pathArg(0).charAt(0);
  if (firstChar == 'T' || firstChar == 't') {
    this->setDoSound(true);
  }
  server.send(200, "application/json",
              jsonPrefix + this->shouldPlaySound + jsonPostfix);
  return true;
}

bool DoSoundHandler::doSound() {
  return this->shouldPlaySound;
}

void DoSoundHandler::setDoSound(const bool newDoSound) {
  this->shouldPlaySound = newDoSound;
  if (this->shouldPlaySound) {
    digitalWrite(this->soundRelayPin, HIGH);
  } else {
    digitalWrite(this->soundRelayPin, LOW);
  }
  this->lastChangedMillis = millis();
  delay(20);
}
