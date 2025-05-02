
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "simulation/physics/SimulationBody.hpp"
#include <chrono>


#include "common.hpp"
#include "simulation/objects/SimulationObjectBase.hpp"

#include <box2d/box2d.h>

class SimulationObjectBase;


class B2dBodyBuilder: public BodyVisitor {
public:
    explicit B2dBodyBuilder(b2WorldId world_id) {
        this->world_id = world_id;
    }

    void visitCircle(CircleBody& circle) override;
    void visitRectangle(RectangleBody& rectangle) override;
    static b2BodyId b2dCreateBody(const SimulationBodyConfig &config, b2WorldId world_id);
private:
    b2WorldId world_id{};
};


class B2dSimulation {
public:
    explicit B2dSimulation(Vector2D gravity) {
        this->gravity = gravity;
        b2WorldDef worldDef = b2DefaultWorldDef();
        worldDef.gravity = {this->gravity.x, this->gravity.y};
        this->world_id = b2CreateWorld(&worldDef);
    }

    void step();

    void fixedStep() {
        if (this->prev_time == std::chrono::steady_clock::time_point::min()) {
            this->prev_time = std::chrono::steady_clock::now();
        }
        std::chrono::steady_clock::time_point current = std::chrono::steady_clock::now();
        std::chrono::duration<float> timeStepChrono{this->timeStep};
        auto diff = current - this->prev_time;
        int possible_step_count = diff / timeStepChrono;


        int actual_step_count = std::ceil(std::sqrt(possible_step_count)); // > 0 ? 1 : 0;


        for (int i = 0; i < actual_step_count; i++) {
            this->step();
        }

        this->prev_time += std::chrono::duration_cast<std::chrono::nanoseconds>(timeStepChrono * actual_step_count);
    }

    void resetTimer() {
        this->prev_time = std::chrono::steady_clock::time_point::min();
    }

    void addObject(const std::shared_ptr<SimulationObjectBase> &obj);

    void addBody(SimulationBody& body) {
        if (B2_IS_NON_NULL(body.id)) {
            throw std::runtime_error("Body already exists in the simulation!");
        }
        B2dBodyBuilder builder(this->world_id);
        body.accept(builder);
        this->bodies.push_back(&body);
    }

    [[nodiscard]] SimulationBody& b2dGetAssociatedBody(b2BodyId body_id) const {
        for (auto it: this->bodies) {
            if (B2_ID_EQUALS(it->id, body_id)) {
                return *it;
            }
        }
        throw std::runtime_error("Unknown body with given body_id");
    }

    [[nodiscard]] std::shared_ptr<SimulationObjectBase> getAssociatedObject(const SimulationBody& body) const;

    Vector2D getBodyPosition(SimulationBody& body) {
        b2BodyId body_id = body.id;
        b2Vec2 v = b2Body_GetPosition(body_id);
        return {v.x, v.y};
    }

    float getBodyRotation(SimulationBody& body) {
        b2BodyId body_id = body.id;
        b2Rot r = b2Body_GetRotation(body_id);
        return b2Rot_GetAngle(r);
    }

    void applyForce(SimulationBody& body, Vector2D force) {
        b2BodyId body_id = body.id;
        b2Body_ApplyForce(body_id, {force.x, force.y}, {0,0}, false);
    }

    std::vector<SimulationBody*> bodies;
    std::vector<std::shared_ptr<SimulationObjectBase>> objects{};
    b2WorldId world_id {};
    Vector2D gravity = {0,0};
    float timeStep = 1.f/60.f;
    int subStepCount = 4;

private:
    std::chrono::steady_clock::time_point prev_time = std::chrono::steady_clock::time_point::min();
};






#endif //SIMULATION_HPP
