#ifndef Light_h
#define Light_h

#include "Arduino.h"
#include "Component.h"

class Light: public Component {
  public:
    Light(int pin);
    void update();
    void passUserInput(int state);
  private:
    int m_state;
    int m_pin;
    bool stateApplied = true;
};

#endif
