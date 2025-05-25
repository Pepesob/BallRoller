#pragma once


#include "Level.hpp"
#include "StateMachine.hpp"
#include "Screen.hpp"
#include "Camera.hpp"



class SimulationStage: public State {
public:
    explicit SimulationStage(StateMachine& state_machine, std::unique_ptr<Level>, Screen* screen, Camera* camera);

    void onInit() override;


    void onUpdate() override;

    void clickTest();

    void onNext() override;

    void draw(Screen* screen, Camera* camera);

    void handleEvents();

private:
    std::unique_ptr<Level> level;
    Screen* screen;
    Camera* camera;
    sf::Vector2i mouse_pos;
    StateMachine& state_machine;
    bool mouse_left_pressed = false;
    bool go_back_to_placement = false;
};
