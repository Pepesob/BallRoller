#pragma once


#include <memory>

#include "BodyDrawer.hpp"
#include "ShapeDrawer.hpp"
#include "simulation/objects/AcceleratorObject.hpp"
#include "simulation/objects/GoalObject.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"

// TODO - remove ISimulationObjectDrawer and replace with Drawer interface
// TODO - move drawers to corresponding object files
// TODO - remove this file

class DefaultDrawersBuilder: public BodyVisitor {
public:
    void visitCircle(CircleBody &circle) override {
        this->drawers.push_back(new CircleBodyDrawer(&circle));
    }
    void visitRectangle(RectangleBody &rectangle) override {
        this->drawers.push_back(new RectangleBodyDrawer(&rectangle));
    }

    std::vector<BodyDrawer*> build() {
        return this->drawers;
    }

private:
    std::vector<BodyDrawer*> drawers;
};


class ISimulationObjectDrawer {
public:
    virtual ~ISimulationObjectDrawer() = default;

    virtual void draw(Screen* screen, Camera* camera) = 0;
};

class DefaultObjectDrawer : public ISimulationObjectDrawer {
public:
    explicit DefaultObjectDrawer(SimulationObjectBase& object) {
        DefaultDrawersBuilder builder;
        for (const auto& body: object.getBodies()) {
            body->accept(builder);
        }
        this->drawers = builder.build();
    }

    void draw(Screen *screen, Camera *camera) override {
        for (const auto &drawer : this->drawers) {
            drawer->draw(screen, camera);
        }
    }

    std::vector<BodyDrawer*> drawers;
};

class MainBallObjectDrawer: public ISimulationObjectDrawer {
public:
    explicit MainBallObjectDrawer(MainBallObject& main_ball): main_ball(main_ball) {
        this->main_ball = main_ball;
        drawer.radius = main_ball.ball.config.radius;
        drawer.texture = sf::Texture("resources/pokeball_texture.png");
    }

    void draw(Screen *screen, Camera *camera) override {
        drawer.position = this->main_ball.ball.getPosition();
        drawer.rotation = this->main_ball.ball.getRotation();
        this->drawer.draw(screen, camera);
    }

private:
    MainBallObject& main_ball;
    CircleDrawer drawer;
};


class RectangleObjectDrawer: public ISimulationObjectDrawer {
public:
    explicit RectangleObjectDrawer(RectangleObject& rectangle): rectangle(rectangle) {
        drawer.texture = sf::Texture(rectangle.texture_path);
    }

    void draw(Screen *screen, Camera *camera) override {
        this->drawer.size = rectangle.rectangle.config.size;
        drawer.position = this->rectangle.rectangle.getPosition();
        drawer.rotation = this->rectangle.rectangle.getRotation();
        this->drawer.draw(screen, camera);
    }

private:
    RectangleObject& rectangle;
    RectangleDrawer drawer;
};

// class AcceleratorObjectDrawer: public ISimulationObjectDrawer {
// public:
//     explicit AcceleratorObjectDrawer(AcceleratorObject& accelerator): accelerator(accelerator) {
//         drawer.texture = sf::Texture("resources/arrow_texture.png");
//     }
//
//     void draw(Screen *screen, Camera *camera) override {
//         this->drawer.size = accelerator.rectangle.config.size;
//         drawer.position = this->accelerator.rectangle.getPosition();
//         drawer.rotation = this->accelerator.rectangle.getRotation();
//         this->drawer.draw(screen, camera);
//     }
//
// private:
//     AcceleratorObject& accelerator;
//     RectangleDrawer drawer;
// };
//
// class GoalObjectDrawer: public ISimulationObjectDrawer {
// public:
//     explicit GoalObjectDrawer(GoalObject& rectangle): goal(rectangle.rectangle) {
//         drawer.texture = sf::Texture("resources/finish_texture.png");
//     }
//
//     void draw(Screen *screen, Camera *camera) override {
//         this->drawer.size = goal.rectangle.config.size;
//         drawer.position = this->goal.rectangle.getPosition();
//         drawer.rotation = this->goal.rectangle.getRotation();
//         this->drawer.draw(screen, camera);
//     }
//
// private:
//     Goal& goal;
//     RectangleDrawer drawer;
// };

