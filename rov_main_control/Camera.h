#ifndef Camera_h
#define Camera_h

#include "Arduino.h"
#include "Component.h"
#include "Servo.h"

class Camera: public Component {
  public:
    Camera(int servo_tilt, int servo_pan);
    void updateCamPosition();
    void update();
    void passUserInput(int x, int y);
    
  private:
    Servo m_pan;
    Servo m_tilt;
    int m_x;
    int m_y;
    int scalingFactor = 2; // set this to adjust the camera movement speed
    int offset = 3; // this is based on the range of values sent from the surface controller. It needs to 
                    // be half of the max value. This will result in negative values for bottom half of range
                    // resulting in negative movement
    bool viewApplied = true; // start true because no defaulyt values assigned for m_x and m_y
};

#endif
