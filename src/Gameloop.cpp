#include "Gameloop.hpp"

#include <iostream>

#include "Screen.hpp"
#include "DrawingEngine.hpp"
#include "ObjectPlacementStage.hpp"
#include <thread>
#include <chrono>

#include "LevelSetup.hpp"
#include "YamlConfigurationLoader.hpp"


void gameloop() {

    std::cout << std::filesystem::current_path() << std::endl;

    YamlConfigurationLoader loader;

    loader.loadYaml("./resources/Level1.yaml");
    // Screen screen(720, 720);
    // Camera camera(0,0,0.3);
    // B2dSimulation simulation({0, -6.0f});
    // LevelSetup level_setup;
    // ObjectPlacementStage placement_stage(&screen, &camera);
    //
    // level_setup.place(simulation);
    // screen.createWindow();
    //
    // // auto start = std::chrono::steady_clock::now();
    //
    // int state = 0;
    //
    // sf::Vector2i prev = sf::Mouse::getPosition(*screen.getWindow());
    // while (true) {
    //     // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));
    //
    //     screen.handleWindowEvents();
    //     camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
    //     screen.getWindow()->clear();
    //
    //
    //
    //
    //     sf::Vector2i current = sf::Mouse::getPosition(*screen.getWindow());
    //     if (state == 0) {
    //         placement_stage.keyboardInput(simulation);
    //         placement_stage.draw(&screen, &camera);
    //     }
    //     else {
    //         simulation.fixedStep();
    //     }
    //
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
    //         state = 1;
    //     }
    //     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    //         sf::Vector2f dx = sf::Vector2f(prev - current);
    //         camera.move(dx.x/screen.getPixelScaleFactor(), -dx.y/screen.getPixelScaleFactor());
    //     }
    //     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    //         camera.setDeltaZoom(0.999);
    //     }
    //     else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    //         camera.setDeltaZoom(1.001);
    //     }
    //
    //
    //     simulation.draw(&screen, &camera);
    //
    //     debug_lines(screen.getWindow());
    //
    //     screen.getWindow()->display();
    //
    //     prev = current;
    // }

    // auto end = std::chrono::steady_clock::now();
    //
    // std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

}
