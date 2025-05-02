#include "Gameloop.hpp"

#include <iostream>

#include "Screen.hpp"
#include "DrawingEngine.hpp"
#include "ObjectPlacementStage.hpp"
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
    DrawingEngine drawingEngine;

    ObjectPlacementStage placement_stage(&screen, &camera);

    // auto rectangle = std::make_shared<RectangleObject>();
    // rectangle->rectangle.config.rotation = 3.14/16;
    // rectangle->rectangle.config.restitution = 0.0f;
    // auto ball = std::make_shared<MainBallObject>();
    // ball->setInitialPosition({0.,1});
    // ball->ball.config.restitution = 0.1f;
    //
    // simulation.addObject(rectangle);
    // simulation.addObject(ball);

    //
    // MainBallDrawer2 main_ball_drawer(ball);
    // RectangleDrawer rectangle_drawer(rectangle);

    screen.createWindow();

    auto start = std::chrono::steady_clock::now();

    int state = 0;

    while (true) {
        // simulation.fixedStep();
        // std::this_thread::sleep_for(std::chrono::milliseconds(1000/30));

        screen.handleWindowEvents();
        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        screen.getWindow()->clear();

        if (state == 0) {
            placement_stage.keyboardInput(simulation, drawingEngine);
            placement_stage.draw(&screen, &camera);
        }
        else {
            simulation.fixedStep();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
            state = 1;
        }

        drawingEngine.draw(&screen, &camera);

        // Vector2D curr_pos = simulation.getBodyPosition(rectangle->rectangle);
        // float curr_rot = simulation.getBodyRotation(rectangle->rectangle);
        //
        // Vector2D curr_pos2 = simulation.getBodyPosition(ball->ball);
        // float curr_rot2 = simulation.getBodyRotation(ball->ball);
        //
        // std::cout << curr_rot << std::endl;
        // std::cout << curr_rot2 << std::endl;
        //
        //
        // rectangle_drawer.drawSimulation(&screen, &camera);
        // main_ball_drawer.drawSimulation(&screen, &camera);
        //
        // if (curr_pos2.y < -1) break;

        debug_lines(screen.getWindow());

        // screen.getWindow()->draw(sprite);

        screen.getWindow()->display();
    }

    auto end = std::chrono::steady_clock::now();

    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

}
