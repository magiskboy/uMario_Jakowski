#include "Controller.h"
#include "CFG.h"

CONTROLLER_EVENT getEventFromKeyboard(SDL_Event*);
CONTROLLER_EVENT getEventFromGameController(SDL_Event*);

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

CONTROLLER_EVENT Controller::getKeyUp() {
    if (this->event->type == SDL_KEYUP) return getEventFromKeyboard(this->event);
    if (this->event->type == SDL_CONTROLLERBUTTONUP) return getEventFromGameController(this->event);
    return BUTTON_NONE;
}

CONTROLLER_EVENT Controller::getKeyDown() {
    if (this->event->type == SDL_KEYDOWN) return getEventFromKeyboard(this->event);
    if (this->event->type == SDL_CONTROLLERBUTTONDOWN) return getEventFromGameController(this->event);
    return BUTTON_NONE;
}

bool Controller::isKeyUp() {
    return this->event->type == SDL_KEYUP || this->event->type == SDL_CONTROLLERBUTTONUP;
}

bool Controller::isKeyDown() {
    return this->event->type == SDL_KEYDOWN || this->event->type == SDL_CONTROLLERBUTTONDOWN;
}

CONTROLLER_EVENT getEventFromGameController(SDL_Event* event) {
    uint8_t key_code = event->cbutton.button;

    if (key_code == SDL_CONTROLLER_BUTTON_DPAD_UP) return BUTTON_UP;
    if (key_code == SDL_CONTROLLER_BUTTON_DPAD_DOWN) return BUTTON_DOWN;
    if (key_code == SDL_CONTROLLER_BUTTON_DPAD_LEFT) return BUTTON_LEFT;
    if (key_code == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) return BUTTON_RIGHT;

    if (key_code == SDL_CONTROLLER_BUTTON_START) return BUTTON_START;
    if (key_code == SDL_CONTROLLER_BUTTON_BACK) return BUTTON_BACK;

    if (key_code == SDL_CONTROLLER_BUTTON_X || key_code == SDL_CONTROLLER_BUTTON_Y) return BUTTON_A;
    if (key_code == SDL_CONTROLLER_BUTTON_A || key_code == SDL_CONTROLLER_BUTTON_B) return BUTTON_B;

    return BUTTON_NONE;
}

CONTROLLER_EVENT getEventFromKeyboard(SDL_Event* event) {
    SDL_Keycode key_code = event->key.keysym.sym;

    if (key_code == CCFG::keyIDA) return BUTTON_LEFT;
    if (key_code == CCFG::keyIDS) return BUTTON_DOWN;
    if (key_code == CCFG::keyIDD) return BUTTON_RIGHT;

    if (key_code == CCFG::keyIDShift) return BUTTON_A;
    if (key_code == CCFG::keyIDSpace) return BUTTON_B;

    return BUTTON_NONE;
}
