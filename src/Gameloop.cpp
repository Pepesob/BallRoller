#include "Gameloop.hpp"

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "MainBall.hpp"
#include "MainBallPhysics.hpp"
#include "Screen.hpp"
#include "StaticRect.hpp"
#include "StaticRectPhysics.hpp"
#include "box2d/box2d.h"


void debug_lines(sf::RenderWindow& window) {
    // Calculate 10% of window dimensions
    float cellWidth = window.getSize().x * 0.1f;
    float cellHeight = window.getSize().y * 0.1f;

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


    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = b2Vec2{ 0.0f, -10.0f };

    b2WorldId worldId = b2CreateWorld( &worldDef );
    // b2BodyDef groundBodyDef = b2DefaultBodyDef();
    // groundBodyDef.position = b2Vec2{ 0.0f, -1.0f };
    //
    // b2BodyId groundId = b2CreateBody( worldId, &groundBodyDef );
    // b2Polygon groundBox = b2MakeBox(50.0f, 0.1f);
    // b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    // b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    float psf = window_size / 2;
    float zoom = 1;
    MainBall ball(0.1, psf);
    ball.setZoom(zoom);
    MainBallPhysics ball_physics(&ball, worldId);

    StaticRect static_rect(0, 0, 1, 0.2, psf);
    static_rect.setZoom(zoom);
    StaticRectPhysics static_rect_physics(&static_rect, worldId);

    Camera camera(0,0,zoom);
    Screen screen(window_size, window_size);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 8;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        sf::sleep(sf::milliseconds(16));
        b2World_Step( worldId, timeStep, subStepCount );
        ball_physics.update();
        static_rect_physics.update();

        window.clear();
        sf::Transform t = screen.getScreenMatrix() * camera.getCameraMatrix();
        ball.draw(window, screen.getScreenMatrix());
        static_rect.draw(window, t);

        debug_lines(window);
        window.display();
    }
}
