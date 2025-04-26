//
// Created by sp on 25.04.2025.
//

#ifndef OBJECTDRAWER_HPP
#define OBJECTDRAWER_HPP
#include "Camera.hpp"
#include "Screen.hpp"


class ObjectDrawer {
public:
    virtual ~ObjectDrawer() = default;
    virtual void draw(Screen* screen, Camera* camera) = 0;
};



#endif //OBJECTDRAWER_HPP
