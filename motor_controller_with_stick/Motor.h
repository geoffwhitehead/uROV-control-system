#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor {
  public:

    Motor(int RPWM, int LPWM, int L_EN, int R_EN);
    void applyThrust(int thrust);
    void activateMotor();
    void deactivateMotor();
    
  private:
  
    int m_RPWM;
    int m_LPWM;
    int m_L_EN;
    int m_R_EN;
};

#endif
