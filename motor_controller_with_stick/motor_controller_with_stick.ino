#include <Servo.h>
#include "Motor.h"

const int SW_pin = 2;
const int X_pin = 0;
const int Y_pin = 1;

const int RPWM_L = 5;
const int LPWM_L = 6;
const int L_EN_L = 7;
const int R_EN_L = 8;

const int RPWM_R = 10;
const int LPWM_R = 11;
const int L_EN_R = 12;
const int R_EN_R = 13;

const int m_factor = 2;
Motor* m_motor_l;
Motor* m_motor_r;


int threshold = 5;
    
void setup() {


  // joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  
  m_motor_l = new Motor(5,6,7,8);
  m_motor_r = new Motor(10,11,12,13);

  m_motor_l->activateMotor();
  m_motor_r->activateMotor();
  
  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(X_pin));
  Serial.println(analogRead(Y_pin));
  int axis_x = map(analogRead(X_pin), 0, 1023, 0, 255) - 127; // adjusted to calibrate joystick slightly (joystick a bit out of whack)
  int axis_y = map(analogRead(Y_pin), 0, 1023, 0, 255) - 127;
      
  if (abs(axis_x) < threshold) {
    axis_x = 0;
  }

  if (abs(axis_y) < threshold) {
    axis_y = 0;
  }

  int mag = getMagnitude(axis_x, axis_y);

  int m_right_thrust = mag;
  int m_left_thrust = mag;

  if (mag > threshold) {
    if (axis_x > 0){
      m_right_thrust = axis_y - axis_x;
    } else {
      m_left_thrust = axis_y + axis_x;
    }
  } else if (mag < -threshold) {
    if (axis_x > 0){
      m_right_thrust = axis_y + axis_x;
    } else {
      m_left_thrust = axis_y - axis_x;
    }
  }
  
  m_motor_l->applyThrust(constrain(m_left_thrust * m_factor, -255, 255));
  m_motor_r->applyThrust(constrain(m_right_thrust * m_factor, -255, 255));
  
  Serial.print("Mag: ");
  Serial.print(mag);
  Serial.print("  left: ");
  Serial.print(m_left_thrust);
  Serial.print("  right: ");
  Serial.print(m_right_thrust);
  Serial.print("  x: ");
  Serial.print(axis_x);
  Serial.print("  y: ");
  Serial.println(axis_y);
  delay(50);
}

int getMagnitude(int x, int y){
  int val = constrain(sqrt((x*x) + (y*y)), -128, 128);

  if (y < 0) {
    return -val;
  }
  return val;
}

