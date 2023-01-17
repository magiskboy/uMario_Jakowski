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
        Controller(SDL_Event*);
        ~Controller(void);

        virtual enum CONTROLLER_EVENT getKeyUp();
        virtual enum CONTROLLER_EVENT getKeyDown();
        virtual bool isKeyUp();
        virtual bool isKeyDown();

    private:
        SDL_Event* event;
        SDL_GameController* gGameController;
        SDL_Joystick* gJoyStick;
};

#endif
