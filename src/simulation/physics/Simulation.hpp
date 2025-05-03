
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "simulation/physics/SimulationBody.hpp"
#include <chrono>
#include "common.hpp"
#include <box2d/box2d.h>

#include "Camera.hpp"
#include "Screen.hpp"


class B2dSimulation;
class SimulationBody;

class SimulationObjectBase {
public:
    virtual ~SimulationObjectBase() = default;
    virtual void onCollisionBegin(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void onCollisionEnd(B2dSimulation& simulation, SimulationBody& this_body, SimulationBody& other_body) {}
    virtual void step() {}
    virtual std::vector<SimulationBody*> getBodies() = 0;
    virtual void setInitialPosition(const Vector2D& position) = 0;
    virtual void setInitialRotation(const float radians) = 0;
    virtual void drawPreview(Screen *screen, Camera *camera) = 0;
    virtual void drawSimulation(Screen *screen, Camera *camera)=0;

    B2dSimulation* simulation = nullptr;
};

class B2dSimulation {
public:
    explicit B2dSimulation(Vector2D gravity);
    void step();
    void fixedStep();
    void resetTimer();
    void addObject(const std::shared_ptr<SimulationObjectBase> &obj);
    void addBody(SimulationBody& body);
    [[nodiscard]] SimulationBody& b2dGetAssociatedBody(b2BodyId body_id) const;
    [[nodiscard]] std::shared_ptr<SimulationObjectBase> getAssociatedObject(const SimulationBody& body) const;
    Vector2D getBodyPosition(SimulationBody& body);
    float getBodyRotation(SimulationBody& body);
    void applyForce(SimulationBody& body, Vector2D force);
    void draw(Screen* screen, Camera* camera);



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
