#include "Gameloop.hpp"

#include "AccelerationFieldDrawer.hpp"
#include "physics/PhysicsEngine.hpp"
#include "Screen.hpp"
#include <iostream>

#include "DrawingEngine.hpp"
#include "ExampleSetup.hpp"


void gameloop() {
    PhysicsEngine physics_engine({0.f, -6.f});
    DrawingEngine drawing_engine{};
    ExampleSetup setup(&physics_engine);

    // TODO - add placing objects by mouse

    for (auto o: setup.objects) {
        physics_engine.addObjectPhysics(o);
    }
    for (auto o: setup.drawers) {
        drawing_engine.addDrawer(o);
    }

    physics_engine.start();
    drawing_engine.start();

    while (drawing_engine.getScreen()->isWindowOpen()) {
        physics_engine.step();
        drawing_engine.draw();
    }

}
