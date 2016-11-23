#include <Arduino.h>
#include "Button.h"

#define CURRENT 0
#define PREVIOUS 1
#define CHANGED 2

Button::Button(uint8_t buttonPin, uint8_t buttonMode){
  pin=buttonPin;
  pinMode(pin,INPUT);

	buttonMode==BUTTON_PULLDOWN ? pulldown() : pullup(buttonMode);
  state = 0;
  bitWrite(state,CURRENT,false);

  cb_onPress = 0;
  cb_onRelease = 0;
  cb_onClick = 0;
  cb_onHold = 0;

  numberOfPresses = 0;
  triggeredHoldEvent = true;
  holdEventThreshold = 1000;

  lastButtonState = HIGH;
  lastDebounceTime = 0;
  debounceDelay = 20;
}

void Button::pullup(uint8_t buttonMode)
{
	mode=BUTTON_PULLUP;
  if (buttonMode == BUTTON_PULLUP_INTERNAL)
  {
	  pinMode(pin,INPUT_PULLUP);
  }
}

void Button::pulldown(void)
{
	mode=BUTTON_PULLDOWN;
}

void Button::read(void)
{
  int reading = digitalRead(pin);

  bitWrite(state,PREVIOUS,bitRead(state,CURRENT));
  bitWrite(state,CHANGED,false);


  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      bitWrite(state,CHANGED,true);

      if (buttonState == !mode) {
        bitWrite(state,CURRENT,true);
      }
      else {
        bitWrite(state,CURRENT,false);
      }
    }
  }

  if (bitRead(state,CHANGED)) {
    if (bitRead(state,CURRENT)) {
      if (cb_onPress) { cb_onPress(*this); }
      pressedStartTime = millis();
      triggeredHoldEvent = false;
    }
    else {
      if (cb_onRelease) { cb_onRelease(*this); }

      if (!triggeredHoldEvent) {
        if (cb_onClick) { cb_onClick(*this); }
      }

      pressedStartTime = -1;
    }
  }
  else {
    if (bitRead(state, CURRENT)) {
      if (pressedStartTime != -1) {
        if (millis()-pressedStartTime > holdEventThreshold) {
          if (cb_onHold) { cb_onHold(*this); }
          triggeredHoldEvent = true;
          pressedStartTime = millis();
        }
      }
    }
  }

  lastButtonState = reading;
}

void Button::setHoldThreshold(unsigned int holdTime)
{
  holdEventThreshold = holdTime;
}

void Button::pressHandler(buttonEventHandler handler)
{
  cb_onPress = handler;
}

void Button::releaseHandler(buttonEventHandler handler)
{
  cb_onRelease = handler;
}

void Button::clickHandler(buttonEventHandler handler)
{
  cb_onClick = handler;
}

void Button::holdHandler(buttonEventHandler handler, unsigned int holdTime /*=0*/)
{
  if (holdTime>0) { setHoldThreshold(holdTime); }
  cb_onHold = handler;
}

unsigned int Button::holdTime() const { if (pressedStartTime!=-1) { return millis()-pressedStartTime; } else return 0; }

bool Button::operator==(Button &rhs)
{
  return (this==&rhs);
}
