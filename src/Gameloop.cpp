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


void debug_lines(sf::RenderWindow& window) {
    // Calculate 10% of window dimensions
    float cellWidth = window.getSize().x * 0.05f;
    float cellHeight = window.getSize().y * 0.05f;

    sf::Vertex line[2];
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;

    // Draw vertical lines
    for (float x = cellWidth; x < window.getSize().x; x += cellWidth)
    {
        line[0].position = sf::Vector2f(x, 0);
        line[1].position = sf::Vector2f(x, window.getSize().y);
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    // Draw horizontal lines
    for (float y = cellHeight; y < window.getSize().y; y += cellHeight)
    {
        line[0].position = sf::Vector2f(0, y);
        line[1].position = sf::Vector2f(window.getSize().x, y);
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

void gameloop() {
    float window_size = 720;
    sf::RenderWindow window(sf::VideoMode({(unsigned int)window_size, (unsigned int)window_size}), "My window");

    float psf = window_size / 2;
    float zoom = 0.5;

    PhysicsEngine physics_engine(0.f, -2.f);

    MainBall ball(0, 1, 0.1);
    MainBallPhysics ball_physics(&ball, physics_engine.getWorldId());
    MainBallDrawer ball_drawer(&ball, psf, zoom);

    StaticRect static_rect(0.51, 0, 1, 0.2);
    StaticRectPhysics static_rect_physics(&static_rect, physics_engine.getWorldId());
    StaticRectDrawer static_rect_drawer(&static_rect, psf, zoom);

    Camera camera(0,0,zoom);
    Screen screen(window_size, window_size);

    physics_engine.start();

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        if (std::rand() % 4 == 0) {
            sf::sleep(sf::milliseconds(48));
        }

        physics_engine.update();
        ball_physics.update();
        static_rect_physics.update();

        window.clear();
        sf::Transform t = screen.getScreenMatrix() * camera.getCameraMatrix();
        ball_drawer.draw(window, t);
        static_rect_drawer.draw(window, t);

        debug_lines(window);
        window.display();

        if (ball.getY() <= -1) break;
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Ball took " << duration.count() << " seconds\n";
}
