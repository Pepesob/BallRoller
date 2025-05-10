
#pragma once

#include <functional>
#include <ranges>
#include <execution>

#include "common.hpp"



#define REGISTER_SIMULATION_SPRITE(Name, ObjectType, DrawerType)          \
    const bool register_##ObjectType = []() {                             \
        SimulationObjectFactory::registerSpriteCreator(                   \
            Name,                                                         \
            []() -> SimulationSprite {                                    \
                auto* obj = new ObjectType();                             \
                auto* drawer = new DrawerType(*obj);                      \
                return {obj, drawer};                                     \
            }                                                             \
        );                                                                \
        return true;                                                      \
    }();                                                                  \

void register_sprites();





class SimulationObjectFactory {

public:
    [[nodiscard]] static SimulationSprite createSimulationSprite(const std::string& name) {
        if (!spriteCreators.contains(name)) {
            throw std::invalid_argument("Object type not recognised: " + name);
        }
        return SimulationObjectFactory::spriteCreators[name]();
    }

    static void registerSpriteCreator(const std::string& name, const std::function<SimulationSprite()>& creator) {
        if (spriteCreators.contains(name)) {
            throw std::invalid_argument("Object already registered: " + name);
        }
        spriteCreators[name] = creator;
    }

    static bool isSpriteTagValid(const std::string& tag) {
        return spriteCreators.contains(tag);
    }

    static std::vector<std::string> getAvailableTags() {
        auto a = std::views::keys(spriteCreators);
        return {a.begin(), a.end()};
    }

private:
    static std::unordered_map<std::string, std::function<SimulationSprite()>> spriteCreators;
};





