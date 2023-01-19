#include "Controller.hpp"
#include "CFG.h"

Controller::Controller(SDL_Event* event) {
    this->event = event;

    if (SDL_NumJoysticks() > 0) {
        this->gJoyStick = SDL_JoystickOpen( 0 );
        this->gGameController = SDL_GameControllerOpen( 0 );
    }
}

Controller::~Controller(void) {
    if (this->gGameController)
        SDL_GameControllerClose(this->gGameController);

    if (this->gJoyStick) 
        SDL_JoystickClose(this->gJoyStick);
    
}

enum CONTROLLER_EVENT Controller::getKey() {}
bool Controller::isKeyUp() {}
bool Controller::isKeyDown() {}
