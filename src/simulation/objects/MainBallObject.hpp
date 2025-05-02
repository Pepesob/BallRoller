//
// Created by sp on 02.05.2025.
//

#ifndef MAINBALLOBJECT_HPP
#define MAINBALLOBJECT_HPP

#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/ShapeDrawer.hpp"


class MainBallObject : public SimulationObjectBase {
public:

    void setInitialPosition(const Vector2D& position) override {
        ball.config.initial_position = position;
        ball.config.bodyType = 2;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&ball};
    }

    CircleBody ball;
};


class MainBallDrawer: public SimulationObjectDrawer {
public:
    explicit MainBallDrawer(const std::shared_ptr<MainBallObject> &object) {
        this->object = object;
    }

    void drawPreview(Screen *screen, Camera *camera) override {
        this->renderer.drawShape(object->ball.config, this->object->ball.config.initial_position, this->object->ball.config.rotation, screen, camera);
    }

    void drawSimulation(Screen *screen, Camera *camera) override {
        Vector2D v = object->simulation->getBodyPosition(this->object->ball);
        float rot = object->simulation->getBodyRotation(this->object->ball);
        this->renderer.drawShape(this->object->ball.config, v, rot, screen, camera);
    }


private:
    CircleShapeDrawer renderer;
    std::shared_ptr<MainBallObject> object;
};



#endif //MAINBALLOBJECT_HPP
