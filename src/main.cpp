
#include <iostream>
#include <memory>
#include "renderer.h"
#include "controller.h"
#include "game.h"
#include "tracking.h"

int main()
{
    constexpr std::size_t kFramesPerSecond{60};
    constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
    constexpr std::size_t kScreenWidth{720};
    constexpr std::size_t kScreenHeight{720};

    int mode;

    do
    {
        std::cout << "Choose the game mode: \n ";
        std::cout << "(1) Manual mode \n";
        std::cout << "(2) Traking mode \n";
        std::cin >> mode;
        std::cout << "Running Mode: " << mode << std::endl;
    } while ((mode != 1) && (mode != 2));

    if (mode == 1)
    {
        Renderer renderer(kScreenWidth, kScreenHeight);
        Game game(kScreenWidth, kScreenHeight);
        Controller controller;
        game.Run(controller, renderer, kMsPerFrame, mode);
    }

    else if (mode == 2)
    {
        Renderer renderer(kScreenWidth, kScreenHeight);
        Game game(kScreenWidth, kScreenHeight);
        auto track_object = std::make_shared<Tracking>(kScreenWidth, kScreenHeight);
        Controller controller(track_object);
        std::thread t1 = std::thread(&Tracking::tracking_color, track_object);
        game.Run(controller, renderer, kMsPerFrame, mode);
        std::vector<int> messi;
        t1.join();
    }

    return 0;
}
