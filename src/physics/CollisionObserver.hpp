//
// Created by sp on 12.04.2025.
//

#ifndef BALLCOLLISIONOBSERVER_HPP
#define BALLCOLLISIONOBSERVER_HPP
#include "ObjectPhysics.hpp"

class CollisionObserver {
public:
    virtual ~CollisionObserver() = default;
    virtual void onContact(ObjectPhysics* object) = 0;
    virtual b2BodyId getBodyId() = 0;
};



#endif //BALLCOLLISIONOBSERVER_HPP
