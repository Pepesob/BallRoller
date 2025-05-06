//
// Created by sp on 04.05.2025.
//

#ifndef YAMLCONFIGURATIONLOADER_HPP
#define YAMLCONFIGURATIONLOADER_HPP
#include <iostream>
#include <string>

#include "AvailableLevelObjects.hpp"
#include "LevelSetup.hpp"
#include "yaml-cpp/yaml.h"


class Level {
public:
    Level() {
        this->level_setup = new LevelSetup();
        this->available_objects = new InfiniteLevelObjects();
    }

    Level(std::string fileName) {
        this->levelInfo = YAML::LoadFile(fileName);
        this->level_setup = new LevelSetup(this->levelInfo["setupObjects"]);
        this->available_objects = new AvailableLevelObjects();
    }

    // YAML::Node loadYaml(const std::string& filePath) {
    //     YAML::Node config = YAML::LoadFile("resources/Level1.yaml");
    //     std::cout << config["levelObjects"][1] << std::endl;
    // }

    void draw(Screen* screen, Camera* camera) {
        this->available_objects->draw(screen, camera);
        this->level_setup->draw(screen, camera);
    }

    YAML::Node levelInfo;
    LevelSetup* level_setup;
    AvailableLevelObjects* available_objects;
};



#endif //YAMLCONFIGURATIONLOADER_HPP
