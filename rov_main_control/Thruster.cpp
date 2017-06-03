/*
  Thruster.cpp - Class for controlling ROV Thruster
*/

#include "Thruster.h"

Thruster::Thruster(int RPWM, int LPWM, int L_EN, int R_EN){
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

Thruster::Thruster(int escPin, int escWrite){
  esc.attach(escPin);
  esc.writeMicroseconds(escWrite);
  isBrushed = false;
}

void Thruster::applyThrust(int thrust){
  if (isBrushed) {
    if (thrust < 0) {
      analogWrite(m_RPWM, 0);
      analogWrite(m_LPWM, abs(thrust));
    } else {
      analogWrite(m_RPWM, abs(thrust));
      analogWrite(m_LPWM, 0);
    }
  } else {
    esc.writeMicroseconds(thrust); 
  }
  
}

void Thruster::activate(){
  if (isBrushed){
    digitalWrite(m_L_EN, HIGH);
    digitalWrite(m_R_EN, HIGH);
  }
}

void Thruster::deactivate(){
  if (isBrushed){
    digitalWrite(m_L_EN, LOW);
    digitalWrite(m_R_EN, LOW);
  }
}

