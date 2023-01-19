#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Controller.hpp"

class GameController: public virtual Controller {
public:
    using Controller::Controller;
    enum CONTROLLER_EVENT getKey();
    bool isKeyUp();
    bool isKeyDown();
};

#endif
