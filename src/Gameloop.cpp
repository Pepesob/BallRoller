#include "Gameloop.hpp"

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "MainBall.hpp"
#include "MainBallPhysics.hpp"
#include "Screen.hpp"
#include "StaticRect.hpp"
#include "StaticRectPhysics.hpp"
#include "box2d/box2d.h"


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

    MainBall ball(window_size);
    MainBallPhysics ball_physics(&ball, worldId);

    StaticRect static_rect(0, 0, 0.5, 0.2, window_size);
    StaticRectPhysics static_rect_physics(&static_rect, worldId);

    Camera camera(0,0,1);
    Screen screen(window_size, window_size);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

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
        window.display();
    }
}
