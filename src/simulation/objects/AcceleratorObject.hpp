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
        Vector2D v_force = {this->forceScalar * std::cos(this->initialRotation), this->forceScalar * std::sin(this->initialRotation)};
        simulation.applyForce(other_body, v_force);
        std::cout << this->initialRotation << std::endl;
        std::cout << v_force.x << " " << v_force.y << std::endl;
    }

    void setInitialPosition(const Vector2D& position) override {
        SimulationObjectBase::setInitialPosition(position);
        rectangle.setInitialPosition(position);
    }

    void setInitialRotation(const float radians) override {
        SimulationObjectBase::setInitialRotation(radians);
        rectangle.setInitialRotation(radians);
    }

    YAML::Node saveConfig() override {
        YAML::Node node = SimulationObjectBase::saveConfig();
        node["objectType"] = "Accelerator";
        return node;
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
    RectangleObject rectangle;
};


#endif //ACCELERATOROBJECT_HPP
