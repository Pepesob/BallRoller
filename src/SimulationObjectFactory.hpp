//
// Created by sp on 27.04.2025.
//

#ifndef SIMULATIONOBJECTFACTORY_HPP
#define SIMULATIONOBJECTFACTORY_HPP

#include "Drawer.hpp"
#include "RectangleDrawer.hpp"
#include "physics/RectanglePhysics.hpp"
#include "common.hpp"
#include "RectanglePreviewDrawer.hpp"


class SimulationObjectFactory {
public:
    static Drawer* createObjectDrawer(PhysicsObjectType object_type, ObjectPhysics* physics) {
        switch (object_type) {
            case Rectangle: {
                auto* p = dynamic_cast<RectanglePhysics*>(physics);
                if (nullptr == p) {
                    throw std::runtime_error("ObjectPhysics is wrong type");
                }
                return new RectangleDrawer(p);
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }

    static ObjectPreviewDrawer* createObjectPreviewDrawer(PhysicsObjectType object_type, ObjectPhysicsConfig& config) {
        switch (object_type) {
            case Rectangle: {
                auto p = dynamic_cast<RectanglePhysicsConfig&>(config);
                return new RectanglePreviewDrawer(p);
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }

    static ObjectPhysics* createObjectPhysics(PhysicsObjectType object_type, ObjectPhysicsConfig* config, b2WorldId world_id) {
        switch (object_type) {
            case Rectangle: {
                auto* p = dynamic_cast<RectanglePhysicsConfig*>(config);
                if (nullptr == p) {
                    throw std::runtime_error("ObjectPhysics is wrong type");
                }
                return new RectanglePhysics(world_id, *p); break;
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }
};



#endif //SIMULATIONOBJECTFACTORY_HPP
