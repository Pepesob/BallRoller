//
// Created by sp on 14.05.2025.
//

#pragma once
#include <iostream>

#include "Camera.hpp"
#include "Screen.hpp"
#include "StateMachine.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "ObjectPlacementStage.hpp"


class MainMenuStage: public State {
public:
    MainMenuStage(StateMachine& state_machine, Screen* screen, Camera* camera): screen(screen), camera(camera), state_machine(state_machine) {}

    void onInit() override {
        ImGui::SFML::Init(*this->screen->getWindow());
    }

    void onUpdate() override {
        this->handleEvents();
        ImGui::SFML::Update(*this->screen->getWindow(), deltaClock.restart());
        ImVec2 windowSize = ImGui::GetIO().DisplaySize;
        ImVec2 buttonSize = ImVec2(200, 40);
        float totalHeight = buttonSize.y * 3 + 20 * 2;  // 3 buttons + 2 spacings
        float x = (windowSize.x - buttonSize.x) * 0.5f;
        float y = (windowSize.y - totalHeight) * 0.5f;

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("Main Page", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoCollapse);

        ImGui::SetCursorPos(ImVec2(x, y - 50));
        ImGui::Text("Welcome to the Simple Page");

        ImGui::SetCursorPos(ImVec2(x, y));
        if (ImGui::Button("Level", buttonSize)) {
            std::string level_name = std::format("resources/levels/Level{}.yaml", this->level_number);
            this->state_machine.switchState(std::make_unique<ObjectPlacementStage>(this->state_machine, std::make_unique<Level>(level_name), screen, camera));
        }

        ImGui::SetCursorPos(ImVec2(x, y + buttonSize.y + 20));
        if (ImGui::Button("Level Builder", buttonSize)) {
            this->state_machine.switchState(std::make_unique<ObjectPlacementStage>(this->state_machine, std::make_unique<Level>(), screen, camera));
        }

        ImGui::SetCursorPos(ImVec2(x, y + (buttonSize.y + 20) * 2));
        if (ImGui::Button("Button 3", buttonSize)) {
            std::cout << "Button 3" << std::endl;
        }

        ImGui::SetCursorPos(ImVec2(x, y + (buttonSize.y + 20) * 3));
        ImGui::PushItemWidth(200);
        ImGui::InputInt("Enter a number", &level_number);
        ImGui::PopItemWidth();

        ImGui::End();
        ImGui::SFML::Render(*this->screen->getWindow());
    }

    void onNext() override {
        ImGui::SFML::Shutdown();
    }

    void handleEvents() {
        while (const std::optional event = this->screen->getWindow()->pollEvent()) {
            this->screen->handleEvent(event);
            ImGui::SFML::ProcessEvent(*this->screen->getWindow(), event.value());
        }
    }

private:
    Screen* screen;
    Camera* camera;
    sf::Clock deltaClock;
    StateMachine& state_machine;

    char inputText[128];
    int level_number=0;
};
