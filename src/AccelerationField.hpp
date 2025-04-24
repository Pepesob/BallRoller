//
// Created by sp on 24.04.2025.
//

#ifndef ACCELERATIONFIELD_HPP
#define ACCELERATIONFIELD_HPP

struct Vector2D {
    float x;
    float y;
};



class AccelerationField {
public:
    AccelerationField(float x, float y, float w, float h, float rotation, Vector2D acceleration) {
        this->x_m = x;
        this->y_m = y;
        this->w_m = w;
        this->h_m = h;
        this->rotation = rotation;
        this->acceleration = acceleration;
    }

    [[nodiscard]] float getX() const {
        return x_m;
    }

    [[nodiscard]] float getY() const {
        return y_m;
    }

    [[nodiscard]] float getWidth() const {
        return w_m;
    }

    [[nodiscard]] float getHeight() const {
        return h_m;
    }

    [[nodiscard]] float getRotation() const {
        return rotation;
    }

    [[nodiscard]] Vector2D getAcceleration() const {
        return acceleration;
    }

private:
    float x_m, y_m, w_m, h_m, rotation;
    Vector2D acceleration;
};



#endif //ACCELERATIONFIELD_HPP
