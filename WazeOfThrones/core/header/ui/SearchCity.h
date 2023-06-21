//
// Created by tsegura on 4/17/2023.
//

#ifndef WAZEOFTHRONES_SEARCHCITY_H
#define WAZEOFTHRONES_SEARCHCITY_H
#include <SFML/Graphics.hpp>
#include <math.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "../Map.h"
#include "CheckAdjacentCities.h"
#include "../../AppVariables.h"

using namespace sf;
using namespace std;

class SearchCity {

public:
    void ShowUI(AppVariables* appVariables, RenderWindow &window, View &view ) {
        ImGui::Begin("Buscar Ciudad");
        ImGui::BeginGroup();

        ImGui::InputText("Ciudad", appVariables->GetCity(), 100);

        if (ImGui::Button("Buscar", ImVec2(100, 40))) {
            int indexCity = appVariables->GetMap()->CityIndex(*appVariables->GetCity());
            City *cityFound = appVariables->GetMap()->getTable()->getCity(appVariables->GetMap()->getTable()->hashing(indexCity), *appVariables->GetCity());

            if(cityFound != nullptr){
                appVariables->SetCameraPosition(Vector2f(cityFound->GetPosX(), cityFound->GetPosY()));
                appVariables->SetCameraZoom(0.6f);
            }
        }

        ImGui::EndGroup();
        ImGui::End();
    }
};


#endif //WAZEOFTHRONES_SEARCHCITY_H
