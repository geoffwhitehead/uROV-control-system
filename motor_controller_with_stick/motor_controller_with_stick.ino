#include <Servo.h>
#include "Motor.h"
#include <Wire.h>

Motor* m_motor_l;
Motor* m_motor_r;

int state_x = 0;
int state_y = 0;
int state_z = 0;
int state_light;

boolean DEBUG = true;

int threshold = 5;
    
void setup() {

  m_motor_l = new Motor(5,6,7,8);
  m_motor_r = new Motor(10,11,12,13);

  m_motor_l->activateMotor();
  m_motor_r->activateMotor();

  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);           // start serial for output
  
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 // Serial.println(analogRead(X_pin));
  //Serial.println(analogRead(Y_pin));
  
  delay(100);
}

void updateHorizontalMotors(int x, int y){

  if (x == state_x && y == state_y){
    return;
  }

  state_x = x;
  state_y = y;

  // adjust the range so that 0, 0 means the stick is central. Also keep the values within 127
  x = constrain((x - 128), -127, 127);
  y = constrain((y - 128), -127, 127);
  
  if (abs(x) < threshold) {
    x = 0;
  }

 if (abs(y) < threshold) {
    y = 0;
 }

  int mag = getMagnitude(x, y);

  int m_right_thrust = mag;
  int m_left_thrust = mag;

  if (mag > threshold) {
    if (x > 0){
      m_right_thrust = y - x;
    } else {
      m_left_thrust = y + x;
    }
  } else if (mag < -threshold) {
    if (x > 0){
      m_right_thrust = y + x;
    } else {
      m_left_thrust = y - x;
    }
  }
  
  m_motor_l->applyThrust(constrain(m_left_thrust * 2, -254, 254));
  m_motor_r->applyThrust(constrain(m_right_thrust * 2, -254, 254));

  if(DEBUG){
    Serial.print("Mag: ");
    Serial.print(mag);
    Serial.print("  left: ");
    Serial.print(m_left_thrust);
    Serial.print("  right: ");
    Serial.print(m_right_thrust);
    Serial.print("  x: ");
    Serial.print(x);
    Serial.print("  y : ");
    Serial.println(y);
  }
}

void updateVerticalMotors(int z){
   if (z == state_z){
    return;
  }

  state_z = z;
}

int getMagnitude(int x, int y){
  int sum = (x*x) + (y*y);
  int val = constrain(sqrt(abs(sum)), -127, 127);

  if (y < 0) {
    return -val;
  }
  return val;
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  Serial.println("Receiving... ");
  int x = Wire.read();
  int y = Wire.read();
  int z = Wire.read();
  int light = Wire.read();

  updateHorizontalMotors(x, y);

  //Serial.println(x);
  //Serial.println(y);
  Serial.println(z);
  //Serial.println(light);
}

