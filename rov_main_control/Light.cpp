/*
  Light.cpp - Class for controlling an ROV light set
*/

#include "Light.h"

Light::Light(int pin) {
	pinMode(0, OUTPUT);
	digitalWrite(pin, 0);
	
	m_pin = pin;
	m_state = 0;
}

void Light::update() {
	if (!stateApplied) {
		digitalWrite(m_pin, m_state);
		stateApplied == true;
	}
}

void Light::passUserInput(int state) {
	m_state = state;
	stateApplied = false;
}