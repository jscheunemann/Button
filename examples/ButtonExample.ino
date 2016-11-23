#include <Button.h>

Button button = Button(12);

void setup(){
  Serial.begin(9600);
  button.pressHandler(onPress);
  button.clickHandler(onClick);
  button.releaseHandler(onRelease);
  button.holdHandler(onHold);
}

//Contrived, but effective
void loop(){
  button.read();
}

void onClick(Button &btn) {
  Serial.println("clicked");
}

void onHold(Button &btn) {
  Serial.println("held");
}

void onRelease(Button &btn) {
  Serial.println("released");
}

void onPress(Button &btn) {
  Serial.println("pressed");
}
