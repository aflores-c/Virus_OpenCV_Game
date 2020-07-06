#pragma once

#include <random>
#include <iostream>
#include <thread>
#include <memory>
#include <cmath>
#include "SDL2/SDL.h"
#include "controller.h"
#include "renderer.h"
#include "entity.h"
#include "tracking.h"

class Game
{
public:
    Game(std::size_t kScreenWidth, std::size_t kScreenHeight);
    void Run(Controller const &controller, Renderer &renderer,
              std::size_t target_frame_duration, int mode);

private:
    std::shared_ptr<Player> _player;
    std::shared_ptr<Entity> _virus;
    std::size_t _kScreenWidth;
    std::size_t _kScreenHeight;
    std::random_device _dev;
    std::mt19937 _engine;
    std::uniform_int_distribution<int> _random_x;
    int _score{0};
    int _mode{1};

    float distance(int x1, int y1, int x2, int y2);
    void Update();
};