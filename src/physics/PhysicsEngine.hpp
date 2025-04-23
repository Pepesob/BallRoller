#pragma once

#include "CollisionObserver.hpp"

#include <Box2d/box2d.h>
#include <chrono>

void test_engine();

enum EventType {
    BallContactEvent,
};

class PhysicsEngine {

public:
    // To make physics engine work as close to real time as possible, algorithm was implemented to keep simulation
    // as close to real time as possible even in case of missing time frames for steps.
    // To make this physics engine work, you have to start it as late as possible before your game loop starts to work
    // For now calling start will just update the prev time reference so it is safe to call it multiple times without
    // stop, however this might change in the future
    PhysicsEngine(float gravity_x, float gravity_y);
    ~PhysicsEngine();

    // void subscribe(CollisionObserver* observer);
    // void unsubscribe(CollisionObserver* observer);

    void start();
    void stop();
    void update();
    [[nodiscard]] b2WorldId getWorldId() const;

private:
    // void collisionNotify();
    //
    // std::vector<CollisionObserver*> collision_observers;
    b2WorldId world_id = B2_ZERO_INIT;
    b2Vec2 gravity = B2_ZERO_INIT;
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool started = false;
    std::chrono::steady_clock::time_point prev_time;

};

