
#include "ThrusterControl.h"
#include <Wire.h>
#include "Camera.h"
#include "Component.h"
#include "Light.h"
#include <Servo.h>

// declare components in global scope
Camera* m_camera;
ThrusterControl* m_thrusterControl;
Light* m_lightLow;
Light* m_lightHigh;

// add components to array
Component* components[] = {
	m_camera,
	m_thrusterControl,
	m_lightLow,
	m_lightHigh
};

void setup() {

  // instantiate components
  m_camera = new Camera(50, 51);
  m_thrusterControl = new ThrusterControl();
  m_lightLow = new Light(49);
  m_lightHigh = new Light(48);


  
  // wire configuration
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);           // start serial for output
  delay(1000);
}

void loop() {
	for (int i = 0; i < 4; i++) {
    components[i]->update();
  }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  //Serial.println("Receiving... ");
  
  int x = Wire.read();
  int y = Wire.read();
  int z = Wire.read();
  int rot = Wire.read();
  m_thrusterControl->passUserInput(x, y, z, rot);
  
  int camX = Wire.read();
  int camY = Wire.read();
  m_camera->passUserInput(camX, camY);

  int lightLow = Wire.read();
  m_lightLow->passUserInput(lightLow);

  int lightHigh = Wire.read();
  m_lightHigh->passUserInput(lightHigh);
}

