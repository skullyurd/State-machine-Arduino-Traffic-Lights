#include <Arduino.h>

#include "receiver.h"

//traffic light slave
const int REDLED = 10;
const int YELLOWLED = 9;
const int GREENLED = 8;

enum States
{
  IDLE,
  LEDON,
  LEDOFF,
  DISRUPTED,
  UNKNOWNMESSAGE,
  LEDGO,
  LEDWAIT,
  LEDSTOP
};

void SetupLeds()
{ 
  //traffic light 1
  pinMode(REDLED, OUTPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
}

void YellowLedOn()
{
  digitalWrite(YELLOWLED, HIGH);
}

void YellowLedOff() {
  digitalWrite(YELLOWLED, LOW);
}

void RedLedOn() {
  digitalWrite(REDLED, HIGH);
}

void RedLedOff() { 
  digitalWrite(REDLED, LOW);
}

void GreenLedOn() {
  digitalWrite(GREENLED, HIGH);
}

void GreenLedOff() {
  digitalWrite(GREENLED, LOW);
}

void BlinkError()
{
    YellowLedOn();
    delay(500);
    YellowLedOff();
    delay(500);
}

void TurnAllOff()
{
    RedLedOff();
    YellowLedOff();
    GreenLedOff();
}

void TurnAllOn()
{ 
    RedLedOn();
    YellowLedOn();
    GreenLedOn();
}

static States state = IDLE;
void CheckState()
{
    switch (state)
  {
    case IDLE:
        BlinkError();
        break;
    case LEDON:
        TurnAllOn();    
        break;
    case LEDOFF:
        TurnAllOff();
        break;
    case DISRUPTED:
        BlinkError();
        break;

    case UNKNOWNMESSAGE:
        BlinkError();
        break;

    case LEDGO:
        GreenLedOn();
        YellowLedOff();
        RedLedOff();
        break;

    case LEDWAIT:
        YellowLedOn();
        GreenLedOff();
        RedLedOff();
        break;

    case LEDSTOP:
        RedLedOn();
        YellowLedOff();
        GreenLedOff();
        break;
  }
}

char message[20] = "IDLE";
void fsm()
{
  if (Serial.available() > 0)
    {
        memset(message, 0, sizeof(message));
        Serial.readBytes(message, 20);
        Serial.println(message);
        if (strcmp(message, "TURNRED") == 0)
        {
            state = LEDSTOP;
        }
        else if (strcmp(message, "TURNGREEN") == 0)
        {
            state = LEDGO;
        }
        else if (strcmp(message, "TURNYELLOW") == 0)
        {
            state = LEDWAIT;
        }
        else
        {
            state = UNKNOWNMESSAGE;
        }
        CheckState();
    }
}