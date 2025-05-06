#include "Gameloop.hpp"

#include <iostream>

#include "Screen.hpp"
#include "DrawingEngine.hpp"
#include "ObjectPlacementStage.hpp"
#include <thread>
#include <chrono>

#include "LevelSetup.hpp"


void gameloop() {

    std::cout << std::filesystem::current_path() << std::endl;

    Screen screen(720, 720);
    Camera camera(0,0,0.3);
    B2dSimulation simulation({0, -6.0f});
    Level level("resources/Level123.yaml");
    ObjectPlacementStage placement_stage(*level.available_objects,&screen, &camera);

    level.level_setup->place(simulation);
    screen.createWindow();

    auto start = std::chrono::steady_clock::now();

    int state = 0;

    sf::Vector2i prev = sf::Mouse::getPosition(*screen.getWindow());
    while (true) {
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));

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
            level.available_objects->addToSimulation(simulation);
            state = 1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            sf::Vector2f dx = sf::Vector2f(prev - current);
            camera.move(dx.x/screen.getPixelScaleFactor(), -dx.y/screen.getPixelScaleFactor());
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            camera.setDeltaZoom(0.999);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            camera.setDeltaZoom(1.001);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            // saveCurrentWorld(simulation.objects, "resources/mysetup3.yaml");
            level.available_objects->save("resources/Level123.yaml");
            break;
        }


        debug_lines(screen.getWindow());

        level.draw(&screen, &camera);

        screen.getWindow()->display();

        prev = current;

        if (simulation.goalReached == true) {
            break;
        }
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

}
