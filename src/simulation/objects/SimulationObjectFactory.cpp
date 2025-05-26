#include "SimulationObjectFactory.hpp"

#include "AcceleratorObject.hpp"
#include "GoalObject.hpp"
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"
#include "TeleporterObject.hpp"

std::unordered_map<std::string, std::function<SimulationSprite(const YAML::Node&)>> SimulationObjectFactory::spriteCreators2;

void register_sprites() {
    // add custom sprites here

    REGISTER_SIMULATION_SPRITE("MainBall", defaultSimulationObjectCreator<MainBallObject>, MainBallObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Rectangle", defaultSimulationObjectCreator<RectangleObject>, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Accelerator", defaultSimulationObjectCreator<AcceleratorObject>, AcceleratorObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Goal", defaultSimulationObjectCreator<GoalObject>, GoalObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Teleporter", defaultSimulationObjectCreator<TeleporterObject>, TeleporterDrawer);
}

void SimulationSprite::free() const {
    delete object;
    delete drawer;
}

