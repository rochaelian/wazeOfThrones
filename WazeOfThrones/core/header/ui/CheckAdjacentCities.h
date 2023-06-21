//
// Created by tsegura on 4/17/2023.
//

#ifndef WAZEOFTHRONES_CHECKADJACENTCITIES_H
#define WAZEOFTHRONES_CHECKADJACENTCITIES_H

#include <SFML/Graphics.hpp>
#include <math.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include <imgui-SFML.h>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include "../Map.h"
#include "../../AppVariables.h"

using namespace sf;
using namespace std;

class CheckAdjacentCities {
public:

    void Clear() {

    }

    void ShowUI(AppVariables* appVariables) {
        ImGui::Begin("Ver ciudades adyascentes");
        ImGui::BeginGroup();

        // Text fields
        ImGui::InputText("Ciudad", appVariables->GetFromCity(), 100);

        if (ImGui::Button("Mostrar Adyacencias", ImVec2(200, 40))) {
            appVariables->GetMap()->HighlightAdjacentCities(*appVariables->GetFromCity());
        }
        if (ImGui::Button("Limpiar", ImVec2(200, 40))) {
            appVariables->GetMap()->ClearHighlights();
        }

        ImGui::EndGroup();
        ImGui::End();
    }
};


#endif //WAZEOFTHRONES_CHECKADJACENTCITIES_H
