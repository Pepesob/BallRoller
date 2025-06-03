//
// Created by sp on 27.05.2025.
//

#pragma once
#include "Drawer.hpp"
#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/BodyDrawer.hpp"
#include "simulation/base_drawers/TextureLoader.hpp"
#include "simulation/physics/Simulation.hpp"


class SwingingRectangleObject: public SimulationObjectBase {
public:

    SwingingRectangleObject(): SimulationObjectBase("SwingingRectangle") {
        this->rectangle.config.size = {1, 0.1};
        this->rectangle.config.bodyType = b2_dynamicBody;
        this->bolt1.config.radius = 0.1;
        this->bolt1.config.initial_position = {-0.5, 0};
        this->bolt1.config.isSensor = true;
        this->bolt2.config.radius = 0.1;
        this->bolt2.config.initial_position = {0.5, 0};
        this->bolt2.config.isSensor = true;


        joint1.body1 = &this->rectangle;
        joint1.body2 = &this->bolt1;
        joint1.local_pos1 = {-0.5, 0};
        joint1.local_pos2 = {0,0};
        //
        joint2.body1 = &this->rectangle;
        joint2.body2 = &this->bolt2;
        joint2.local_pos1 = {0.5,0};
        joint2.local_pos2 = {0,0};

        this->compound.addBody(&this->rectangle);
        this->compound.addBody(&this->bolt1, {-0.5, 0});
        this->compound.addBody(&this->bolt2, {0.5, 0});
    }

    void onInit() override {
        this->simulation->addJoint(this->joint1);
        this->simulation->addJoint(this->joint2);
    }

    void onClick(SimulationBody& body) override {
        if (!bolt_removed) {
            this->simulation->removeJoint(this->joint1);
            bolt_removed = true;
        }
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&rectangle, &bolt1, &bolt2};
    }

    RectangleBody rectangle;
    CircleBody bolt1;
    CircleBody bolt2;

    RevoluteJoint joint1;
    RevoluteJoint joint2;

    bool bolt_removed = false;
};

class SwingingRectangleObjectDrawer: public Drawer {
public:
    explicit SwingingRectangleObjectDrawer(SwingingRectangleObject& rectangle): rectangle(rectangle) {
        drawer.texture = TextureLoader::getTexture(this->texture_path);
        b1_drawer.texture = TextureLoader::getTexture(this->broken_bolt_path);
        b2_drawer.texture = TextureLoader::getTexture(this->bolt_path);
    }

    void draw(Screen *screen, Camera *camera) override {
        this->drawer.size = rectangle.rectangle.config.size;
        drawer.position = this->rectangle.rectangle.getPosition();
        drawer.rotation = this->rectangle.rectangle.getRotation();
        this->drawer.draw(screen, camera);

        if (!this->rectangle.bolt_removed) {
            this->b1_drawer.radius = this->rectangle.bolt1.config.radius;
            this->b1_drawer.position = this->rectangle.bolt1.getPosition();
            this->b1_drawer.rotation = this->rectangle.bolt1.getRotation();
            this->b1_drawer.draw(screen, camera);
        }

        this->b2_drawer.radius = this->rectangle.bolt2.config.radius;
        this->b2_drawer.position = this->rectangle.bolt2.getPosition();
        this->b2_drawer.rotation = this->rectangle.bolt2.getRotation();
        this->b2_drawer.draw(screen, camera);
    }

    std::string texture_path = "resources/wood_texture.jpg";
    std::string broken_bolt_path = "resources/broken_screw_texture.png";
    std::string bolt_path = "resources/screw_texture.png";
    SwingingRectangleObject& rectangle;
    RectangleDrawer drawer;
    CircleDrawer b1_drawer;
    CircleDrawer b2_drawer;
};
