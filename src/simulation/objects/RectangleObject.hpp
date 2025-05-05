
#ifndef RECTANGLEOBJECT_HPP
#define RECTANGLEOBJECT_HPP


#include "simulation/base_drawers/ShapeDrawer.hpp"
#include "simulation/physics/Simulation.hpp"


class RectangleObject : public SimulationObjectBase {
public:

    void setInitialPosition(const Vector2D& position) override {
        SimulationObjectBase::setInitialPosition(position);
        rectangle.config.initial_position = position;
    }

    void setInitialRotation(const float radians) override {
        SimulationObjectBase::setInitialRotation(radians);
        rectangle.config.rotation = radians;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&rectangle};
    }

    void drawPreview(Screen *screen, Camera *camera) override {
        renderer.drawShape(rectangle.config, rectangle.config.initial_position, rectangle.config.rotation, screen, camera);
    }

    void drawSimulation(Screen *screen, Camera *camera) override {
        Vector2D v = simulation->getBodyPosition(rectangle);
        float rot = simulation->getBodyRotation(rectangle);
        this->renderer.drawShape(rectangle.config, v, rot, screen, camera);
    }

    void loadConfig(const YAML::Node &config) override {
        SimulationObjectBase::loadConfig(config);
        assignIfExist(config["restitution"], &this->rectangle.config.restitution);
        assignIfExist(config["size"], &this->rectangle.config.size);
    }

    YAML::Node saveConfig() override {
        YAML::Node node = SimulationObjectBase::saveConfig();
        node["objectType"] = "Rectangle";
        node["restitution"] = this->rectangle.config.restitution;
        node["size"] = this->rectangle.config.size;
        return node;
    }

    RectangleShapeDrawer renderer;
    RectangleBody rectangle;
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



#endif //RECTANGLEOBJECT_HPP
