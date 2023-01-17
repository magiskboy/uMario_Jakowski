#include "Controller.h"
#include "header.h"
#include "Core.h"
#include "IMG.h"
#include "CFG.h"
#include "Text.h"
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdio.h>

/* ******************************************** */

Map* CCore::oMap = new Map();
bool CCore::mouseLeftPressed = false;
bool CCore::mouseRightPressed = false;
int CCore::mouseX = 0;
int CCore::mouseY = 0;
bool CCore::quitGame = false;

bool CCore::movePressed = false;
bool CCore::keyMenuPressed = false;
bool CCore::keyS = false;
bool CCore::keyW = false;
bool CCore::keyA = false;
bool CCore::keyD = false;
bool CCore::keyShift = false;
bool CCore::keyAPressed = false;
bool CCore::keyDPressed = false;

CCore::CCore(void) {
	this->quitGame = false;
	this->iFPS = 0;
	this->iNumOfFPS = 0;
	this->lFPSTime = 0;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
	
	window = SDL_CreateWindow("uMario - www.LukaszJakowski.pl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, CCFG::GAME_WIDTH, CCFG::GAME_HEIGHT, SDL_WINDOW_SHOWN);

	if(window == NULL) {
		quitGame = true;
	}

	rR = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	// ----- ICO
	std::string fileName = "files/images/ico.bmp";
	SDL_Surface* loadedSurface = SDL_LoadBMP(fileName.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 0, 255));

	SDL_SetWindowIcon(window, loadedSurface);
	SDL_FreeSurface(loadedSurface);

	mainEvent = new SDL_Event();

    this->controller = new Controller(mainEvent);
	// ----- ICO
	
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	
	oMap = new Map(rR);
	CCFG::getMM()->setActiveOption(rR);
	CCFG::getSMBLOGO()->setIMG("super_mario_bros", rR);

	CCFG::getMusic()->PlayMusic();

	this->keyMenuPressed = this->movePressed = this->keyS = this->keyW = this->keyA = this->keyD = this->keyShift = false;

	this->keyAPressed = this->keyDPressed = this->firstDir = false;

	this->mouseX = this->mouseY = 0;

	CCFG::keyIDA = SDLK_a;
	CCFG::keyIDS = SDLK_s;
	CCFG::keyIDD = SDLK_d;
	CCFG::keyIDSpace = SDLK_SPACE;
	CCFG::keyIDShift = SDLK_LSHIFT;
}

CCore::~CCore(void) {
	delete oMap;
	delete mainEvent;
	SDL_DestroyRenderer(rR);
	SDL_DestroyWindow(window);
    SDL_JoystickClose(CCFG::gJoyStick);
}

/* ******************************************** */

void CCore::mainLoop() {
	lFPSTime = SDL_GetTicks();

	while(!quitGame && mainEvent->type != SDL_QUIT) {
		frameTime = SDL_GetTicks();
		SDL_PollEvent(mainEvent);
		SDL_RenderClear(rR);

		CCFG::getMM()->setBackgroundColor(rR);
		SDL_RenderFillRect(rR, NULL);

		Input();
		MouseInput();
		Update();
		Draw();

		SDL_RenderPresent(rR);
		
		if(SDL_GetTicks() - frameTime < MIN_FRAME_TIME) {
			SDL_Delay(MIN_FRAME_TIME - (SDL_GetTicks () - frameTime));
		}
	}
}

void CCore::Input() {
	switch(CCFG::getMM()->getViewID()) {
		case 2: case 7:
			if(!oMap->getInEvent()) {
				InputPlayer();
			} else {
				resetMove();
			}
			break;
		default:
			InputMenu();
			break;
	}
}

void CCore::InputMenu() {
	if(this->controller->isKeyDown()) {
		CCFG::getMM()->setKey(mainEvent->key.keysym.sym);

		switch(this->controller->getKeyDown()) {
            case BUTTON_DOWN:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(2);
					keyMenuPressed = true;
				}
				break;
            case BUTTON_UP: 
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(0);
					keyMenuPressed = true;
				}
				break;
			case BUTTON_START:
				if(!keyMenuPressed) {
					CCFG::getMM()->enter();
					keyMenuPressed = true;
				}
				break;
			case BUTTON_BACK:
				if(!keyMenuPressed) {
					CCFG::getMM()->escape();
					keyMenuPressed = true;
				}
				break;
            case BUTTON_LEFT:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(3);
					keyMenuPressed = true;
				}
				break;
            case BUTTON_RIGHT:
				if(!keyMenuPressed) {
					CCFG::getMM()->keyPressed(1);
					keyMenuPressed = true;
				}
				break;
		}
	}

	if(this->controller->isKeyUp()) {
        keyMenuPressed = false;
    }
}

