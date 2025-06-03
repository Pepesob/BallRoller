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


std::vector<std::string> getFilenamesFromDirectory(const std::string& directoryPath);

class MainMenuStage: public State {
public:
    MainMenuStage(StateMachine& state_machine, Screen* screen, Camera* camera): screen(screen), camera(camera), state_machine(state_machine) {
        this->available_levels = getFilenamesFromDirectory("./resources/levels");
    }

    void onInit() override {
        ImGui::SFML::Init(*this->screen->getWindow());
    }

    void onUpdate() override {
        this->screen->draw(this->screen, this->camera);
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
        ImGui::Text("Ball Roller The Game!");

        ImGui::SetCursorPos(ImVec2(x, y));
        if (ImGui::Button("Level", buttonSize)) {
            std::string level_name = std::format("resources/levels/{}", available_levels[selected_level_index]);
            this->state_machine.switchState(std::make_unique<ObjectPlacementStage>(this->state_machine, std::make_unique<Level>(level_name), screen, camera));
        }

        ImGui::SetCursorPos(ImVec2(x, y + buttonSize.y + 5)); // Slight gap below the first button
        ImGui::PushItemWidth(buttonSize.x);

        if (!available_levels.empty()) {
            const char* current_item = available_levels[selected_level_index].c_str();
            if (ImGui::BeginCombo("##level_select", current_item)) { // Label hidden with "##" to avoid clutter
                for (int n = 0; n < available_levels.size(); n++) {
                    bool is_selected = (selected_level_index == n);
                    if (ImGui::Selectable(available_levels[n].c_str(), is_selected)) {
                        selected_level_index = n;
                    }
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }
        }

        ImGui::PopItemWidth();

        ImGui::SetCursorPos(ImVec2(x, y + buttonSize.y + 35));
        if (ImGui::Button("Level Builder", buttonSize) && !std::string(this->inputText).empty()) {
            this->state_machine.switchState(std::make_unique<ObjectPlacementStage>(this->state_machine, std::make_unique<Level>(), screen, camera, std::string(this->inputText)));
        }

        ImGui::SetCursorPos(ImVec2(x, y + (buttonSize.y + 35) * 1 + buttonSize.y + 5)); // slight gap
        ImGui::PushItemWidth(buttonSize.x);
        ImGui::InputText("##level_name_input", inputText, IM_ARRAYSIZE(inputText));
        ImGui::PopItemWidth();

        ImGui::SetCursorPos(ImVec2(x, y + (buttonSize.y + 35) * 2));
        if (ImGui::Button("Quit", buttonSize)) {
            this->state_machine.shutdown = true;
        }

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

    char inputText[128] = "";
    std::vector<std::string> available_levels;
    int selected_level_index = 0;
};

