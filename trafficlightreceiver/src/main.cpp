#include <Arduino.h>
#include "receiver.h"

void setup() {
  SetupLeds();
  Serial.begin(9600);
}

void loop()
{
  fsm();
}