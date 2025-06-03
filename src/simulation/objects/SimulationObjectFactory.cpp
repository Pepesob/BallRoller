#include "SimulationObjectFactory.hpp"

#include "AcceleratorObject.hpp"
#include "GoalObject.hpp"
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"
#include "SwingingRectangle.hpp"
#include "TeleporterObject.hpp"

std::unordered_map<std::string, std::function<SimulationSprite(const YAML::Node&)>> SimulationObjectFactory::spriteCreators2;

void register_sprites() {
    // add custom sprites here

    REGISTER_SIMULATION_SPRITE("MainBall", defaultSimulationObjectCreator<MainBallObject>, MainBallObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Rectangle", defaultSimulationObjectCreator<RectangleObject>, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Accelerator", defaultSimulationObjectCreator<AcceleratorObject>, AcceleratorObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Goal", defaultSimulationObjectCreator<GoalObject>, GoalObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Teleporter", defaultSimulationObjectCreator<TeleporterObject>, TeleporterDrawer);
    REGISTER_SIMULATION_SPRITE("SwingingRectangle", defaultSimulationObjectCreator<SwingingRectangleObject>, SwingingRectangleObjectDrawer);
}

void SimulationSprite::free() const {
    delete object;
    delete drawer;
}

SimulationSprite SimulationObjectFactory::createSimulationSprite(const std::string &name) {
    if (!spriteCreators2.contains(name)) {
        throw std::invalid_argument("Object type not recognised: " + name);
    }
    return SimulationObjectFactory::spriteCreators2[name](YAML::Node());
}

SimulationSprite SimulationObjectFactory::createSimulationSprite(const YAML::Node &config) {
    const std::string name = config["objectType"].as<std::string>();
    if (!spriteCreators2.contains(name)) {
        throw std::invalid_argument("Object type not recognised: " + name);
    }
    return SimulationObjectFactory::spriteCreators2[name](config);
}

void SimulationObjectFactory::registerSpriteCreator(const std::string &name,
    const std::function<SimulationSprite(const YAML::Node &)> &creator) {
    if (spriteCreators2.contains(name)) {
        throw std::invalid_argument("Object already registered: " + name);
    }
    spriteCreators2[name] = creator;
}

bool SimulationObjectFactory::isSpriteTagValid(const std::string &tag) {
    return spriteCreators2.contains(tag);
}

std::vector<std::string> SimulationObjectFactory::getAvailableTags() {
    auto a = std::views::keys(spriteCreators2);
    return {a.begin(), a.end()};
}

void SimulationObjectFactory::clear() {
    SimulationObjectFactory::spriteCreators2.clear();
}

