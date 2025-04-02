#pragma once
#include <iostream>

#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"


class MainBall {

private:
    sf::CircleShape shape;
    int x = 0;
    int y = 0;


    b2BodyId ballId;
    sf::Transform t1;

    // Set shape radius in meters and then scale it by appropriate factor, this will ensure modularity and easy changable
public:
    explicit MainBall(b2WorldId worldId): shape(0.1f) {
        shape.setFillColor(sf::Color::Red);
        shape.setPosition({0, 0});


        b2BodyDef bodyDef = b2DefaultBodyDef();
        bodyDef.type = b2_dynamicBody;
        bodyDef.position = {0.0f, 1.0f};
        this->ballId = b2CreateBody(worldId, &bodyDef);
        b2Polygon dynamicBox = b2MakeRoundedBox(0.1f, 0.1f, 0.1f);
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.friction = 1.f;
        b2CreatePolygonShape(this->ballId, &shapeDef, &dynamicBox);
    }

    void draw(sf::RenderWindow& window, sf::Transform& transform) {
        b2Vec2 pos = b2Body_GetPosition(this->ballId);
        sf::Vector2f v = transform.transformPoint({pos.x,pos.y});
        std::cout << v.x << " " << v.y << std::endl;
        shape.setPosition(v);
        window.draw(shape);
    }

};

