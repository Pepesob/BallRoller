
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include <chrono>
#include <box2d/box2d.h>

#include "common.hpp"
#include "simulation/physics/SimulationBody.hpp"



class B2dSimulation;
class SimulationBody;
class SimulationObjectBase;

template<typename T>
T* getObjectAs(SimulationObjectBase* obj) {
    return dynamic_cast<T*>(obj);
}

inline void saveCurrentWorld(const std::vector<SimulationObjectBase*>& objects, const std::string &filename);


class B2dSimulation {
public:
    explicit B2dSimulation(Vector2D gravity);
    void step();
    void fixedStep();
    void resetTimer();
    void addObject(SimulationObjectBase& obj);
    void addBody(SimulationBody& body);
    [[nodiscard]] SimulationBody& b2dGetAssociatedBody(b2BodyId body_id) const;
    [[nodiscard]] SimulationObjectBase* getAssociatedObject(const SimulationBody& body) const;
    Vector2D getBodyPosition(SimulationBody& body);
    float getBodyRotation(SimulationBody& body);
    void updateBodies();
    void applyForce(SimulationBody& body, Vector2D force);
    void setVelocity(SimulationBody& body, Vector2D velocity);
    [[nodiscard]] Vector2D getVelocity(SimulationBody& body);

    std::vector<SimulationBody*> bodies;
    std::vector<SimulationObjectBase*> objects{};
    b2WorldId world_id {};
    Vector2D gravity = {0,0};
    float timeStep = 1.f/60.f;
    int subStepCount = 4;
    bool goalReached = false;

private:
    std::chrono::steady_clock::time_point prev_time = std::chrono::steady_clock::time_point::min();
};






#endif //SIMULATION_HPP
