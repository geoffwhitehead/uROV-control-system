#include <Servo.h>

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

const int threshold = 5;

void setup() {

  // joystick
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  
  //motor 1
  pinMode(RPWM_L, OUTPUT);
  pinMode(LPWM_L, OUTPUT);
  pinMode(L_EN_L, OUTPUT);
  pinMode(R_EN_L, OUTPUT);
  digitalWrite(RPWM_L, LOW);
  digitalWrite(LPWM_L, LOW);
  digitalWrite(L_EN_L, LOW);
  digitalWrite(R_EN_L, LOW);
  
  // motor 2
  pinMode(RPWM_R, OUTPUT);
  pinMode(LPWM_R, OUTPUT);
  pinMode(L_EN_R, OUTPUT);
  pinMode(R_EN_R, OUTPUT);
  digitalWrite(RPWM_R, LOW);
  digitalWrite(LPWM_R, LOW);
  digitalWrite(L_EN_R, LOW);
  digitalWrite(R_EN_R, LOW);

  Serial.begin(115200);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:

  int axis_x = map(analogRead(X_pin), 0, 1023, 0, 255) - 125;
  int axis_y = map(analogRead(Y_pin), 0, 1023, 0, 255) - 128;
  //servo1.write(joyVal);
  delay(50);

  digitalWrite(R_EN_L,HIGH);
  digitalWrite(L_EN_L,HIGH);
  digitalWrite(R_EN_R,HIGH);
  digitalWrite(L_EN_R,HIGH);

  int mag = getMagnitude(axis_x, axis_y);

  if (mag < threshold) {
    mag = 0;
  }
  int m_right_thrust = mag;
  int m_left_thrust = mag;
  
  if (axis_x > 0){
    m_right_thrust = axis_y - mag;
  } else {
    m_left_thrust = axis_y - mag;
  }

  if (m_right_thrust < 0){
    analogWrite(RPWM_R, 0);
    analogWrite(LPWM_R, abs(m_right_thrust));
  } else {
    analogWrite(LPWM_R, 0);
    analogWrite(RPWM_R, abs(m_right_thrust));
  }

    if (m_left_thrust < 0){
    analogWrite(RPWM_L, 0);
    analogWrite(LPWM_L, abs(m_left_thrust));
  } else {
    analogWrite(LPWM_L, 0);
    analogWrite(RPWM_L, abs(m_left_thrust));
  }
  
  Serial.print("Mag: ");
  Serial.print(mag);
  Serial.print(" x: ");
  Serial.print(axis_x);
  Serial.print(" y: ");
  Serial.println(axis_y);
  delay(20);
}

int getMagnitude(int x, int y){
  return constrain(sqrt((x*x) + (y*y)), 0, 128);
}

