#ifndef Camera_h
#define Camera_h

#include "Arduino.h"
#include <Thruster.h>

class ThrusterControl {
  public:

    ThrusterControl();
    void update();
    void passUserInput(int x, int y, int z, int rot);
    void headingApplied();
    void depthApplied();
    
  private:
    
    Thruster* m_ThrusterL;
    Thruster* m_ThrusterR;
    Thruster* m_ThrusterVert;
    Thruster* m_ThrusterLat;

    bool headingApplied;
    bool depthApplied;

    int m_x;
    int m_y;
    int m_z;
    int m_rot;

    int m_threshold = 30; // adjust this to set how far you need to push the stick before the rov begins to move.
};

#endif
