#include "Gameloop.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Screen.hpp"
#include "stage/ObjectPlacementStage.hpp"
#include "LevelSetup.hpp"
#include "stage/SimulationStage.hpp"


void saveCurrentWorld(const std::vector<SimulationSprite> &objects, const std::string &filename) {
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "setupObjects" << YAML::BeginSeq;
    for (const auto obj : objects) {
        out << obj.object->config;
    }
    std::ofstream fout(filename);
    fout << out.c_str();
}

void gameloop() {
    register_sprites();

    Screen screen(720, 720);
    Camera camera(0,0,0.3);
    Level level("resources/level1234.yaml");
    StateMachine state_machine;
    state_machine.setInitialState(new ObjectPlacementStage(state_machine, level, &screen, &camera));

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

        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        state_machine.update();

        debug_lines(screen.getWindow());

        screen.getWindow()->display();
    }
    screen.destroyWindow();
    std::cout << "Exiting..." << std::endl;
}
