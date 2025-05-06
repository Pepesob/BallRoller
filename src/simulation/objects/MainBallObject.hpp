//
// Created by sp on 02.05.2025.
//

#ifndef MAINBALLOBJECT_HPP
#define MAINBALLOBJECT_HPP

#include "simulation/physics/Simulation.hpp"
#include <cmath>

class MainBallObject : public SimulationObjectBase {
public:

    MainBallObject() {
        this->ball.config.bodyType = 2;
    }

    void setInitialPosition(const Vector2D& position) override {
        ball.config.initial_position = position;
        ball.setPosition(ball.config.initial_position);
    }

    void setInitialRotation(const float radians) override {
        ball.config.initial_rotation = radians;
        ball.setRotation(ball.config.initial_rotation);
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&ball};
    }

    YAML::Node saveConfig() override {
        YAML::Node node = SimulationObjectBase::saveConfig();
        node["objectType"] = "MainBall";
        return node;
    }

    void step() override {
        Vector2D v = this->simulation->getVelocity(this->ball);
        float current_speed = std::sqrt(v.x * v.x + v.y * v.y);
        if (current_speed > this->max_speed) {
            float scale = this->max_speed / current_speed;
            this->simulation->setVelocity(this->ball, {v.x * scale, v.y * scale});
        }
    }

    float max_speed = 20;
    CircleBody ball;
};


// class MainBallDrawer: public SimulationObjectDrawer {
// public:
//     explicit MainBallDrawer(const std::shared_ptr<MainBallObject> &object) {
//         this->object = object;
//     }
//
//     void drawPreview(Screen *screen, Camera *camera) override {
//         this->renderer.drawShape(object->ball.config, this->object->ball.config.initial_position, this->object->ball.config.rotation, screen, camera);
//     }
//
//     void drawSimulation(Screen *screen, Camera *camera) override {
//         Vector2D v = object->simulation->getBodyPosition(this->object->ball);
//         float rot = object->simulation->getBodyRotation(this->object->ball);
//         this->renderer.drawShape(this->object->ball.config, v, rot, screen, camera);
//     }
//
//
// private:
//     CircleShapeDrawer renderer;
//     std::shared_ptr<MainBallObject> object;
// };



#endif //MAINBALLOBJECT_HPP
