#pragma once

#include "BodyCompound.hpp"
#include "MainBallObject.hpp"
#include "SimulationObjectBase.hpp"

class TeleporterObject: public SimulationObjectBase {
public:
    TeleporterObject(): SimulationObjectBase("Teleporter") {
        this->teleportA.config.isSensor = true;
        this->teleportA.config.size = {0.3, 0.3};

        this->teleportB.config.isSensor = true;
        this->teleportB.config.size = {0.3, 0.3};

        this->compound.addBody(&this->teleportA, {-distance/2, 0}, 0);
        this->compound.addBody(&this->teleportB, {distance/2, 0}, 0);
    }

    void onCollisionBegin(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override {
        if (this->cd_count < this->teleport_cd) return;
        if (auto obj = getObjectAs<MainBallObject>(this->simulation->getAssociatedObject(other_body)); obj != nullptr) {
            if (&this->teleportA == &this_body) {
                this->simulation->teleport(obj->ball, teleportB.getPosition());
            } else {
                this->simulation->teleport(obj->ball, teleportA.getPosition());
            }
            this->cd_count = 0;
        }
    }

    void onCollisionEnd(B2dSimulation &simulation, SimulationBody &this_body, SimulationBody &other_body) override {

    }

    void step() override {
        this->cd_count++;
    }

    std::vector<SimulationBody *> getBodies() override {
        return {&teleportA, &teleportB};
    }

    void applyConfig() override {
        // this->compound.setPosition(this->config["initial_position"].as<Vector2D>());
        // this->compound.setRotation(this->config["initial_rotation"].as<float>());
        this->compound.setTransform(this->config["initial_position"].as<Vector2D>(), this->config["initial_rotation"].as<float>());
    }

    float distance = 1;
    int teleport_cd = 60*5;
    uint64_t cd_count = teleport_cd + 1;
    RectangleBody teleportA;
    RectangleBody teleportB;
};

class TeleporterDrawer: public Drawer {
public:
    explicit TeleporterDrawer(TeleporterObject& teleporter): teleporter(teleporter) {
        drawer.texture = sf::Texture("resources/teleporter_texture.png");
    }

    void draw(Screen *screen, Camera *camera) override {
        this->drawer.size = teleporter.teleportA.config.size;
        drawer.position = this->teleporter.teleportA.getPosition();
        drawer.rotation = this->teleporter.teleportA.getRotation();
        this->drawer.draw(screen, camera);

        this->drawer.size = teleporter.teleportB.config.size;
        drawer.position = this->teleporter.teleportB.getPosition();
        drawer.rotation = this->teleporter.teleportB.getRotation();
        this->drawer.draw(screen, camera);
    }

private:
    TeleporterObject& teleporter;
    RectangleDrawer drawer;
};
