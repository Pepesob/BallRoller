//
// Created by sp on 02.05.2025.
//

#ifndef RECTANGLEOBJECT_HPP
#define RECTANGLEOBJECT_HPP


#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/ShapeDrawer.hpp"



class RectangleObject : public SimulationObjectBase {
public:

    void setInitialPosition(const Vector2D& position) override {
        rectangle.config.initial_position = position;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&rectangle};
    }
    RectangleBody rectangle;
};


class RectangleDrawer: public SimulationObjectDrawer {
public:
    explicit RectangleDrawer(const std::shared_ptr<RectangleObject> &object) {
        this->object = object;
    }

    void drawPreview(Screen *screen, Camera *camera) override {
        renderer.drawShape(object->rectangle.config, this->object->rectangle.config.initial_position, this->object->rectangle.config.rotation, screen, camera);
    }

    void drawSimulation(Screen *screen, Camera *camera) override {
        Vector2D v = object->simulation->getBodyPosition(this->object->rectangle);
        float rot = object->simulation->getBodyRotation(this->object->rectangle);
        this->renderer.drawShape(this->object->rectangle.config, v, rot, screen, camera);
    }

private:
    RectangleShapeDrawer renderer;
    std::shared_ptr<RectangleObject> object;
};




#endif //RECTANGLEOBJECT_HPP
