#include "Renderer.h"

Renderer::Renderer()
{
    std::cout << "Renderer constructor" << std::endl;
    this->init();
    this->loadMedia();
}

Renderer::~Renderer()
{
    TTF_CloseFont(font);
    font = NULL;

    SDL_DestroyWindow(window);
    window = NULL;

    SDL_DestroyRenderer(render);
    render = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool Renderer::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Can't init SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow("Eternal life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "Can't create window: " << SDL_GetError() << std::endl;
        return false;
    }

    render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (render == NULL) {
        std::cout << "Can't create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    //Initialize renderer color
    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

    //Initialize PNG loading
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    //Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    std::cout << "Success init renderer" << std::endl;

    return true;
}

bool Renderer::loadMedia()
{
    font = TTF_OpenFont("fonts/lazy.ttf", 28);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }

    return true;
}

void Renderer::renderFrame(bool grid[][WORLD_HEIGHT])
{
    // Clear frame
    SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(render);

    SDL_SetRenderDrawColor(render, 0xFF, 0xFF, 0xFF, 0xFF);

    int cellSize = round(SCREEN_HEIGHT / WORLD_HEIGHT);
    
    for (int x = 0; x < WORLD_WIDTH; x++) {
        for (int y = 0; y < WORLD_HEIGHT; y++) {
            if (grid[x][y] == 1) {
                SDL_Rect* location;
                location = new SDL_Rect;
                location->x = x * cellSize;
                location->y = y * cellSize;
                location->w = cellSize;
                location->h = cellSize;

                SDL_RenderFillRect(render, location);
                delete location;
            }
        }
    }

    this->drawFps();

    SDL_RenderPresent(render);
}

void Renderer::setFps(int avgFps)
{
    fps = avgFps;
}

void Renderer::drawFps()
{
    std::stringstream timeText;
    timeText.str("");
    timeText << "FPS: " << this->fps;

    SDL_Color color{ 0, 0, 255 };

    if (!this->text(timeText.str(), SCREEN_WIDTH - 80, 20, &color))
    {
        printf("Unable to render FPS texture!\n");
    }

}

bool Renderer::text(std::string textToRender, int x, int y, SDL_Color* color)
{
    SDL_Surface* text;

    text = TTF_RenderText_Solid(font, textToRender.c_str(), *color);
    if (!text) {
        std::cout << "Failed to render text: " << TTF_GetError() << std::endl;
        return false;
    }

    SDL_Texture* text_texture;
    text_texture = SDL_CreateTextureFromSurface(render, text);

    SDL_Rect* dest;
    dest = new SDL_Rect;
    dest->x = x - round(text->w / 2);
    dest->y = y - round(text->h / 2);
    dest->w = text->w;
    dest->h = text->h;

    SDL_RendererFlip flip (SDL_FLIP_NONE);

    SDL_RenderCopyEx(render, text_texture, nullptr, dest, 0, nullptr, flip);

    SDL_DestroyTexture(text_texture);
    SDL_FreeSurface(text);
    delete dest;

    return true;
}
