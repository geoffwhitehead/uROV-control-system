#ifndef Thruster_h
#define Thruster_h

#include "Arduino.h"
#include <Servo.h>

class Thruster {
  public:

    Thruster(int RPWM, int LPWM, int L_EN, int R_EN);
    Thruster(int escPin, int escWrite);
    void applyThrust(int thrust);
    void activate();
    void deactivate();
    
  private:
  
    int m_RPWM;
    int m_LPWM;
    int m_L_EN;
    int m_R_EN;
    Servo esc;
    bool isBrushed = true;
};

#endif
