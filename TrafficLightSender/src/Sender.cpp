#include <Arduino.h>

#include "sender.h"

//traffic light slave
  const int REDLED1 = 10;
  const int YELLOWLED1 = 9;
  const int GREENLED1 = 8;

enum states
{
    IDLE,
    LEDON,
    LEDOFF,
    LEDON_GO,
    LEDON_STOP,
    LEDON_WAIT,
    MOVEON,
    COUNTDOWN,
    INVALIDMESSAGE,
    DISRUPTION
};

void YellowOn()
{
    digitalWrite(YELLOWLED1, HIGH);
}

void YellowOff()
{
    digitalWrite(YELLOWLED1, LOW);
}

void RedOn()
{
    digitalWrite(REDLED1, HIGH);
}

void RedOff()
{
    digitalWrite(REDLED1, LOW);
}

void GreenOn()
{
    digitalWrite(GREENLED1, HIGH);
}

void GreenOff()
{
    digitalWrite(GREENLED1, LOW);
}

void TurnAllOff()
{
    RedOff();
    YellowOff();
    GreenOff();
    Serial.write("All Lights Off");
}

void TurnAllOn()
{
    RedOn();
    YellowOn();
    GreenOn();
    Serial.write("All Lights On");
}

void BlinkError()
{
    YellowOn();
    delay(500);
    YellowOff();
    delay(500);
    Serial.write("InvalidMessage");
}

void setupLeds()
{
    pinMode(REDLED1, OUTPUT);
    pinMode(YELLOWLED1, OUTPUT);
    pinMode(GREENLED1, OUTPUT);
}

states CheckState(states state)
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

    case LEDON_GO:
        Serial.write("TURNRED");
        delay(1000);
        GreenOn();
        YellowOff();
        RedOff();
        delay(5400);
        return LEDON_WAIT;
        break;

    case LEDON_STOP:
        Serial.write("TURNGREEN");
        delay(1000);
        RedOn();
        GreenOff();
        YellowOff();
        delay(5000);
        Serial.write("TURNYELLOW");
        delay(5000);
        return LEDON_GO;
        break;

    case LEDON_WAIT:
        YellowOn();
        GreenOff();
        RedOff();
        delay(3400);
        return LEDON_STOP;
        break;

    case MOVEON:

        break;

    case COUNTDOWN:
        YellowOn();
        delay(5000);
        break;

    case INVALIDMESSAGE:
        BlinkError();
        Serial.write("InvalidMessage");
        break;

    case DISRUPTION:
        BlinkError();
        Serial.write("Disruption");
        break;
    
    default:
        state = IDLE;
        break;
    }
}

static states state = LEDON_GO;
void fsm()
{

    state = CheckState(state);
}