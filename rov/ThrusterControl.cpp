/*
  ThrusterControl.cpp - Class for controlling ROV thrusters
*/

ThrusterControl::ThrusterControl(){
    m_thrusterL = new Thruster(3,4,46,47);
    m_thrusterR = new Thruster(5,6,28,29);
    m_thrusterLat = new Thruster(7,8,26,27);
    m_thrusterVert = new Thruster(2, 1000);

    m_thrusterL->activate();
    m_thrusterR->activate();
    m_thrusterLat->activate();
    m_thrusterVert->activate();
} 

void ThrusterControl::update(){
  if(!headingApplied){
    this.adjustHeading();
    headingApplied = true;
  }
  if(!depthApplied){
    this.adjustDepth();
    depthApplied = true;
  }
  
}

void ThrusterControl::passUserInput(int x, int y, int z, int rot){
  m_x = x;
  m_y = y;
  m_z = z;
  m_rot = rot;
  
  headingApplied = false;
  depthApplied = false;
}

int ThrusterControl::checkThreshold(int thrust){
  if(abs(thrust) < m_threshold) {
    return 0;
  }
}

void ThrusterControl::adjustHeading(){

  int x = checkThreshold(m_x);
  int y = checkThreshold(m_y);
  int rot = checkThreshold(m_rot);
  int thrustL;
  int thrustR;
  int thrustLat;

  // Currently values range from 0 -256. Adjust the range so that 0 means the stick is central.
  x = (x - 128) * 2;
  y = (y - 128) * 2;
  rot = (rot - 128) * 2;

  // is the user performing a rotation? If so, adjust the forward thrusters accordingly
  if (rot >= 0){
    thrustL = constrain(y + rot, -254, 254 );
    thrustR = constrain(y - rot, -254, 254 );
  } else {
    thrustL = constrain(y - rot, -254, 254 );
    thrustR = constrain(y + rot, -254, 254 );   
  }

  thrustLat = constrain(x, -254, 254);

  m_thrusterL->applyThrust(thrustL);
  m_thrusterR->applyThrust(thrustR);
  m_thrusterLat->applyThrust(thrustLat);
}

//TODO finish this function  - need to work out how to reservse direction on brushless motor
void ThrusterControl::adjustDepth(){
  int val = map(z, 0, 254, 1000, 2000);
  m_thrusterVert->applyThrust(val); 
}
