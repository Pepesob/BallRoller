//
// Created by sp on 04.05.2025.
//

#ifndef YAMLCONFIGURATIONLOADER_HPP
#define YAMLCONFIGURATIONLOADER_HPP
#include <iostream>
#include <string>
#include "yaml-cpp/yaml.h"


class YamlConfigurationLoader {


public:
    void loadYaml(const std::string& filePath) {
        YAML::Node config = YAML::LoadFile("config.yaml");
        std::cout << config << std::endl;
    }

};



#endif //YAMLCONFIGURATIONLOADER_HPP
