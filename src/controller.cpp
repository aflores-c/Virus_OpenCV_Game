#include "controller.h"

Controller::Controller()
{
    _track_object = nullptr;
}
Controller::Controller(std::shared_ptr<Tracking> track_object)
{
    _track_object = track_object;
}

void Controller::HandleInput(std::shared_ptr<Player> player) const
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            doKeyDown(&event.key, player);
            break;

        case SDL_KEYUP:
            doKeyUp(&event.key, player);
            break;

        default:
            break;
        }
    }
}

void Controller::doKeyDown(SDL_KeyboardEvent *event, std::shared_ptr<Player> player) const
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            player->up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            player->down = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            player->left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            player->right = 1;
        }

        if(event->keysym.scancode == SDL_SCANCODE_ESCAPE)
        {
            exit(0);
        }
    }
}

void Controller::doKeyUp(SDL_KeyboardEvent *event, std::shared_ptr<Player> player) const
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            player->up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            player->down = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            player->left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            player->right = 0;
        }
    }
}

void Controller::HandleInputTracking( std::shared_ptr<Player> player) const
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_KEYDOWN:
            doKeyDown(&event.key, player);
            break;

        case SDL_KEYUP:
            doKeyUp(&event.key, player);
            break;

        default:
            break;
        }
    }

    if (_track_object->getX_position() > player->x)
    {
        player->left = 0;
        player->right = 1;
        std::cout << "going right\n";
    }

    else if (_track_object->getX_position() < player->x)
    {
        player->right = 0;
        player->left = 1;
        std::cout << "going left\n";
    }

    else
    {
        player->right = 0;
        player->left = 0;
    }
}