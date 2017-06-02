
#include "ThrusterControl.h"
#include <Wire.h>
#include "Camera.h"

// declare components in global scope
Camera* m_camera;
ThrusterControl* m_thrusterControl;

void setup() {

  // instantiate components
  m_cam = new Camera(50, 51);
  m_thrusterControl = new ThrusterControl();

  // wire configuration
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);           // start serial for output
  delay(1000);
}

void loop() {
  m_thrusterControl->update();
  m_camera->update();
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  //Serial.println("Receiving... ");
  
  int x = Wire.read();
  int y = Wire.read();
  int z = Wire.read();
  ThrusterControl->passUserInput(x, y, z);
  
  wire_light = Wire.read();
  
  int cam_x = Wire.read();
  int cam_y = Wire.read();
  Camera->passUserInput(cam_x, cam_y);
}

