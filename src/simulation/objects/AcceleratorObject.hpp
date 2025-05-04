//
// Created by sp on 02.05.2025.
//

#ifndef ACCELERATOROBJECT_HPP
#define ACCELERATOROBJECT_HPP

#include "RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"
#include "simulation/physics/SimulationBody.hpp"


class AcceleratorObject : public SimulationObjectBase {
public:
    AcceleratorObject() {
        rectangle.rectangle.config.isSensor = true;
        rectangle.rectangle.config.size = {0.5, 0.5};
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody& this_body, SimulationBody& other_body) override {
        Vector2D v_force = {this->forceScalar * std::cos(this->rotation), this->forceScalar * std::sin(this->rotation)};
        simulation.applyForce(other_body, v_force);
        std::cout << this->rotation << std::endl;
        std::cout << v_force.x << " " << v_force.y << std::endl;
    }

    void setInitialPosition(const Vector2D& position) override {
        rectangle.setInitialPosition(position);
    }

    void setInitialRotation(const float radians) override {
        rectangle.setInitialRotation(radians);
        this->rotation = radians;
    }

    std::vector<SimulationBody *> getBodies() override {
        return rectangle.getBodies();
    }

    void drawPreview(Screen *screen, Camera *camera) override {
        rectangle.drawPreview(screen, camera);
    }

    void drawSimulation(Screen *screen, Camera *camera) override {
        rectangle.drawSimulation(screen, camera);
    }

    void loadConfig(const YAML::Node &config) override {
        rectangle.loadConfig(config);
    }

    float forceScalar = 10;
    float rotation = 0;
    RectangleObject rectangle;
};


#endif //ACCELERATOROBJECT_HPP
