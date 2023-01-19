#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <SDL2/SDL.h>

enum CONTROLLER_EVENT {
    BUTTON_LEFT,
    BUTTON_RIGHT,
    BUTTON_UP,
    BUTTON_DOWN,
    BUTTON_START,
    BUTTON_BACK,
    BUTTON_A,
    BUTTON_B,
    BUTTON_NONE
};

class Controller {
    public:
        Controller(SDL_Event* event);
        ~Controller(void);

        enum CONTROLLER_EVENT getKey();
        bool isKeyUp();
        bool isKeyDown();

    protected:
        SDL_Event* event;
        SDL_GameController* gGameController;
        SDL_Joystick* gJoyStick;
};

#endif
