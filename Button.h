/**************************************************************************/
/*!
    @file     Button.h
    @author   Jason Scheunemann <jason.scheunemann@gmail.com>
    @section LICENSE
    Software License Agreement (BSD License)
    Copyright (c) 2016, Jason Scheunemann
    All rights reserved.
    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/

#ifndef Button_h
#define Button_h

#include <inttypes.h>

#define BUTTON_PULLUP HIGH
#define BUTTON_PULLUP_INTERNAL 2
#define BUTTON_PULLDOWN LOW

class Button;
typedef void (*buttonEventHandler)(Button&);

class Button {
  public:

    Button(uint8_t buttonPin, uint8_t buttonMode=BUTTON_PULLUP_INTERNAL);

    void pullup(uint8_t buttonMode);
    void pulldown();

    void read();
    void setHoldThreshold(unsigned int holdTime);

    void pressHandler(buttonEventHandler handler);
    void releaseHandler(buttonEventHandler handler);
    void clickHandler(buttonEventHandler handler);
    void holdHandler(buttonEventHandler handler, unsigned int holdTime=0);

    unsigned int holdTime() const;
    inline unsigned int presses() const { return numberOfPresses; }

    bool operator==(Button &rhs);

  private:
    uint8_t pin;
    uint8_t mode;
    uint8_t state;
    unsigned long pressedStartTime;
    unsigned int holdEventThreshold;
    buttonEventHandler cb_onPress;
    buttonEventHandler cb_onRelease;
    buttonEventHandler cb_onClick;
    buttonEventHandler cb_onHold;
    unsigned int numberOfPresses;
    bool triggeredHoldEvent;

    int buttonState;
    int lastButtonState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;

};

#endif
