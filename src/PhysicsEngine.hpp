#pragma once

#include <Box2d/box2d.h>
#include <chrono>
#include <cmath>
#include <iostream>

void test_engine();

class PhysicsEngine {

public:
    // To make physics engine work as close to real time as possible, algorithm was implemented to keep simulation
    // as close to real time as possible even in case of missing time frames for steps.
    // To make this physics engine work, you have to start it as late as possible before your game loop starts to work
    // For now calling start will just update the prev time reference so it is safe to call it multiple times without
    // stop, however this might change in the future
    PhysicsEngine(float gravity_x, float gravity_y) {
        this->gravity = {gravity_x, gravity_y};

        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = this->gravity;

        this->worldId = b2CreateWorld( &worldDef );
        this->started = false;
    }

    ~PhysicsEngine() {
        b2DestroyWorld(this->worldId);
    }

    void start() {
        this->prev_time = prev_time = std::chrono::steady_clock::now();
        this->started = true;
    }

    void stop() {
        this->started = false;
    }

    void update() {
        if (!this->started) {
            throw std::runtime_error("PhysicsEngine is not started");
        }
        std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
        std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(current - this->prev_time);
        int possible_step_count = static_cast<float>(diff.count()) / (this->timeStep * 1000.);
        std::cout << "----------------------------" << std::endl;
        std::cout << possible_step_count << " possible steps" << std::endl;
        int actual_step_count = std::ceil(std::sqrt(possible_step_count));
        std::cout << actual_step_count << " steps" << std::endl;
        std::cout << "----------------------------" << std::endl;
        for (int i = 0; i < actual_step_count; i++) {
            b2World_Step(worldId, timeStep, subStepCount);
        }
        std::chrono::milliseconds delta_ms(static_cast<long long>(actual_step_count * this->timeStep * 1000.0));
        this->prev_time += delta_ms;
    }

    [[nodiscard]] b2WorldId getWorldId() const {
        return worldId;
    }


private:
    b2WorldId worldId;
    b2Vec2 gravity;
    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;
    bool started = false;
    std::chrono::steady_clock::time_point prev_time;
};

