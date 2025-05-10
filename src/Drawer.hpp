#pragma once

class Screen;
class Camera;

class Drawer {
public:
    virtual ~Drawer() = default;
    virtual void draw(Screen* screen, Camera* camera) = 0;
};
