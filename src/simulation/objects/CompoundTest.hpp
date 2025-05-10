//
// Created by sp on 10.05.2025.
//

#pragma once
#include "BodyCompound.hpp"
#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/BodyDrawer.hpp"


class CompoundTest: public SimulationObjectBase {
public:
    CompoundTest(): SimulationObjectBase("CompoundTest") {
        body_compound.addBody(circle, {0,0}, 0);
        body_compound.addBody(rectangle, {0.5, 0}, 3.14/6);
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&circle, &rectangle};
    }

    void applyConfig() override {
        this->body_compound.setPosition(this->config["initial_position"].as<Vector2D>());
    }

    BodyCompound body_compound;
    CircleBody circle;
    RectangleBody rectangle;
};

class CompoundTestDrawer: public Drawer {
public:
    explicit CompoundTestDrawer(CompoundTest& compound): compound(compound) {
        rectangle_drawer.texture = sf::Texture("resources/wood_texture.jpg");
        circle_drawer.texture = sf::Texture("resources/pokeball_texture.png");
    }

    void draw(Screen *screen, Camera *camera) override {
        rectangle_drawer.size = compound.rectangle.config.size;
        rectangle_drawer.position = compound.rectangle.getPosition();
        rectangle_drawer.rotation = compound.rectangle.getRotation();
        rectangle_drawer.draw(screen, camera);

        circle_drawer.radius = compound.circle.config.radius;
        circle_drawer.position = compound.circle.getPosition();
        circle_drawer.rotation = compound.circle.getRotation();
        circle_drawer.draw(screen, camera);
    }

private:
    CompoundTest& compound;
    RectangleDrawer rectangle_drawer;
    CircleDrawer circle_drawer;
};
