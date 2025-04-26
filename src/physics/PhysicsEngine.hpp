#pragma once


#include <Box2d/box2d.h>
#include <chrono>

#include "CollisionManager.hpp"
#include "common.hpp"

void test_engine();

enum EventType {
    BallContactEvent,
};

class PhysicsEngine {

public:
    // To make physics engine work as close to real time as possible, algorithm was implemented to keep simulation
    // as close to real time as possible even in case of missing time frames for steps.
    // To make this physics engine work, you have to start it as late as possible before your game loop starts to work
    // For now calling start will just update the prev time value so it is safe to call it multiple times without
    // stop, however this might change in the future
    explicit PhysicsEngine(Vector2D gravity);
    ~PhysicsEngine();

    void addObjectPhysics(ObjectPhysics* obj) {
        this->objects.push_back(obj);
    }
    void start();
    void stop();
    void step();
    [[nodiscard]] b2WorldId getWorldId() const;

private:
    void callStepOnObjects() {
        for (auto o: this->objects) {
            o->step();
        }
    }

    b2WorldId world_id = {};
    Vector2D gravity = {};
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool started = false;
    std::chrono::steady_clock::time_point prev_time;
    CollisionManager* collision_manager;
    std::vector<ObjectPhysics*> objects;
};

