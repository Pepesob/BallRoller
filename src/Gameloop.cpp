#include "Gameloop.hpp"

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "MainBall.hpp"
#include "MainBallDrawer.hpp"
#include "MainBallPhysics.hpp"
#include "PhysicsEngine.hpp"
#include "Screen.hpp"
#include "StaticRect.hpp"
#include "StaticRectDrawer.hpp"
#include "StaticRectPhysics.hpp"


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
    float window_size = 720;

    float psf = window_size / 2;
    float zoom = 0.5;

    PhysicsEngine physics_engine(0.f, -2.f);
    Camera camera(-0.3,-0.5,zoom);
    Screen screen(window_size, window_size, psf);

    MainBall ball(0, 1, 0.1);
    MainBallPhysics ball_physics(&ball, physics_engine.getWorldId());
    MainBallDrawer ball_drawer(&ball, &screen, &camera);

    StaticRect static_rect(0.51, 0, 1, 0.2);
    StaticRectPhysics static_rect_physics(&static_rect, physics_engine.getWorldId());
    StaticRectDrawer static_rect_drawer(&static_rect, &screen, &camera);

    physics_engine.start();
    screen.createWindow();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (screen.isWindowOpen()) {
        screen.handleWindowEvents();
        // if (std::rand() % 4 == 0) {
        //     sf::sleep(sf::milliseconds(48));
        // }

        physics_engine.update();
        
        ball_physics.update();
        static_rect_physics.update();

        screen.getWindow()->clear();

        ball_drawer.draw();
        static_rect_drawer.draw();
        debug_lines(screen.getWindow());

        screen.getWindow()->display();

        if (ball.getY() <= -1) break;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Ball took " << duration.count() << " seconds\n";
}
