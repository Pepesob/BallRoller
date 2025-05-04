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
                std::shared_ptr<SimulationObjectBase> obj_base = factory.createSimulationObject(obj_config["objectType"].as<std::string>());
                obj_base->loadConfig(obj_config);
                objects.push_back(obj_base);
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            throw std::runtime_error("Error while loading available level objects");
        }
    }

    LevelSetup() {
        auto main_ball = std::make_shared<MainBallObject>();
        main_ball->setInitialPosition({0, 0});

        auto rect1 = std::make_shared<RectangleObject>();
        rect1->setInitialPosition({0, -2});
        rect1->setInitialRotation(0);
        rect1->rectangle.config.size = {4, 0.2};
        rect1->rectangle.config.restitution = 1.1;

        auto rect2 = std::make_shared<RectangleObject>();
        rect2->setInitialPosition({-2, 0});
        rect2->setInitialRotation(3.14/2);
        rect2->rectangle.config.size = {4, 0.2};
        rect2->rectangle.config.restitution = 1.1;

        auto rect3 = std::make_shared<RectangleObject>();
        rect3->setInitialPosition({0, 2});
        rect3->setInitialRotation(0);
        rect3->rectangle.config.size = {4, 0.2};
        rect3->rectangle.config.restitution = 1.1;

        auto rect4 = std::make_shared<RectangleObject>();
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
        for (auto& object : objects) {
            simulation.addObject(object);
        }
    }

    std::vector<std::shared_ptr<SimulationObjectBase>> objects;
};



#endif //LEVELSETUP_HPP
