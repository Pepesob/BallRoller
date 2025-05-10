#include "SimulationObjectFactory.hpp"

#include "AcceleratorObject.hpp"
#include "CompoundTest.hpp"
#include "GoalObject.hpp"
#include "MainBallObject.hpp"
#include "RectangleObject.hpp"

std::unordered_map<std::string, std::function<SimulationSprite()>> SimulationObjectFactory::spriteCreators;

void register_sprites() {
    REGISTER_SIMULATION_SPRITE("MainBall", MainBallObject, MainBallObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Rectangle", RectangleObject, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Accelerator", AcceleratorObject, RectangleObjectDrawer);
    REGISTER_SIMULATION_SPRITE("Goal", GoalObject, RectangleObjectDrawer);

    // add custom sprites here
    REGISTER_SIMULATION_SPRITE("CompoundTest", CompoundTest, CompoundTestDrawer);
}