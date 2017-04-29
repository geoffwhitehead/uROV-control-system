
#include <Wire.h>

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

const int Z_pin = 2;

byte x = 0;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)

  // joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  Serial.begin(9600);           // start serial for output
}

void loop() {
  int x = map(analogRead(X_pin), 0, 1023, 0, 254);
  int y = map(analogRead(Y_pin), 0, 1023, 0, 254);
  int z = map(analogRead(Z_pin), 0, 1023, 0, 254);
  sendData(x, y, z, 0);
}

void sendData(int x, int y, int z, int light){
  Wire.beginTransmission(8); // transmit to device #8

 // Serial.print("  x: ");
  //Serial.print(x);
  //Serial.print("  y : ");
  //Serial.println(y);
    
  // send joystick x, y axis with delimeter
  Wire.write(x);     
  Wire.write(y);
  Wire.write(z); 
  Wire.write(light);
  
  Wire.endTransmission();    // stop transmitting
  delay(100);
}

