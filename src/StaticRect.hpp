//
// Created by sp on 04.04.2025.
//

#ifndef STATICRECT_HPP
#define STATICRECT_HPP

class StaticRect {
public:
    StaticRect(float x, float y, float w, float h);

    [[nodiscard]] float getX() const;
    [[nodiscard]] float getY() const;
    [[nodiscard]] float getW() const;
    [[nodiscard]] float getH() const;

private:
    float x_m, y_m, w_m, h_m;
};



#endif //STATICRECT_HPP
