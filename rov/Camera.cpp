/*
  Camera.cpp - Class for controlling ROV camera
*/

#include "Camera.h"

Camera::Camera(int pin_servo_tilt, int pin_servo_pan){
  m_tilt.attach(pin_servo_tilt);
  m_pan.attach(pin_servo_pan);
} 

void Camera::update(){
  if(!viewApplied){
    this.updateCamPosition();
    viewApplied = true;
  }
}

void Camera::passUserInput(int x, int y){
  m_x = x;
  m_y = y;
  viewApplied = false;
}

void Camera::updateCamPos(){
  m_pan.write(m_pan.read() + ((m_x - offset) * scalingFactor));
  m_tilt.write(m_tilt.read() + ((m_y - offset) * scalingFactor));
}
