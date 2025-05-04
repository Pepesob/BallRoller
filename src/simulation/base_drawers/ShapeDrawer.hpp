//
// Created by sp on 28.04.2025.
//

#ifndef SHAPE_HPP
#define SHAPE_HPP


#include "common.hpp"
#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Screen.hpp"
#include "simulation/physics/SimulationBody.hpp"

class RectangleShape;
class CircleShape;
class SimulationObjectBase;
class B2dSimulation;
class CircleBody;
class RectangleBody;
class SimulationBody;
void collisionNotify(B2dSimulation& simulation);


class RectangleShapeDrawer {
public:
    void drawShape(RectangleBodyConfig config, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {
        auto [w, h] = config.size;
        float zoom = camera->getZoom();
        int psf = screen->getPixelScaleFactor();
        this->shape.setOrigin({w*psf*zoom/2.f, h*psf*zoom/2.f});
        this->shape.setSize({w*psf*zoom, h*psf*zoom});
        this->shape.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({objectPos.x, objectPos.y});
        this->shape.setPosition(v);
        screen->getWindow()->draw(this->shape);
    }

    sf::RectangleShape shape;
};



class CircleShapeDrawer {
public:
    CircleShapeDrawer() {
        const unsigned int texSize = 256;
        sf::Image image;
        image.resize({texSize, texSize},sf::Color::Transparent);

        // Fill image with two colors
        for (unsigned int y = 0; y < texSize; ++y)
        {
            for (unsigned int x = 0; x < texSize; ++x)
            {
                float factor = static_cast<float>(y) / texSize; // Vertical gradient
                unsigned int r = ((1.0f - factor) * 255 + factor * 0);   // From Red to Blue
                unsigned int g = ((1.0f - factor) * 0   + factor * 0);
                unsigned int b = ((1.0f - factor) * 0   + factor * 255);
                image.setPixel({x, y}, sf::Color(r, g, b));
            }
        }

        // Load texture from image
        bool res = this->texture.loadFromImage(image);
        if (!res) {
            throw std::runtime_error("Failed to load texture from image");
        }
    }

    void drawShape(CircleBodyConfig config, Vector2D objectPos, float objectRot, Screen* screen, Camera* camera) {

        float radius = config.radius;
        auto [x, y] = objectPos;
        float psf = screen->getPixelScaleFactor();
        circle.setOrigin({radius*psf*camera->getZoom(), radius*psf*camera->getZoom()});
        circle.setRadius(config.radius * psf * camera->getZoom());
        circle.setRotation(sf::radians(-objectRot));
        sf::Vector2f v = (screen->getScreenMatrix() * camera->getCameraMatrix()).transformPoint({x, y});
        circle.setPosition(v);
        circle.setTexture(&this->texture);
        screen->getWindow()->draw(circle);
    }

    sf::CircleShape circle;
    sf::Texture texture;
};




#endif //SHAPE_HPP
