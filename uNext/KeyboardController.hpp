#ifndef KEYBOARD_CONTROLLER_H
#define KEYBOARD_CONTROLLER_H

#include "Controller.hpp"

class KeyboardController: public virtual Controller {
public:
    using Controller::Controller;
    enum CONTROLLER_EVENT getKey();
    bool isKeyUp();
    bool isKeyDown();
};

#endif
