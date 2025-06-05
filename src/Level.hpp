//
// Created by sp on 04.05.2025.
//

#pragma once


#include <string>

#include "AvailableLevelObjects.hpp"
#include "LevelSetup.hpp"
#include "yaml-cpp/yaml.h"


class Level {
public:
    Level() {
        this->level_setup = new LevelSetup();
        this->available_objects = new AvailableLevelObjects();
        this->simulation = new B2dSimulation({0, -6.0f});
    }

    explicit Level(const std::string& fileName) {
        this->levelInfo = YAML::LoadFile(fileName);
        this->level_setup = new LevelSetup(this->levelInfo["setupObjects"]);
        this->available_objects = new AvailableLevelObjects(this->levelInfo["availableObjects"]);
        this->simulation = new B2dSimulation(this->levelInfo["simulation"]);
    }

    ~Level() {
        delete this->simulation;
        delete this->level_setup;
        delete this->available_objects;
    }

    YAML::Node levelInfo;
    LevelSetup* level_setup;
    AvailableLevelObjects* available_objects;
    B2dSimulation* simulation;
};

