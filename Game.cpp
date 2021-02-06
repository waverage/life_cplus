#include "Game.h"

Game::Game()
{
    std::cout << "Game constructor" << std::endl;
	run = true;
    countedFrames = 0;
}

Game::~Game()
{
	this->shutdown();
}

void Game::loop()
{
    countedFrames = 0;
    fpsTimer.start();

	while (run)
	{
        this->handleEvents();

        runtime.step();

        int fps = this->getAvgFPS();
        if (countedFrames % 10 == 0) {
            std::cout << "FPS: " << fps << endl;
        }
       
        render.setFps(this->getAvgFPS());
        render.renderFrame(runtime.grid);
        ++countedFrames;
	}

    this->shutdown();
}

int Game::getAvgFPS()
{
    float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
    if (avgFPS > 2000000)
    {
        avgFPS = 0;
    }

    return (int)avgFPS;
}

void Game::handleEvents()
{
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            run = false;
        }

        /*if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP) {
            }
            if (event.key.keysym.sym == SDLK_DOWN) {
            }
            if (event.key.keysym.sym == SDLK_RIGHT) {
            }
            if (event.key.keysym.sym == SDLK_LEFT) {
            }
        }*/
    }
}

void Game::shutdown()
{
    std::cout << "Game::shutdown()" << std::endl;
	/*delete& render;
	delete& fpsTimer;*/
}