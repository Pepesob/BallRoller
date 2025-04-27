//
// Created by sp on 27.04.2025.
//

#ifndef SIMULATIONOBJECTFACTORY_HPP
#define SIMULATIONOBJECTFACTORY_HPP

#include "AccelerationField.hpp"
#include "Drawer.hpp"
#include "common.hpp"


class SimulationObjectFactory {
public:
    static Drawer* createObjectDrawer(PhysicsObjectType object_type, ObjectPhysics* physics) {
        switch (object_type) {
            case TypeRectangle: {
                auto* p = dynamic_cast<RectanglePhysics*>(physics);
                return new RectangleDrawer(p);
            }
            case TypeAccelerationField: {
                auto* p = dynamic_cast<RectanglePhysics*>(physics);
                return new RectangleDrawer(p, sf::Color(255,0,0, 128));
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }

    static Drawer* createObjectDrawer(PhysicsObjectType object_type, Shape* shape) {
        switch (object_type) {
            case TypeRectangle: {
                auto* p = dynamic_cast<Rectangle*>(shape);
                return new RectangleDrawer(p);
            }
            case TypeAccelerationField: {
                auto* p = dynamic_cast<Rectangle*>(shape);
                return new RectangleDrawer(p, sf::Color(255,0,0, 128));
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }

    static ObjectPhysics* createObjectPhysics(PhysicsObjectType object_type, ObjectPhysicsConfig* config, b2WorldId world_id) {
        switch (object_type) {
            case TypeRectangle: {
                auto* p = dynamic_cast<RectanglePhysicsConfig*>(config);
                return new RectanglePhysics(world_id, *p);
            }
            case TypeAccelerationField: {
                auto* p = dynamic_cast<AccelerationFieldPhysicsConfig*>(config);
                return new AccelerationFieldPhysics(world_id, *p);
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }

    static ShapePrototype* createObjectPrototype(PhysicsObjectType object_type, ObjectPhysicsConfig* config) {
        switch (object_type) {
            case TypeRectangle: {
                auto* p = dynamic_cast<RectanglePhysicsConfig*>(config);
                auto* o = new RectanglePrototype();
                o->setSize(p->size);
                return o;
            }
            case TypeAccelerationField: {
                auto* p = dynamic_cast<AccelerationFieldPhysicsConfig*>(config);
                auto* o = new RectanglePrototype();
                o->setSize(p->size);
                return o;
            }
            default: {
                throw std::runtime_error("Unknown object drawer name");
            }
        }
    }
};



#endif //SIMULATIONOBJECTFACTORY_HPP
