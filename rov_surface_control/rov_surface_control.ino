
#include <Wire.h>

//const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;
const int Z_pin = 2;

const int cam_x = 3;
const int cam_y = 4;

const int depth_sensor = 7;

const int divs = 6;
const int centre_adj = (1023 / divs) / 2;

byte x = 0;

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)

  // joystick
  //pinMode(SW_pin, INPUT);
 // digitalWrite(SW_pin, HIGH);

  Serial.begin(9600);           // start serial for output
}

void loop() {
  int x = map(analogRead(X_pin), 0, 1023, 0, 254);
  int y = map(analogRead(Y_pin), 0, 1023, 0, 254);
  int z = map(analogRead(Z_pin), 0, 1023, 0, 254);

  int c_x = map(analogRead(cam_x) + centre_adj, 0, 1023, 0, divs);
  int c_y = map(analogRead(cam_y) + centre_adj, 0, 1023, 0, divs);

  //getDepth();

 
  
  sendData(x, y, z, 0, c_x, c_y);
}

void getDepth(){
  int sensor = analogRead(depth_sensor);

  Serial.print("Sensor Value: ");
  Serial.println(sensor);

  float voltage = (sensor * 5.0) / 1024.0;
  
  Serial.print("Volts: ");
  Serial.println(voltage);

  float pressure_pasc = (3.0 * ((float)voltage - 0.47 )) * 1000000.0;
  float pressure_bar = pressure_pasc / 10e5;
  float pressure_psi = pressure_pasc / 6894.7;
  int depth = (pressure_psi - 14.3) / 0.445;
  
  Serial.print("Pressure Pascal: : ");
  Serial.println(pressure_pasc);
  Serial.print("Pressure Bar: ");
  Serial.println(pressure_bar);
  Serial.print("Pressure PSI: ");
  Serial.println(pressure_psi);
  Serial.print("Depth: ");
  Serial.println(depth / 3.33);
  delay(100);
  
}

void sendData(int x, int y, int z, int light, int c_x, int c_y){
  Wire.beginTransmission(8); // transmit to device #8
  Serial.print("x: ");
  Serial.println(analogRead(cam_x));
  Serial.print("y: ");
  Serial.println(analogRead(cam_y));
  //Serial.print("  x: ");
  //Serial.print(x);
  //Serial.print("  y : ");
 // Serial.println(y); 
    Serial.print("  camx : ");
    
  Serial.println(c_x);
  Serial.print("  cam_y : ");
  
  Serial.println(c_y);
  
  // send joystick x, y axis with delimeter
  Wire.write(x);     
  Wire.write(y);
  Wire.write(z); 
  Wire.write(light);
  Wire.write(c_x);
  Wire.write(c_y); 
  
  Wire.endTransmission();    // stop transmitting
  delay(100);
}

