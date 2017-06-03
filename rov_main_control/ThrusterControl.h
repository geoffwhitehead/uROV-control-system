#ifndef ThruserControl_h
#define ThrusterControl_h

#include "Arduino.h"
#include "Component.h"
#include "Thruster.h"

class ThrusterControl: public Component{
  public:
	ThrusterControl();
	~ThrusterControl();
    void update();
    void passUserInput(int x, int y, int z, int rot);
    
  private: 
    Thruster* m_thrusterL;
    Thruster* m_thrusterR;
    Thruster* m_thrusterVert;
    Thruster* m_thrusterLat;

    bool headingApplied;
    bool depthApplied;

    int m_x;
    int m_y;
    int m_z;
    int m_rot;

    int m_threshold = 30; // adjust this to set how far you need to push the stick before the rov begins to move.

	void adjustHeading();
	void adjustDepth();
	int adjustToThreshold(int);
};

#endif
