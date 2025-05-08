
#pragma once

#include <functional>

#include "SimulationObjectBase.hpp"
#include "simulation/base_drawers/SimulationObjectDrawer.hpp"


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


struct SimulationSprite {
    SimulationObjectBase* object;
    ISimulationObjectDrawer* drawer;
};


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

private:
    static std::unordered_map<std::string, std::function<SimulationSprite()>> spriteCreators;
};