void CCore::InputPlayer() {
	if(mainEvent->type == SDL_WINDOWEVENT) {
		switch(mainEvent->window.event) {
			case SDL_WINDOWEVENT_FOCUS_LOST:
				CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
				CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
				CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
				CCFG::getMusic()->PauseMusic();
				break;
		}
	}

	if(this->controller->isKeyUp()) {
		if(this->controller->getKeyUp() == BUTTON_RIGHT) {
            if(firstDir) {
                firstDir = false;
            }

            keyDPressed = false;
        }

        if(this->controller->getKeyUp() == BUTTON_DOWN) {
            oMap->getPlayer()->setSquat(false);
            keyS = false;
        }
		
        if(this->controller->getKeyUp() == BUTTON_LEFT) {
            if(!firstDir) {
                firstDir = true;
            }

            keyAPressed = false;
        }
		
        if(this->controller->getKeyUp() == BUTTON_B) {
            CCFG::keySpace = false;
        }
    
        if(this->controller->getKeyUp() == BUTTON_A) {
            if(keyShift) {
                oMap->getPlayer()->resetRun();
                keyShift = false;
            }
        }

        if (this->controller->getKeyUp() == BUTTON_BACK) keyMenuPressed = false;
	}

	if(this->controller->isKeyDown()) {
		if(this->controller->getKeyDown() == BUTTON_RIGHT) {
			keyDPressed = true;
			if(!keyAPressed) {
				firstDir = true;
			}
		}

		if(this->controller->getKeyDown() == BUTTON_DOWN) {
			if(!keyS) {
				keyS = true;
				if(!oMap->getUnderWater() && !oMap->getPlayer()->getInLevelAnimation()) oMap->getPlayer()->setSquat(true);
			}
		}
		
		if(this->controller->getKeyDown() == BUTTON_LEFT) {
			keyAPressed = true;
			if(!keyDPressed) {
				firstDir = false;
			}
		}
		
		if(this->controller->getKeyDown() == BUTTON_B) {
			if(!CCFG::keySpace) {
				oMap->getPlayer()->jump();
				CCFG::keySpace = true;
			}
		}
		
		if(this->controller->getKeyDown() == BUTTON_A) {
			if(!keyShift) {
				oMap->getPlayer()->startRun();
				keyShift = true;
			}
		}

        CONTROLLER_EVENT key_down = this->controller->getKeyDown();
        if (
            key_down == BUTTON_START && 
            !keyMenuPressed
        ) {
            CCFG::getMM()->enter();
            keyMenuPressed = true;
        }
        else if (
            key_down == BUTTON_BACK &&
            !keyMenuPressed && CCFG::getMM()->getViewID() == CCFG::getMM()->eGame
        ) {
            CCFG::getMM()->resetActiveOptionID(CCFG::getMM()->ePasue);
            CCFG::getMM()->setViewID(CCFG::getMM()->ePasue);
            CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPASUE);
            CCFG::getMusic()->PauseMusic();
            keyMenuPressed = true;
        }
	}

	if(keyAPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == false && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(false);
		} else if(!keyDPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(keyDPressed) {
		if(!oMap->getPlayer()->getMove() && firstDir == true && !oMap->getPlayer()->getChangeMoveDirection() && !oMap->getPlayer()->getSquat()) {
			oMap->getPlayer()->startMove();
			oMap->getPlayer()->setMoveDirection(true);
		} else if(!keyAPressed && oMap->getPlayer()->getMoveSpeed() > 0 && firstDir != oMap->getPlayer()->getMoveDirection()) {
			oMap->getPlayer()->setChangeMoveDirection();
		}
	}

	if(oMap->getPlayer()->getMove() && !keyAPressed && !keyDPressed) {
		oMap->getPlayer()->resetMove();
	}
}

void CCore::MouseInput() {
	switch(mainEvent->type) {
		case SDL_MOUSEBUTTONDOWN: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeftPressed = true;
					break;
				case SDL_BUTTON_RIGHT:
					mouseRightPressed = true;
					break;
			}
			break;
		}
		case SDL_MOUSEMOTION: {
			
			SDL_GetMouseState(&mouseX, &mouseY);
			//CCFG::getMM()->getConsole()->print("x:" + std::to_string(mouseX));
			//CCFG::getMM()->getConsole()->print("y:" + std::to_string(mouseY));
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			switch (mainEvent->button.button) {
				case SDL_BUTTON_LEFT:
					mouseLeftPressed = false;
					break;
				case SDL_BUTTON_RIGHT:
					mouseRightPressed = false;
					break;
			}
			break;
		}
		case SDL_MOUSEWHEEL:
			if(mainEvent->wheel.timestamp > SDL_GetTicks() - 2) {
				//CCFG::getMM()->getLE()->mouseWheel(mainEvent->wheel.y);
			}
			break;
	}
}

void CCore::resetKeys() {
	movePressed = keyMenuPressed = keyS = keyW = keyA = keyD = CCFG::keySpace = keyShift = keyAPressed = keyDPressed = false;
}

void CCore::Update() {
	CCFG::getMM()->Update();
}


void CCore::Draw() {
	CCFG::getMM()->Draw(rR);
}

/* ******************************************** */

void CCore::resetMove() {
	this->keyAPressed = this->keyDPressed = false;
}

Map* CCore::getMap() {
	return oMap;
}
