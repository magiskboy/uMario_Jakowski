#include "KeyboardController.hpp"
#include "CFG.h"

enum CONTROLLER_EVENT KeyboardController::getKey() {
    SDL_Keycode kCode = this->event->key.keysym.sym;

    if (kCode == CCFG::keyIDA || kCode == SDLK_LEFT) return BUTTON_LEFT;
    if (kCode == CCFG::keyIDS || kCode == SDLK_DOWN) return BUTTON_DOWN;
    if (kCode == CCFG::keyIDD || kCode == SDLK_RIGHT) return BUTTON_RIGHT;
    if (kCode == SDLK_w || kCode == SDLK_UP) return BUTTON_UP;

    if (kCode == SDLK_RETURN) return BUTTON_START;
    if (kCode == SDLK_ESCAPE) return BUTTON_BACK;

    if (kCode == CCFG::keyIDShift) return BUTTON_A;
    if (kCode == CCFG::keyIDSpace) return BUTTON_B;

    return BUTTON_NONE;
}

bool KeyboardController::isKeyUp() {
    return this->event->type == SDL_KEYUP;
}

bool KeyboardController::isKeyDown() {
    return this->event->type == SDL_KEYDOWN;
}
