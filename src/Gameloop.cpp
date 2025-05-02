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


    RectangleBody rect_body;
    rect_body.config.position = {0,0};
    rect_body.config.rotation = 3.14/6;

    CircleBody body_circle;
    body_circle.config.position = {0,1};
    body_circle.config.bodyType = b2_dynamicBody;

    simulation.addBody(rect_body);
    simulation.addBody(body_circle);


    RectangleShapeRenderer renderer;
    CircleShapeRenderer circle_renderer;

    screen.createWindow();

    auto start = std::chrono::steady_clock::now();

    while (true) {
        simulation.fixedStep();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));

        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        Vector2D curr_pos = simulation.getBodyPosition(rect_body);
        float curr_rot = simulation.getBodyRotation(rect_body);

        Vector2D curr_pos2 = simulation.getBodyPosition(body_circle);
        float curr_rot2 = simulation.getBodyRotation(body_circle);

        std::cout << curr_rot << std::endl;
        std::cout << curr_rot2 << std::endl;

        renderer.drawShape(rect_body, curr_pos, curr_rot, &screen, &camera);
        circle_renderer.drawShape(body_circle, curr_pos2, curr_rot2, &screen, &camera);

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
