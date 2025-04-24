#include "Gameloop.hpp"

#include <SFML/Graphics.hpp>

#include "AccelerationField.hpp"
#include "AccelerationFieldDrawer.hpp"
#include "Camera.hpp"
#include "physics/LauncherPhysics.hpp"
#include "MainBall.hpp"
#include "MainBallDrawer.hpp"
#include "physics/MainBallPhysics.hpp"
#include "physics/PhysicsEngine.hpp"
#include "Screen.hpp"
#include "StaticRect.hpp"
#include "StaticRectDrawer.hpp"
#include "physics/AccelerationFieldPhysics.hpp"
#include "physics/CollisionManager.hpp"
#include "physics/StaticRectPhysics.hpp"


void debug_lines(sf::RenderWindow* window) {
    // Calculate 10% of window dimensions
    float cellWidth = window->getSize().x * 0.05f;
    float cellHeight = window->getSize().y * 0.05f;


    sf::Vertex line[2];
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    // Draw vertical lines
    for (float x = cellWidth; x < window->getSize().x; x += cellWidth)
    {
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, window->getSize().y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Draw horizontal lines
    for (float y = cellHeight; y < window->getSize().y; y += cellHeight)
    {
        line[0].position = sf::Vector2f(0, y);
        line[1].position = sf::Vector2f(window->getSize().x, y);
        window->draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Create a red dot at the center of the screen
    sf::CircleShape redDot(5); // Radius 10
    redDot.setFillColor(sf::Color::Cyan);

    // Position the dot at the center of the window
    redDot.setPosition({window->getSize().x / 2 - redDot.getRadius(), window->getSize().y / 2 - redDot.getRadius()});

    // Draw the red dot
    window->draw(redDot);
}

void gameloop() {
    PhysicsEngine physics_engine(0.f, -6.f);

    Camera camera(-0,0,0.1f);
    Screen screen(720, 720);

    MainBall ball(0, 2, 0.1);
    MainBallPhysics ball_physics(&ball, physics_engine.getWorldId());
    MainBallDrawer ball_drawer(&ball, &screen, &camera);
    //
    StaticRect static_rect(0, 0, 1, 0.2);
    StaticRectPhysics static_rect_physics(&static_rect, physics_engine.getWorldId());
    StaticRectDrawer static_rect_drawer(&static_rect, &screen, &camera);

    // StaticRect launcher(0, -0.5, 0.5, 0.1, 0.5);
    // LauncherPhysics launcher_physics(&launcher, physics_engine.getWorldId(), 0.05);
    // StaticRectDrawer launcher_drawer(&launcher, &screen, &camera);

    AccelerationField acceleration_field(0, 0.2f, 1, 0.2, 1, {0.3,0});
    AccelerationFieldDrawer acceleration_field_drawer(&acceleration_field, &screen, &camera);
    AccelerationFieldPhysics acceleration_field_physics(&acceleration_field, physics_engine.getWorldId());

    CollisionManager collision_manager(physics_engine.getWorldId(), &ball_physics);
    // collision_manager.collisionSubscribe(&launcher_physics);
    collision_manager.collisionSubscribe(&acceleration_field_physics);

    screen.createWindow();
    physics_engine.start();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (screen.isWindowOpen()) {
        screen.handleWindowEvents();

        camera.setScreenRatio(static_cast<float>(screen.getWidth()) / static_cast<float>(screen.getHeight()));
        // if (std::rand() % 4 == 0) {
        //     sf::sleep(sf::milliseconds(48));
        // }

        physics_engine.update();
        collision_manager.collisionNotify();
        
        ball_physics.step();
        static_rect_physics.step();
        // acceleration_field_physics.step();
        // launcher_physics.step();

        screen.getWindow()->clear();

        ball_drawer.draw();
        static_rect_drawer.draw();
        acceleration_field_drawer.draw();
        // launcher_drawer.draw();
        debug_lines(screen.getWindow());

        screen.getWindow()->display();

        // if (ball.getY() <= -1) break;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Ball took " << duration.count() << " seconds\n";
}
