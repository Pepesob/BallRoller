#pragma once

#include <SFML/Graphics.hpp>

#include "Drawer.hpp"
#include "simulation/physics/SimulationBody.hpp"



class RectangleDrawer: public Drawer {
public:
    void draw(Screen* screen, Camera* camera) override;

    Vector2D size{};
    Vector2D position{};
    float rotation=0;
    sf::Texture* texture;
    sf::RectangleShape shape;
};


class CircleDrawer: public Drawer {
public:
    void draw(Screen* screen, Camera* camera) override;

    float radius = 0;
    Vector2D position{};
    float rotation=0;
    sf::CircleShape circle;
    sf::Texture* texture;
};

class RectangleBodyDrawer: public Drawer {
public:
    explicit RectangleBodyDrawer(RectangleBody* body);

    void draw(Screen* screen, Camera* camera) override;

private:
    RectangleBody* rectangle;
    RectangleDrawer drawer;
};


class CircleBodyDrawer: public Drawer {
public:
    explicit CircleBodyDrawer(CircleBody* body);

    void draw(Screen* screen, Camera* camera) override;

private:
    CircleBody* circle;
    CircleDrawer drawer;
};
