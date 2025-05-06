//
// Created by sp on 27.04.2025.
//

#ifndef AVAILABLELEVELOBJECTS_HPP
#define AVAILABLELEVELOBJECTS_HPP
#include <iostream>
#include <string>
#include <vector>

#include "SimulationObjectFactory.hpp"
#include "simulation/base_drawers/SimulationObjectDrawer.hpp"
#include "simulation/physics/Simulation.hpp"

struct ObjectAndDrawer {
    SimulationObjectBase* object;
    ISimulationObjectDrawer* drawer;
};




class AvailableLevelObjects {

public:
    enum LevelObjectState {
        NOT_PLACED, PREVIEW, PLACED
    };

    virtual ~AvailableLevelObjects() {
        this->clear();
    }

    // explicit AvailableLevelObjects(const YAML::Node& config) {
    // }

    AvailableLevelObjects() {
        // this->objectTags.emplace_back("MainBall");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Accelerator");
        this->objectTags.emplace_back("Accelerator");
        this->objectTags.emplace_back("Accelerator");

        for (int i=0; i<this->objectTags.size(); i++) {
            SimulationObjectFactory factory;
            this->objects.push_back(factory.createSimulationObject(this->objectTags[i]));
            this->drawers.push_back(factory.createSimulationObjectDrawer(this->objectTags[i], this->objects[i]));
            this->objectPlaced.push_back(NOT_PLACED);
        }
    }

    virtual void select(int index) {
        if (index < 0 || index >= this->objectTags.size()) {
            this->selected = -1;
            return;
        }
        this->selected = index;
    }

    virtual void set(Vector2D position, float rotation) {
        if (this->selected == -1) {
            return;
        }
        this->objects[this->selected]->setInitialPosition(position);
        this->objects[this->selected]->setInitialRotation(rotation);
    }

    virtual void unplace(int index) {
        if (index < 0 || index >= this->objectTags.size()) {
            return;
        }
        this->objectPlaced[index] = NOT_PLACED;
    }

    virtual void place(Vector2D position, float rotation) {
        if (this->selected == -1) {
            return;
        }
        this->set(position, rotation);
        this->objectPlaced[this->selected] = PLACED;
        this->selected = -1;
    }

    virtual bool isPlaced(int index) {
        if (index < 0 || index >= this->objectTags.size()) {
            return false;
        }
        return this->objectPlaced[index] == PLACED;
    }

    virtual void draw(Screen* screen, Camera* camera) {
        for (int i=0; i<this->objectTags.size(); i++) {
            if (this->objectPlaced[i] == PLACED) {
                drawers[i]->draw(screen, camera);
            }
        }
        if (selected != -1) {
            drawers[this->selected]->draw(screen, camera);
        }
    }

    virtual void addToSimulation(B2dSimulation& simulation) {
        for (int i=0; i<this->objectTags.size(); i++) {
            if (this->objectPlaced[i] == PLACED) {
                simulation.addObject(*this->objects[i]);
            }
        }
    }

    virtual int size() {
        return this->objectTags.size();
    }

    void clear() {
        this->objectTags.clear();
        for (int i=0; i<this->objectTags.size(); i++) {
            delete this->objects[i];
            delete this->drawers[i];
        }
        this->objects.clear();
        this->drawers.clear();
        this->objectPlaced.clear();
    }

    virtual void save(std::string file_name) {
    }

    int currentPreviewIndex = -1;
    int selected = -1;

protected:
    std::vector<std::string> objectTags;
    std::vector<SimulationObjectBase*> objects;
    std::vector<ISimulationObjectDrawer*> drawers;
    std::vector<LevelObjectState> objectPlaced;
};

class InfiniteLevelObjects: public AvailableLevelObjects {
public:
    InfiniteLevelObjects() {
        this->objectTags.clear();
        this->objects.clear();
        this->drawers.clear();
        this->objectPlaced.clear();

        this->objectTags.emplace_back("MainBall");
        this->objectTags.emplace_back("Rectangle");
        this->objectTags.emplace_back("Accelerator");
        this->objectTags.emplace_back("Goal");

        int i=0;
        for (const auto& tag: objectTags) {
            SimulationObjectFactory factory;
            this->objects.push_back(factory.createSimulationObject(tag));
            this->drawers.push_back(factory.createSimulationObjectDrawer(tag, this->objects[i]));
            this->objectPlaced.push_back(NOT_PLACED);
            i++;
        }
    }

    bool isPlaced(int index) {
        return false;
    }

    void place(Vector2D position, float rotation) override {
        if (this->selected == -1) {
            return;
        }
        SimulationObjectFactory factory;
        SimulationObjectBase* base = factory.createSimulationObject(this->objectTags[this->selected]);
        base->setInitialPosition(position);
        base->setInitialRotation(rotation);
        this->objects_for_simulation.push_back(base);
        this->drawers_for_simulation.push_back(factory.createSimulationObjectDrawer(this->objectTags[this->selected], base));
    }

    void draw(Screen *screen, Camera *camera) override {
        for (auto drawer: this->drawers_for_simulation) {
            drawer->draw(screen, camera);
        }
        if (selected != -1) {
            drawers[this->selected]->draw(screen, camera);
        }
    }

    void addToSimulation(B2dSimulation& simulation) override {
        for (auto obj: this->objects_for_simulation) {
            simulation.addObject(*obj);
        }
    }

    void save(std::string file_name) override {
        saveCurrentWorld(objects_for_simulation, file_name);
    }

    std::vector<SimulationObjectBase*> objects_for_simulation;
    std::vector<ISimulationObjectDrawer*> drawers_for_simulation;
};



#endif //AVAILABLELEVELOBJECTS_HPP
