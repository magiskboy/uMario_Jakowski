#pragma once

#ifndef CORE_H
#define CORE_H

#include "Map.h"
#include "Controller.h"

class CCore
{
private:
	SDL_Window* window;
	SDL_Renderer* rR;
	SDL_Event* mainEvent;
    Controller* controller;

	// ----- FPS -----

	long frameTime;
	static const int MIN_FRAME_TIME = 16;

	unsigned long lFPSTime;
	int iNumOfFPS, iFPS;

	// ----- FPS -----

	// ----- INPUT
	static bool movePressed, keyMenuPressed, keyDown, keyUp, keyLeft, keyRight, keyButtonA;

	static bool keyLeftPressed, keyRightPressed;
	// ----- true = RIGHT, false = LEFT
	bool firstDir;

	// ----- INPUT

	static Map* oMap;

	// ----- Methods

	void Input();
	void MouseInput();
	void InputPlayer();
	void InputMenu();
public:
	CCore(void);
	~CCore(void);

	static bool quitGame;

	void mainLoop();

	void Update();
	void Draw();

	void resetMove();
	static void resetKeys();

	static bool mouseLeftPressed, mouseRightPressed;
	static int mouseX, mouseY;
	
	/* ----- get & set ----- */
	static Map* getMap();
    
    Controller* getController();
};

#endif
