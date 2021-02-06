#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Const.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <sstream>

#pragma once
class Renderer
{
public:
	Renderer();
	~Renderer();

	bool init();
	void renderFrame(bool grid[WORLD_WIDTH][WORLD_HEIGHT]);
	bool text(std::string textToRender, int x, int y, SDL_Color* color);
	void drawFps();
	void setFps(int avgFps);

private:
	SDL_Window* window;
	SDL_Renderer* render;
	TTF_Font* font = NULL;
	int fps;

	bool loadMedia();
};

