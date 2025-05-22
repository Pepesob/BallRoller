//
// Created by sp on 02.05.2025.
//

#pragma once


#include "simulation/physics/Simulation.hpp"
#include "RectangleObject.hpp"


class AcceleratorObject : public RectangleObject {
public:
    AcceleratorObject(): RectangleObject("Accelerator") {
        rectangle.config.isSensor = true;
        rectangle.config.size = {0.5, 0.5};
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody& this_body, SimulationBody& other_body) override {
        Vector2D v_force = {this->forceScalar * std::cos(this->rectangle.getRotation()), this->forceScalar * std::sin(this->rectangle.getRotation())};
        simulation.applyForce(other_body, v_force);
    }

    float forceScalar = 10;
};

class AcceleratorObjectDrawer: public RectangleObjectDrawer {
public:
    AcceleratorObjectDrawer(AcceleratorObject& accelerator_object): RectangleObjectDrawer(accelerator_object) {
        this->texture_path = "resources/arrow_texture.png";
        this->drawer.texture = TextureLoader::getTexture(this->texture_path);
    }
};


