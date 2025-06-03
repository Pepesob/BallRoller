
#pragma once

#include <functional>
#include <ranges>
#include <execution>

#include "common.hpp"



#define REGISTER_SIMULATION_SPRITE(Name, CreatorFunc, DrawerType)         \
    SimulationObjectFactory::registerSpriteCreator(                       \
        Name,                                                             \
        [](const YAML::Node& config) -> SimulationSprite {                \
            auto* obj = CreatorFunc(config);                              \
            auto* drawer = new DrawerType(*obj);                          \
            return {obj, drawer};                                         \
        }                                                                 \
    );                                                                    \



class Drawer;
class SimulationObjectBase;

template<class T>
T* defaultSimulationObjectCreator(const YAML::Node& config) {
    auto* obj = new T();
    try {
        obj->compound.setTransform(config["initial_position"].as<Vector2D>(), config["initial_rotation"].as<float>());
    } catch (const std::exception& e) {

    }
    return obj;
}

struct SimulationSprite {
    SimulationObjectBase* object=nullptr;
    Drawer* drawer=nullptr;

    void free() const;
};

void register_sprites();


class SimulationObjectFactory {
public:
    [[nodiscard]] static SimulationSprite createSimulationSprite(const std::string& name);
    [[nodiscard]] static SimulationSprite createSimulationSprite(const YAML::Node& config);
    static void registerSpriteCreator(const std::string& name,
        const std::function<SimulationSprite(const YAML::Node&)>& creator);
    static bool isSpriteTagValid(const std::string& tag);
    static std::vector<std::string> getAvailableTags();
    static void clear();

private:
    static std::unordered_map<std::string, std::function<SimulationSprite(const YAML::Node&)>> spriteCreators2;
};





