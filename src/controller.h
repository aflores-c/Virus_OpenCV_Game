
#pragma once

#include "entity.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "tracking.h"
#include <memory>

class Controller
{

public:
    Controller();
    Controller(std::shared_ptr<Tracking> track_object);
    void HandleInput(std::shared_ptr<Player> player) const;
    void HandleInputTracking(std::shared_ptr<Player> player) const;
    void doKeyDown(SDL_KeyboardEvent *event, std::shared_ptr<Player> player) const;
    void doKeyUp(SDL_KeyboardEvent *event, std::shared_ptr<Player> player) const;

private:
    std::shared_ptr<Tracking> _track_object;
    void ReadTracking();
    
};