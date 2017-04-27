#include <Servo.h>

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

Servo servo1;

int joyVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(115200);
  servo1.attach(5);
}

void loop() {
  // put your main code here, to run repeatedly:

  joyVal = map(analogRead(X_pin), 0, 1023, 0, 180);
  servo1.write(joyVal);

  Serial.print("x val: ");
  Serial.print(joyVal);
  
  delay(15);

  
}
