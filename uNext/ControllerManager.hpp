#ifndef CONTROLLER_MANAGER_H
#define CONTROLLER_MANAGER_H

#include <vector>
#include <SDL2/SDL.h>
#include "Controller.hpp"

class ControllerManager {
public:
    ControllerManager(SDL_Event*);
    ~ControllerManager(void);

    Controller& getController(int);
    int getNumControllers();
    void update();

private:
    std::vector<Controller> controllers;
};

#endif
