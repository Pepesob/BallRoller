#pragma once

#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/BodyDrawer.hpp"
#include "simulation/base_drawers/TextureLoader.hpp"
#include <iostream>

class RectangleObject : public SimulationObjectBase {
public:

    RectangleObject(): SimulationObjectBase("Rectangle") {
        this->compound.addBody(&this->rectangle);
    }

    explicit RectangleObject(const std::string& objectType): SimulationObjectBase(objectType) {
        this->compound.addBody(&this->rectangle);
    }

    void onClick(SimulationBody& body) override {
        std::cout << "Clicked" <<std::endl;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&rectangle};
    }

    RectangleBody rectangle;
};

class RectangleObjectDrawer: public Drawer {
public:
    explicit RectangleObjectDrawer(RectangleObject& rectangle): rectangle(rectangle) {
        drawer.texture = TextureLoader::getTexture(this->texture_path);
    }

    void draw(Screen *screen, Camera *camera) override {
        this->drawer.size = rectangle.rectangle.config.size;
        drawer.position = this->rectangle.rectangle.getPosition();
        drawer.rotation = this->rectangle.rectangle.getRotation();
        this->drawer.draw(screen, camera);
    }



    std::string texture_path = "resources/wood_texture.jpg";
    RectangleObject& rectangle;
    RectangleDrawer drawer;
};

//
// class RectangleDrawer: public SimulationObjectDrawer {
// public:
//     explicit RectangleDrawer(const std::shared_ptr<RectangleObject> &object) {
//         this->object = object;
//     }
//
//     void drawPreview(Screen *screen, Camera *camera) override {
//         renderer.drawShape(object->rectangle.config, this->object->rectangle.config.initial_position, this->object->rectangle.config.rotation, screen, camera);
//     }
//
//     void drawSimulation(Screen *screen, Camera *camera) override {
//         Vector2D v = object->simulation->getBodyPosition(this->object->rectangle);
//         float rot = object->simulation->getBodyRotation(this->object->rectangle);
//         this->renderer.drawShape(this->object->rectangle.config, v, rot, screen, camera);
//     }
//
//
//
// private:
//     RectangleShapeDrawer renderer;
//     std::shared_ptr<RectangleObject> object;
// };
//


