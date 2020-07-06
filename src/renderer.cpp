#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : _screen_width(screen_width),
      _screen_height(screen_height)
{

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }

    //Create a window
    _sdl_window = SDL_CreateWindow("CORONAVIRUS_GAME", // creates a window
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  _screen_width, _screen_height, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    //Creates a renderer to render our images
    _sdl_renderer = SDL_CreateRenderer(_sdl_window, -1, render_flags);

    //Load texture from images
    _texture_player = loadTexture("../images/entity.png");
    _texture_bullet = loadTexture("../images/virus.png");
}

Renderer::~Renderer()
{
    SDL_DestroyWindow(_sdl_window);
    SDL_Quit();
}

void Renderer::Render(std::shared_ptr<Entity> player, std::shared_ptr<Entity> virus)
{

    SDL_Rect dest;

    // Clear screen
    SDL_SetRenderDrawColor(_sdl_renderer, 96, 128, 255, 255);
    SDL_RenderClear(_sdl_renderer);

    //Render player
    dest.x = player->x;
    dest.y = player->y;
    SDL_QueryTexture(_texture_player, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopy(_sdl_renderer, _texture_player, NULL, &dest);

    //Render virus
    if (virus->health > 0)
    {
        dest.x = virus->x;
        dest.y = virus->y;
        SDL_QueryTexture(_texture_bullet, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(_sdl_renderer, _texture_bullet, NULL, &dest);
    }

    //Update screen
    SDL_RenderPresent(_sdl_renderer);
}

SDL_Texture *Renderer::loadTexture(char const *filename)
{
    SDL_Texture *texture;
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
    texture = IMG_LoadTexture(_sdl_renderer, filename);

    return texture;
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(_sdl_window, title.c_str());
}
