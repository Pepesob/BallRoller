#pragma once


#include <iostream>
#include <vector>

#include "simulation/objects/SimulationObjectFactory.hpp"
#include "simulation/objects/MainBallObject.hpp"
#include "simulation/objects/RectangleObject.hpp"
#include "simulation/physics/Simulation.hpp"


class LevelSetup {
public:
    explicit LevelSetup(const YAML::Node& object_list) {
        try {
            assert(object_list.IsSequence());
            for (const YAML::Node& obj_config: object_list) {
                SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(obj_config["objectType"].as<std::string>());
                SimulationObjectBase* obj_base = sprite.object;
                Drawer* obj_drawer = sprite.drawer;
                obj_base->config = obj_config;
                obj_base->applyConfig();
                objects.push_back(obj_base);
                drawers.push_back(obj_drawer);
            }
        }
        catch (const std::exception& e) {
            std::cout << e.what() << std::endl;
            throw std::runtime_error("Error while loading available level objects");
        }
    }

    LevelSetup() = default;

    ~LevelSetup() {
        for (const auto* drawer: drawers) {
            delete drawer;
        }
        for (const auto* obj: objects) {
            delete obj;
        }
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
    std::vector<Drawer*> drawers;
};
