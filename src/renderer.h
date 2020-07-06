#pragma once
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "entity.h"

class Renderer
{

public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height);
    ~Renderer();

    void Render(std::shared_ptr<Entity> player, std::shared_ptr<Entity> bullet);
    SDL_Texture *loadTexture(char const *filename);
    void UpdateWindowTitle(int score, int fps);

private:
    SDL_Window *_sdl_window;
    SDL_Renderer *_sdl_renderer;
    const std::size_t _screen_width;
    const std::size_t _screen_height;
    SDL_Texture *_texture_player;
    SDL_Texture *_texture_bullet;
};

