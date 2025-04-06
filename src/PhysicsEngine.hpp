#pragma once

#include <Box2d/box2d.h>
#include <chrono>

void test_engine();

class PhysicsEngine {

public:
    // To make physics engine work as close to real time as possible, algorithm was implemented to keep simulation
    // as close to real time as possible even in case of missing time frames for steps.
    // To make this physics engine work, you have to start it as late as possible before your game loop starts to work
    // For now calling start will just update the prev time reference so it is safe to call it multiple times without
    // stop, however this might change in the future
    PhysicsEngine(float gravity_x, float gravity_y);
    ~PhysicsEngine();

    void start();
    void stop();
    void update();
    [[nodiscard]] b2WorldId getWorldId() const;

private:
    b2WorldId worldId;
    b2Vec2 gravity;
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool started = false;
    std::chrono::steady_clock::time_point prev_time;
};

