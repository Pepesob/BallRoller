
#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "simulation/physics/SimulationBody.hpp"
#include <chrono>
#include <fstream>
#include <iostream>

#include "common.hpp"
#include <box2d/box2d.h>
#include "yaml_configuration.hpp"

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
    virtual void setInitialRotation(float radians) = 0;
    virtual void loadConfig(const YAML::Node& config) {
        try {
            YamlConfigLoaderVisitor visitor(config["bodies"]);
            for (auto body: this->getBodies()) {
                body->accept(visitor);
            }
        }
        catch (std::exception& e) {
            std::cerr << "WARNING: could not load configuration" << std::endl;
        }
    }

    virtual YAML::Node saveConfig() {
        YamlConfigSaverVisitor saver;
        for (auto body: this->getBodies()) {
            body->accept(saver);
        }
        YAML::Node node;
        node["bodies"] = saver.node;
        return node;
    }

    B2dSimulation* simulation = nullptr;
};

template<typename T>
T* getObjectAs(SimulationObjectBase* obj) {
    return dynamic_cast<T*>(obj);
}

inline void saveCurrentWorld(std::vector<SimulationObjectBase*>& objects, std::string filename) {
    YAML::Emitter out;
    out << YAML::BeginMap << YAML::Key << "setupObjects" << YAML::BeginSeq;
    for (auto obj : objects) {
        out << obj->saveConfig();
    }
    std::ofstream fout(filename);
    fout << out.c_str();
}



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
