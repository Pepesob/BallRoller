//
// Created by sp on 12.04.2025.
//

#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <map>
#include <vector>
#include <box2d/box2d.h>
#include <iostream>
#include "ObjectPhysics.hpp"


class CollisionManager {
public:
    CollisionManager(b2WorldId world_id, std::vector<ObjectPhysics*>* objects=nullptr) {
        this->simulation_objects = objects;
        this->world_id = world_id;
    }

    void collisionNotify() {
        if (this->simulation_objects == nullptr) {
            throw std::runtime_error("collisionNotify called without initializing vector<ObjectPhysics*>");
        }
        b2ContactEvents contactEvents = b2World_GetContactEvents(this->world_id);
        for (int i = 0; i < contactEvents.beginCount; ++i)
        {
        	b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
            b2BodyId body_a = b2Shape_GetBody(beginEvent->shapeIdA);
            b2BodyId body_b = b2Shape_GetBody(beginEvent->shapeIdB);
            std::cout << "Iteration " << i << std::endl;

            ObjectPhysics* obja = this->getObjectOnBodyId(body_a);
            ObjectPhysics* objb = this->getObjectOnBodyId(body_b);
            if (obja == nullptr || objb == nullptr) {
                throw std::runtime_error("Object that collided is not registered!");
            }
            obja->onContact(objb);
            objb->onContact(obja);
        }

        b2SensorEvents sensor_events = b2World_GetSensorEvents(this->world_id);
        for (int i = 0; i < sensor_events.beginCount; ++i)
        {
            b2SensorBeginTouchEvent* beginEvent = sensor_events.beginEvents + i;
            b2BodyId body_a = b2Shape_GetBody(beginEvent->sensorShapeId);
            b2BodyId body_b = b2Shape_GetBody(beginEvent->visitorShapeId);

            ObjectPhysics* obja = this->getObjectOnBodyId(body_a);
            ObjectPhysics* objb = this->getObjectOnBodyId(body_b);
            if (obja == nullptr || objb == nullptr) {
                throw std::runtime_error("Object that collided is not registered!");
            }
            obja->onContact(objb);
            objb->onContact(obja);
        }
    }

    void setObjectPhysicsList(std::vector<ObjectPhysics*>* objects) {
        this->simulation_objects = objects;
    }

private:
    struct B2IdComp {
        bool operator()(const b2BodyId& a, const b2BodyId& b) const {
            // Compare index1 first, if equal, compare world0, and then revision
            if (a.index1 != b.index1) {
                return a.index1 < b.index1;
            }
            if (a.world0 != b.world0) {
                return a.world0 < b.world0;
            }
            return a.revision < b.revision;
        }
    };

    ObjectPhysics* getObjectOnBodyId(b2BodyId body_id) {
        for (auto o: *this->simulation_objects) {
            if (B2_ID_EQUALS(o->getBodyId(), body_id)) {
                return o;
            }
        }
        return nullptr;
    }

    std::vector<ObjectPhysics*>* simulation_objects;
    b2WorldId world_id;
};



#endif //COLLISIONMANAGER_HPP
