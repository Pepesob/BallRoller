#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ranges>
#include "simulation/objects/SimulationObjectFactory.hpp"
#include "simulation/base_drawers/SimulationObjectDrawer.hpp"

struct ObjectAndDrawer {
    SimulationObjectBase* object;
    ISimulationObjectDrawer* drawer;
};



// class AvailableObjects {
// public:
//     virtual ~AvailableObjects() = default;
//
//     virtual void place(int index) = 0;
//     virtual void move(int index, Vector2D position, float rotation) = 0;
//     virtual void remove(int index) = 0;
//
//     std::vector<std::string> available_object_tags;
//     std::vector<SimulationSprite> available_sprites;
//     std::vector<SimulationSprite*> placed_sprites;
// };

class AvailableLevelObjects {
public:
    AvailableLevelObjects() {
        this->available_objects["Rectangle"] = 3;
        this->available_objects["Accelerator"] = 3;

        this->available_object_tags.emplace_back("Rectangle");
        this->available_object_tags.emplace_back("Accelerator");
    }

    bool place(const std::string& tag, Vector2D position, float rotation) {
        if (available_objects.contains(tag) && available_objects[tag] > 0) {
            const SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
            sprite.object->config["initial_position"] = position;
            sprite.object->config["rotation"] = rotation;
            sprite.object->applyConfig();
            this->placed_objects.push_back(sprite);
            available_objects[tag]--;
            return true;
        }
        return false;
    }

    [[nodiscard]] std::vector<std::string>& getAvailableObjects() {
        return this->available_object_tags;
    }

    std::vector<std::string> available_object_tags;
    std::map<std::string, int> available_objects;
    std::vector<SimulationSprite> placed_objects;
};
//
// class AvailableLevelObjects: public AvailableObjects {
// public:
//
//     AvailableLevelObjects() {
//         this->available_object_tags.emplace_back("Rectangle");
//         this->available_object_tags.emplace_back("Rectangle");
//         this->available_object_tags.emplace_back("Rectangle");
//         this->available_object_tags.emplace_back("Accelerator");
//         this->available_object_tags.emplace_back("Accelerator");
//         this->available_object_tags.emplace_back("Accelerator");
//
//         for (int i=0; i<this->available_object_tags.size(); i++) {
//             SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(this->available_object_tags[i]);
//             this->available_sprites.push_back(sprite);
//         }
//     }
//
//     void place(int index) override {
//         if (index < 0 || index >= available_sprites.size()) {
//             std::cerr << "index out of bounds" << std::endl;
//             return;
//         }
//         if (SimulationSprite* sprite_ptr = &available_sprites[index]; std::ranges::find(placed_sprites, sprite_ptr) == placed_sprites.end()) {
//             this->placed_sprites.push_back(sprite_ptr);
//         }
//
//     }
//
//     void move(int index, Vector2D position, float rotation) {
//         if (index < 0 || index >= available_sprites.size()) {
//             std::cerr << "index out of bounds" << std::endl;
//             return;
//         }
//         this->remove(index);
//         this->available_sprites[index].object->config["initial_position"] = position;
//         this->available_sprites[index].object->config["initial_rotation"] = rotation;
//         this->available_sprites[index].object->applyConfig();
//     }
//
//     void remove(int index) override {
//         if (index < 0 || index >= available_sprites.size()) {
//             std::cerr << "index out of bounds" << std::endl;
//             return;
//         }
//         SimulationSprite* sprite_ptr = &this->available_sprites[index];
//         if (const auto it = std::ranges::remove(placed_sprites, sprite_ptr).begin(); it != placed_sprites.end()) {
//             placed_sprites.erase(it, placed_sprites.end());
//         }
//     }
//
// };
//

