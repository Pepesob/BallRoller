//
// Created by sp on 03.05.2025.
//

#ifndef LEVELSETUP_HPP
#define LEVELSETUP_HPP
#include <iostream>
#include <vector>

#include "SimulationObjectFactory.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"


class LevelSetup {
public:
    LevelSetup(const YAML::Node& object_list) {
        try {
            assert(object_list.IsSequence());
            SimulationObjectFactory factory;
            for (const YAML::Node& obj_config: object_list) {
                SimulationObjectBase* obj_base = factory.createSimulationObject(obj_config["objectType"].as<std::string>());
                ISimulationObjectDrawer* obj_drawer = factory.createSimulationObjectDrawer(obj_config["objectType"].as<std::string>(), obj_base);
                obj_base->loadConfig(obj_config);
                objects.push_back(obj_base);
                drawers.push_back(obj_drawer);
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            throw std::runtime_error("Error while loading available level objects");
        }
    }

    LevelSetup() {
        auto main_ball = new MainBallObject();
        main_ball->setInitialPosition({0, 0});

        auto rect1 = new RectangleObject();
        rect1->setInitialPosition({0, -2});
        rect1->setInitialRotation(0);
        rect1->rectangle.config.size = {4, 0.2};
        rect1->rectangle.config.restitution = 1.1;

        auto rect2 = new RectangleObject();
        rect2->setInitialPosition({-2, 0});
        rect2->setInitialRotation(3.14/2);
        rect2->rectangle.config.size = {4, 0.2};
        rect2->rectangle.config.restitution = 1.1;

        auto rect3 = new RectangleObject();
        rect3->setInitialPosition({0, 2});
        rect3->setInitialRotation(0);
        rect3->rectangle.config.size = {4, 0.2};
        rect3->rectangle.config.restitution = 1.1;

        auto rect4 = new RectangleObject();
        rect4->setInitialPosition({2, 0});
        rect4->setInitialRotation(3.14/2);
        rect4->rectangle.config.size = {4, 0.2};
        rect4->rectangle.config.restitution = 1.1;


        objects.push_back(main_ball);
        objects.push_back(rect1);
        objects.push_back(rect2);
        objects.push_back(rect3);
        objects.push_back(rect4);
    }

    void place(B2dSimulation& simulation) {
        for (auto* object : objects) {
            simulation.addObject(*object);
        }
    }

    void draw(Screen* screen, Camera* camera) {
        for (auto* drawer : drawers) {
            drawer->draw(screen, camera);
        }
    }

    std::vector<SimulationObjectBase*> objects;
    std::vector<ISimulationObjectDrawer*> drawers;
};



#endif //LEVELSETUP_HPP
