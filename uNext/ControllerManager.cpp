#include "ControllerManager.hpp"
#include "KeyboardController.hpp"
#include "GameController.hpp"
#include <exception>

ControllerManager::ControllerManager(SDL_Event* event) {
    Controller kController(event);
    this->controllers.push_back(kController);
}

ControllerManager::~ControllerManager(void) {
    this->controllers.clear();
}

Controller& ControllerManager::getController(int id) {
    return this->controllers[id];
}

int ControllerManager::getNumControllers() {
    return this->controllers.size();
}

void ControllerManager::update() {
     
}
