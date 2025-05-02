// //
// // Created by sp on 02.05.2025.
// //
//
// #ifndef SIMULATION_HPP
// #define SIMULATION_HPP
// #include <memory>
// #include <vector>
//
// #include "common.hpp"
//
// class Simulation;
//
//
// struct SimulationBodyConfig {
//     int bodyType = 0;
//     Vector2D position = {0,0};
//     float rotation = 0.f;
//     float friction = 0;
//     float restitution = 0.5f;
//     float density = 1.f;
//     bool isSensor = false;
// };
//
// class SimulationBody {
//     virtual ~SimulationBody() = default;
// };
//
//
// struct CircleBodyConfig: SimulationBodyConfig {
//     float radius = 0.1f;
// };
//
// class CircleBody: public SimulationBody {
// public:
//     explicit CircleBody(const CircleBodyConfig& config=CircleBodyConfig()) {
//         this->config=config;
//     }
//
//     CircleBodyConfig config;
// };
//
// struct RectangleBodyConfig: SimulationBodyConfig {
//     Vector2D size = {1.f,0.1f};
// };
//
// class RectangleBody: public SimulationBody {
// public:
//     explicit RectangleBody(const RectangleBodyConfig& config=RectangleBodyConfig()) {
//         this->config=config;
//     }
//
//     RectangleBodyConfig config;
// };
//
//
// class SimulationObject {
// public:
//     virtual ~SimulationObject() = default;
//     virtual void onCollisionBegin(Simulation& simulation, SimulationBody& this_body, SimulationBody& other_body);
//     virtual void onCollisionEnd(Simulation& simulation, SimulationBody& this_body, SimulationBody& other_bodyB);
//     virtual void step();
//     virtual bool hasBody(const SimulationBody& body);
// };
//
//
// class Simulation {
// public:
//     explicit Simulation(Vector2D gravity);
//     void step();
//     void fixedStep();
//     void resetTimer();
//     void addObject(const std::shared_ptr<SimulationObject> &obj);
//     void addBody(SimulationBody& body);
//     [[nodiscard]] std::shared_ptr<SimulationObject> getAssociatedObject(const SimulationBody& body) const;
//     Vector2D getBodyPosition(SimulationBody& body);
//     float getBodyRotation(SimulationBody& body);
//     void applyForce(SimulationBody& body, Vector2D force);
// };
//
//
// #endif //SIMULATION_HPP
