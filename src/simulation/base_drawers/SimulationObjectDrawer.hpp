#pragma once

#include "Screen.hpp"
#include "Camera.hpp"

class ISimulationObjectDrawer {
public:
    virtual ~ISimulationObjectDrawer() = default;

    virtual void draw(Screen* screen, Camera* camera) = 0;
};
