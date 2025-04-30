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
    Camera camera(0,0,1);
    // DrawingEngine drawing_engine;
    // ExampleSetup setup(&physics_engine);
    // ObjectPlacementStage placement_stage(&physics_engine, &drawing_engine, &screen, &camera);

    B2dSimulation simulation({0, -6.0f});

    ShapeConfig shapeConfig;
    RectangleShape rectangle({1, 0.1}, shapeConfig);
    SimulationBody body;
    body.addShape(&rectangle);
    AcceleratorObject accelerator_object;
    accelerator_object.addBody(&body);

    CircleShape ball({0,2}, 0.1);
    SimulationBodyConfig config;
    config.bodyType = b2_dynamicBody;
    config.position = {0, 2};
    config.rotation = 3.14/3;
    SimulationBody body2(config);
    body2.addShape(&ball);

    RectangleShapeRenderer renderer;
    CircleShapeRenderer circle_renderer;

    // simulation.addBody(&body);
    simulation.addObject(&accelerator_object);
    simulation.addBody(&body2);


    screen.createWindow();

    auto start = std::chrono::steady_clock::now();

    while (true) {
        simulation.fixedStep();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));

        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        Vector2D curr_pos = simulation.getBodyPosition(&body);
        float curr_rot = simulation.getBodyRotation(&body);

        Vector2D curr_pos2 = simulation.getBodyPosition(&body2);
        float curr_rot2 = simulation.getBodyRotation(&body2);

        std::cout << curr_rot << std::endl;
        std::cout << curr_rot2 << std::endl;

        renderer.drawShape(rectangle, curr_pos, curr_rot, &screen, &camera);
        circle_renderer.drawShape(ball, curr_pos2, curr_rot2, &screen, &camera);

        if (curr_pos2.y < -1) break;

        debug_lines(screen.getWindow());

        // screen.getWindow()->draw(sprite);

        screen.getWindow()->display();
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

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
