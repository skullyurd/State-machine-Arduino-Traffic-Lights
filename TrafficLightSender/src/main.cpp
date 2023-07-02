#include <Arduino.h>
#include "sender.h"

void setup() {
  setupLeds();
  Serial.begin(9600);
}

void loop()
{
  fsm();
}