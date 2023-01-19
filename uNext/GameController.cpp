#include "GameController.hpp"

enum CONTROLLER_EVENT GameController::getKey() {
    uint8_t kCode = this->event->cbutton.button;

    if (kCode == SDL_CONTROLLER_BUTTON_DPAD_UP) return BUTTON_UP;
    if (kCode == SDL_CONTROLLER_BUTTON_DPAD_DOWN) return BUTTON_DOWN;
    if (kCode == SDL_CONTROLLER_BUTTON_DPAD_LEFT) return BUTTON_LEFT;
    if (kCode == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) return BUTTON_RIGHT;

    if (kCode == SDL_CONTROLLER_BUTTON_START) return BUTTON_START;
    if (kCode == SDL_CONTROLLER_BUTTON_BACK) return BUTTON_BACK;

    if (kCode == SDL_CONTROLLER_BUTTON_X || kCode == SDL_CONTROLLER_BUTTON_Y) return BUTTON_A;
    if (kCode == SDL_CONTROLLER_BUTTON_A || kCode == SDL_CONTROLLER_BUTTON_B) return BUTTON_B;

    return BUTTON_NONE;
}

bool GameController::isKeyUp() {
    return this->event->type == SDL_CONTROLLERBUTTONUP;
}

bool GameController::isKeyDown() {
    return this->event->type == SDL_CONTROLLERBUTTONDOWN;
}
