#include "trainSpeedHandler.h"

bool TrainSpeedHandler::canHandle(HTTPMethod requestMethod,
                                  const String& requestUri) {
  if (requestMethod != HTTP_ANY) {
    return false;
  }
  return _uri->canHandle(requestUri, RequestHandler::pathArgs);
}

bool TrainSpeedHandler::handle(ESP8266WebServer& server,
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

bool TrainSpeedHandler::handleGet(ESP8266WebServer& server,
                                  HTTPMethod requestMethod,
                                  const String& requestUri) {
  (void)server;
  server.send(200, "application/json", jsonPrefix + this->speed + jsonPostfix);
  return true;
}

bool TrainSpeedHandler::handlePost(ESP8266WebServer& server,
                                   HTTPMethod requestMethod,
                                   const String& requestUri) {
  (void)server;
  // toInt() returns a long, because it's stupid.
  long newSpeed = pathArg(0).toInt();
  newSpeed = (newSpeed > 255) ? 255 : newSpeed;
  newSpeed = (newSpeed < -256) ? -256 : newSpeed;
  // The bitwise and with UINT_MAX chops off the upper bits
  this->speed = newSpeed & UINT_MAX;

  server.send(200, "application/json", jsonPrefix + this->speed + jsonPostfix);
  return true;
}

int TrainSpeedHandler::getSpeed() {
  return this->speed;
}

void TrainSpeedHandler::setSpeed(const int newSpeed) {
  int adjustedSpeed = (newSpeed > 255) ? 255 : newSpeed;
  adjustedSpeed = (adjustedSpeed < -256) ? -256 : adjustedSpeed;
  this->speed = adjustedSpeed;

  if (speed != 0) {
    // stop first
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    analogWrite(this->pwmPin, 0);
    delay(1000);
  }
  // set the new speed
  bool isReverse = (newSpeed < 0);
  speed = isReverse ? newSpeed * -1 : newSpeed;
  if (isReverse) {
    // Go backwards
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else {
    // Go forwards
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  analogWrite(this->pwmPin, speed);
  this->lastChangedMillis = millis();
  delay(20);
}
