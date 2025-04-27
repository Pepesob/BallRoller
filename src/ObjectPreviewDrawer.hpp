//
// Created by sp on 27.04.2025.
//

#ifndef OBJECTPREVIEWDRAWER_HPP
#define OBJECTPREVIEWDRAWER_HPP
#include "common.hpp"
#include "Drawer.hpp"


class ObjectPreviewDrawer: public Drawer {

public:
    void setPosition(Vector2D v) {
        this->position = v;
    }
    void setRotation(float rotation) {
        this->rotation = rotation;
    }
protected:
    Vector2D position{};
    float rotation=0;
};



#endif //OBJECTPREVIEWDRAWER_HPP
