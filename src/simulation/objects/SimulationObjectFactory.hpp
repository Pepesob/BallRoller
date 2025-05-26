
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

void register_sprites();

struct SimulationSprite {
    SimulationObjectBase* object=nullptr;
    Drawer* drawer=nullptr;

    void free() const;
};


class SimulationObjectFactory {

public:
    [[nodiscard]] static SimulationSprite createSimulationSprite(const std::string& name) {
        if (!spriteCreators2.contains(name)) {
            throw std::invalid_argument("Object type not recognised: " + name);
        }
        return SimulationObjectFactory::spriteCreators2[name](YAML::Node());
    }

    [[nodiscard]] static SimulationSprite createSimulationSprite(const YAML::Node& config) {
        const std::string name = config["objectType"].as<std::string>();
        if (!spriteCreators2.contains(name)) {
            throw std::invalid_argument("Object type not recognised: " + name);
        }
        return SimulationObjectFactory::spriteCreators2[name](config);
    }

    static void registerSpriteCreator(const std::string& name, const std::function<SimulationSprite(const YAML::Node&)>& creator) {
        if (spriteCreators2.contains(name)) {
            throw std::invalid_argument("Object already registered: " + name);
        }
        spriteCreators2[name] = creator;
    }

    static bool isSpriteTagValid(const std::string& tag) {
        return spriteCreators2.contains(tag);
    }

    static std::vector<std::string> getAvailableTags() {
        auto a = std::views::keys(spriteCreators2);
        return {a.begin(), a.end()};
    }

    static void clear() {
        SimulationObjectFactory::spriteCreators2.clear();
    }

private:
    static std::unordered_map<std::string, std::function<SimulationSprite(const YAML::Node&)>> spriteCreators2;
};





