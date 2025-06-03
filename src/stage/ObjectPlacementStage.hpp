#pragma once

#include "Level.hpp"
#include "SimulationStage.hpp"
#include "simulation/objects/AcceleratorObject.hpp"
#include "StateMachine.hpp"



class ObjectPlacementStage: public State {

public:
    ObjectPlacementStage(StateMachine& state_machine, std::unique_ptr<Level> level, Screen* screen, Camera* camera, const std::string& customLevelName="");

    void everyFrameInput();

    void onKeyPressed(const sf::Event::KeyPressed& keyPressed);

    void onMousePressed(const sf::Event::MouseButtonPressed& keyPressed);

    void onMouseMoved(const sf::Event::MouseMoved& mouseMoved);

    void calculateMouseWorldPos();

    void moveObject() const;

    void placeObject();

    void draw();

    void changeObject(int index);

    void onInit() override;

    void onUpdate() override;

    void onNext() override;

    void handleEvents();
private:
    int index = -1;

    int selected_object = -1;

    std::string current_tag;
    SimulationSprite current_sprite {};

    StateMachine& state_machine;
    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    Vector2D world_pos {0,0};
    float rotation_radians = 0;

    sf::CircleShape highlighter;

    std::unique_ptr<Level> level;

    bool switch_to_simulation = false;
    std::string custom_level_name;
    std::unordered_map<std::string, int> tagCounts;
    sf::Clock deltaClock;
};

