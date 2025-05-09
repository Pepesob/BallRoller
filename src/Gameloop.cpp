#include "Gameloop.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>

#include "Screen.hpp"
#include "DrawingEngine.hpp"
#include "ObjectPlacementStage.hpp"
#include "LevelSetup.hpp"


void saveCurrentWorld(const std::vector<SimulationSprite> &objects, const std::string &filename) {
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "setupObjects" << YAML::BeginSeq;
    for (const auto obj : objects) {
        out << obj.object->config;
    }
    std::ofstream fout(filename);
    fout << out.c_str();
}

// TODO - implement state machine that changes game stages eg. LevelChoosingStage -> ObjectPlacementStage -> SimulationStage
void gameloop() {
    register_sprites();

    Screen screen(720, 720);
    Camera camera(0,0,0.3);
    B2dSimulation simulation({0, -6.0f});

    Level level("resources/level1234.yaml");

    ObjectPlacementStage placement_stage(level, &screen, &camera);

    level.level_setup->place(simulation);
    screen.createWindow();

    auto start = std::chrono::steady_clock::now();
    auto prev_time = std::chrono::steady_clock::now();

    int state = 0;

    long long int frames = 0;

    sf::Vector2i prev = sf::Mouse::getPosition(*screen.getWindow());
    while (true) {
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


        sf::Vector2i current = sf::Mouse::getPosition(*screen.getWindow());
        if (state == 0) {
            placement_stage.keyboardInput(simulation);
        }
        else {
            simulation.fixedStep();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && state == 0) {
            // level.available_objects->addToSimulation(simulation);
            state = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sf::Vector2f dx = sf::Vector2f(prev - current);
            camera.move(dx.x/screen.getPixelScaleFactor(), -dx.y/screen.getPixelScaleFactor());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.setDeltaZoom(1.001);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.setDeltaZoom(0.999);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            saveCurrentWorld(level.available_objects->placed_objects, "resources/mysetup4.yaml");
            // level.available_objects->save("resources/Level12345.yaml");
            break;
        }

        level.level_setup->draw(&screen, &camera);

        debug_lines(screen.getWindow());

        screen.getWindow()->display();

        prev = current;

        if (simulation.goalReached == true) {
            break;
        }
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

}