//
//
//
//
// class AvailableLevelObjects {
//
// public:
//
//     virtual ~AvailableLevelObjects() {
//         this->clear();
//     }
//
//     // explicit AvailableLevelObjects(const YAML::Node& config) {
//     // }
//
//     AvailableLevelObjects() {
//         // this->objectTags.emplace_back("MainBall");
//         this->objectTags.emplace_back("Rectangle");
//         this->objectTags.emplace_back("Rectangle");
//         this->objectTags.emplace_back("Rectangle");
//         this->objectTags.emplace_back("Accelerator");
//         this->objectTags.emplace_back("Accelerator");
//         this->objectTags.emplace_back("Accelerator");
//
//         for (int i=0; i<this->objectTags.size(); i++) {
//             SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(this->objectTags[i]);
//             this->objects.push_back(sprite.object);
//             this->drawers.push_back(sprite.drawer);
//             this->objectPlaced.push_back(NOT_PLACED);
//         }
//     }
//
//     virtual void select(int index) {
//         if (index < 0 || index >= this->objectTags.size()) {
//             this->selected = -1;
//             return;
//         }
//         this->selected = index;
//     }
//
//     virtual void set(Vector2D position, float rotation) {
//         if (this->selected == -1) {
//             return;
//         }
//         this->objects[this->selected]->config["initial_position"] = position;
//         this->objects[this->selected]->config["initial_rotation"] = rotation;
//         this->objects[this->selected]->applyConfig();
//     }
//
//     virtual void unplace(int index) {
//         if (index < 0 || index >= this->objectTags.size()) {
//             return;
//         }
//         this->objectPlaced[index] = NOT_PLACED;
//     }
//
//     virtual void place(Vector2D position, float rotation) {
//         if (this->selected == -1) {
//             return;
//         }
//         this->set(position, rotation);
//         this->objectPlaced[this->selected] = PLACED;
//         this->selected = -1;
//     }
//
//     virtual bool isPlaced(int index) {
//         if (index < 0 || index >= this->objectTags.size()) {
//             return false;
//         }
//         return this->objectPlaced[index] == PLACED;
//     }
//
//     virtual void draw(Screen* screen, Camera* camera) {
//         for (int i=0; i<this->objectTags.size(); i++) {
//             if (this->objectPlaced[i] == PLACED) {
//                 drawers[i]->draw(screen, camera);
//             }
//         }
//         if (selected != -1) {
//             drawers[this->selected]->draw(screen, camera);
//         }
//     }
//
//     virtual void addToSimulation(B2dSimulation& simulation) {
//         for (int i=0; i<this->objectTags.size(); i++) {
//             if (this->objectPlaced[i] == PLACED) {
//                 simulation.addObject(*this->objects[i]);
//             }
//         }
//     }
//
//     virtual int size() {
//         return this->objectTags.size();
//     }
//
//     void clear() {
//         this->objectTags.clear();
//         for (int i=0; i<this->objectTags.size(); i++) {
//             delete this->objects[i];
//             delete this->drawers[i];
//         }
//         this->objects.clear();
//         this->drawers.clear();
//         this->objectPlaced.clear();
//     }
//
//     virtual void save(std::string file_name) {
//     }
//
//     int currentPreviewIndex = -1;
//     int selected = -1;
//
// protected:
//
//     enum LevelObjectState {
//         NOT_PLACED, PREVIEW, PLACED
//     };
//     std::vector<std::string> objectTags;
//     std::vector<SimulationObjectBase*> objects;
//     std::vector<ISimulationObjectDrawer*> drawers;
//     std::vector<LevelObjectState> objectPlaced;
// };
//
// class InfiniteLevelObjects: public AvailableObjects {
// public:
//     InfiniteLevelObjects() {
//         this->available_object_tags.emplace_back("MainBall");
//         this->available_object_tags.emplace_back("Rectangle");
//         this->available_object_tags.emplace_back("Accelerator");
//         this->available_object_tags.emplace_back("Goal");
//
//         int i=0;
//         for (const auto& tag: this->available_object_tags) {
//             SimulationObjectFactory factory;
//             SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
//             this->available_sprites.push_back(sprite);
//             i++;
//         }
//     }
//
//     void place(int index) override {
//         if (index < 0 || index >= available_object_tags.size()) {
//             std::cerr << "index out of bounds" << std::endl;
//             return;
//         }
//         std::string tag = this->available_object_tags[index];
//         SimulationSprite sprite = SimulationObjectFactory::createSimulationSprite(tag);
//         sprite.object->config = this->available_sprites[index].object->config;
//         this->placed_sprites_.push_back(sprite);
//         this->placed_sprites.push_back(&this->placed_sprites_[this->placed_sprites_.size()-1]);
//     }
//
//     void move(int index, Vector2D position, float rotation) override {
//         if (index < 0 || index >= available_sprites.size()) {
//             std::cerr << "index out of bounds" << std::endl;
//             return;
//         }
//         this->available_sprites[index].object->config["initial_position"] = position;
//         this->available_sprites[index].object->config["initial_rotation"] = rotation;
//         this->available_sprites[index].object->applyConfig();
//     }
//
//     void remove(int index) override {
//         throw std::logic_error("Not implemented");
//     }
//
//     std::vector<SimulationSprite> placed_sprites_;
// };
//
//

