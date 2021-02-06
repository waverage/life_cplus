#include "Renderer.h"
#include "Timer.h"
#include "Runtime.h"
#include <stdio.h>

#pragma once
class Game
{
public:
	Game();
	~Game();

	void loop();
	void shutdown();
	int getAvgFPS();

private:
	Renderer render;
	Timer fpsTimer;
	SDL_Event event;
	Runtime runtime;

	int countedFrames = 0;
	bool run;

	void handleEvents();
};

