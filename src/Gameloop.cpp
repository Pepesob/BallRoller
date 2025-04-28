#include "Gameloop.hpp"

#include <iostream>

#include "AccelerationField.hpp"
#include "physics/PhysicsEngine.hpp"
#include "Screen.hpp"

#include "DrawingEngine.hpp"
#include "ExampleSetup.hpp"
#include "ObjectPlacementStage.hpp"
#include "Shape.hpp"
#include <thread>
#include <chrono>


void gameloop() {
    // PhysicsEngine physics_engine({0.f, -6.f});
    Screen screen(720, 720);
    Camera camera(0,0,0.5);
    // DrawingEngine drawing_engine;
    // ExampleSetup setup(&physics_engine);
    // ObjectPlacementStage placement_stage(&physics_engine, &drawing_engine, &screen, &camera);

    B2dSimulation simulation({0, -6.0f});

    RectangleShape rectangle({0,0}, {1, 0.1});
    SimulationBody body;
    body.addShape(&rectangle);

    CircleShape ball({0,0}, 0.1);
    SimulationBodyConfig config;
    config.bodyType = b2_dynamicBody;
    config.position = {0, 2};
    config.rotation = 3.14/2;
    SimulationBody body2(config);
    body2.addShape(&ball);

    RectangleShapeRenderer renderer;
    CircleShapeRenderer circle_renderer;

    simulation.addBody(&body);
    simulation.addBody(&body2);

    screen.createWindow();

    while (true) {
        simulation.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
        Vector2D v = simulation.getBodyPosition(&body);
        Vector2D v2 = simulation.getBodyPosition(&body2);
        std::cout << "Time step" << std::endl;
        std::cout << v.x << ", " << v.y << std::endl;
        std::cout << v2.x << ", " << v2.y << std::endl;

        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        Vector2D curr_pos = simulation.getBodyPosition(&body);
        Vector2D curr_pos2 = simulation.getBodyPosition(&body2);
        float curr_rot = simulation.getBodyRotation(&body);
        float curr_rot2 = simulation.getBodyRotation(&body2);

        renderer.drawShape(rectangle, curr_pos, curr_rot, &screen, &camera);
        circle_renderer.drawShape(ball, curr_pos2, curr_rot2, &screen, &camera);

        screen.getWindow()->display();
    }

    // for (auto o: setup.objects) {
    //     physics_engine.addObjectPhysics(o);
    // }
    // for (auto o: setup.drawers) {
    //     drawing_engine.addDrawer(o);
    // }

    // physics_engine.start();
    // screen.createWindow();
    //
    // bool started = false;
    //
    // while (screen.isWindowOpen()) {
    //     // physics_engine.step();
    //     screen.handleWindowEvents();
    //     camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
    //     screen.getWindow()->clear();
    //
    //     drawing_engine.draw(&screen, &camera);
    //
    //     if (!started) {
    //         placement_stage.keyboardInput();
    //         placement_stage.draw(&screen, &camera);
    //     }
    //     else {
    //         physics_engine.step();
    //     }
    //
    //     screen.getWindow()->display();
    //
    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && !started) {
    //         started = true;
    //         physics_engine.start();
    //     }
    // }
}
