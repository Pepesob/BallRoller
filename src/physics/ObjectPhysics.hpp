//
// Created by sp on 12.04.2025.
//

#ifndef OBJECTPHYSICS_HPP
#define OBJECTPHYSICS_HPP

#include "box2d/box2d.h"


class ObjectPhysics {
public:
    virtual ~ObjectPhysics() = default;
    virtual void onContact(ObjectPhysics* object) = 0;
    virtual b2BodyId getBodyId() = 0;
    virtual void step() = 0;

    template<typename T>
    T getObjectAsType() {
        return static_cast<T>(this);
    }
};



#endif //OBJECTPHYSICS_HPP
