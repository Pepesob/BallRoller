#include "Gameloop.hpp"

#include "AccelerationFieldDrawer.hpp"
#include "physics/PhysicsEngine.hpp"
#include "Screen.hpp"
#include <iostream>

#include "DrawingEngine.hpp"
#include "ExampleSetup.hpp"
#include "ObjectPlacementStage.hpp"


void gameloop() {
    PhysicsEngine physics_engine({0.f, -6.f});
    Screen screen(720, 720);
    Camera camera(0,0,1);
    DrawingEngine drawing_engine;
    ExampleSetup setup(&physics_engine);
    ObjectPlacementStage placement_stage(&physics_engine, &drawing_engine, &screen, &camera);

    // TODO - add placing objects by mouse

    for (auto o: setup.objects) {
        physics_engine.addObjectPhysics(o);
    }
    for (auto o: setup.drawers) {
        drawing_engine.addDrawer(o);
    }

    // physics_engine.start();
    screen.createWindow();

    bool started = false;

    while (screen.isWindowOpen()) {
        // physics_engine.step();
        // TODO - window events should not be handled here, find a way to change that
        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        drawing_engine.draw(&screen, &camera);

        if (!started) {
            placement_stage.keyboardInput();
            placement_stage.draw(&screen, &camera);
        }
        else {
            physics_engine.step();
        }

        screen.getWindow()->display();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !started) {
            started = true;
            physics_engine.start();
        }
    }

}
