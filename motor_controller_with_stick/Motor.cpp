/*
  Motor.cpp - Simple class for controlling ROV motors
*/

#include "Motor.h"

Motor::Motor(int RPWM, int LPWM, int L_EN, int R_EN){
  
  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);
  digitalWrite(RPWM, LOW);
  digitalWrite(LPWM, LOW);
  digitalWrite(L_EN, LOW);
  digitalWrite(R_EN, LOW);

  m_RPWM = RPWM;
  m_LPWM = LPWM;
  m_L_EN = L_EN;
  m_R_EN = R_EN;
  
} 

void Motor::applyThrust(int thrust){
  if (thrust < 0) {
    analogWrite(m_RPWM, 0);
    analogWrite(m_LPWM, abs(thrust));
  } else {
    analogWrite(m_RPWM, abs(thrust));
    analogWrite(m_LPWM, 0);
  }
}

void Motor::activateMotor(){
  //digitalWrite(m_RPWM, HIGH);
  //digitalWrite(m_LPWM, HIGH);
  digitalWrite(m_L_EN, HIGH);
  digitalWrite(m_R_EN, HIGH);
}

void Motor::deactivateMotor(){
 /// digitalWrite(m_RPWM, LOW);
 // digitalWrite(m_LPWM, LOW);
  digitalWrite(m_L_EN, LOW);
  digitalWrite(m_R_EN, LOW);
}

