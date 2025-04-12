//
// Created by sp on 12.04.2025.
//

#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <map>
#include <box2d/box2d.h>

#include "CollisionObserver.hpp"
#include "MainBallPhysics.hpp"
#include "ObjectPhysics.hpp"


class CollisionManager {
public:
    CollisionManager(b2WorldId world_id, MainBallPhysics* main_ball_physics) {
        this->main_ball_physics = main_ball_physics;
        this->world_id = world_id;
    }

    void collisionSubscribe(CollisionObserver* observer) {
        this->ball_collision_observers[observer->getBodyId()] = observer;
    }
    void collisionUnsubscribe(CollisionObserver* observer) {
        this->ball_collision_observers.erase(observer->getBodyId());
    }

    void collisionNotify() {
        b2ContactEvents contactEvents = b2World_GetContactEvents(this->world_id);
        for (int i = 0; i < contactEvents.beginCount; ++i)
        {
        	b2ContactBeginTouchEvent* beginEvent = contactEvents.beginEvents + i;
            // TODO - right now collisions are only with the main ball, implement getting all world objects and allow collisions with them
            b2BodyId body_a = b2Shape_GetBody(beginEvent->shapeIdA);
            b2BodyId body_b = b2Shape_GetBody(beginEvent->shapeIdB);
            auto it_a = this->ball_collision_observers.find(body_a);
            if (it_a != this->ball_collision_observers.end()) {
                it_a->second->onContact(this->main_ball_physics);
            }
            auto it_b = this->ball_collision_observers.find(body_b);
            if (it_b != this->ball_collision_observers.end()) {
                it_b->second->onContact(this->main_ball_physics);
            }
        }
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

    std::map<b2BodyId, CollisionObserver*, B2IdComp> ball_collision_observers;
    MainBallPhysics* main_ball_physics;
    b2WorldId world_id;
};



#endif //COLLISIONMANAGER_HPP
