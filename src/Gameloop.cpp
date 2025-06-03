#include "Gameloop.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Screen.hpp"
#include "stage/ObjectPlacementStage.hpp"
#include "LevelSetup.hpp"
#include "stage/MainMenuStage.hpp"


void gameloop() {
    register_sprites();

    Screen screen(720, 720);
    Camera camera(0,0,0.3);
    StateMachine state_machine(std::make_unique<MainMenuStage>(state_machine, &screen, &camera));

    screen.createWindow();

    auto prev_time = std::chrono::steady_clock::now();

    long long int frames = 0;
    while (!state_machine.shutdown) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));
        frames++;
        auto now_time = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now_time - prev_time).count() >= 1) {
            std::cout << "FPS: " << frames << std::endl;
            prev_time = std::chrono::steady_clock::now();
            frames = 0;
        }

        screen.getWindow()->clear();

        state_machine.update();

        // debug_lines(screen.getWindow());

        screen.getWindow()->display();
    }
    screen.destroyWindow();
    TextureLoader::clear();
    SimulationObjectFactory::clear();
    std::cout << "Exiting..." << std::endl;
}
