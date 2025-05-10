#include "SimulationObjectFactory.hpp"

#include "AcceleratorObject.hpp"
#include "GoalObject.hpp"
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"
#include "TeleporterObject.hpp"

std::unordered_map<std::string, std::function<SimulationSprite()>> SimulationObjectFactory::spriteCreators;

void register_sprites() {
    REGISTER_SIMULATION_SPRITE("MainBall", MainBallObject, MainBallObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Rectangle", RectangleObject, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Accelerator", AcceleratorObject, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Goal", GoalObject, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Teleporter", TeleporterObject, TeleporterDrawer);

    // add custom sprites here
}