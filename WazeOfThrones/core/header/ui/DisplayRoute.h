//
// Created by tsegura on 4/17/2023.
//

#ifndef WAZEOFTHRONES_DISPLAYROUTE_H
#define WAZEOFTHRONES_DISPLAYROUTE_H

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

class DisplayRoute {
public:
    char* items[2] = { "Seleccionar origen", "Seleccionar destino" };
    char* current_item = items[0];

    void Clear() {
        current_item = items[0];
    }

    void ShowUI(AppVariables* appVariables) {
        ImGui::Begin("Mostrar ruta");
        ImGui::BeginGroup();

        // To select which city to pick
        if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
        {
            for (int n = 0; n < IM_ARRAYSIZE(items); n++)
            {
                bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
                if (ImGui::Selectable(items[n], current_item, is_selected)) {
                    current_item = items[n];
                    appVariables->SetSelectCityOption(n);
                }

                if (is_selected) {
                    ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                }
            }
            ImGui::EndCombo();
        }

        // Text fields
        ImGui::InputText("Origen", appVariables->GetFromCity(), 100);
        ImGui::InputText("Destino", appVariables->GetToCity(), 100);

        if (ImGui::Button("Mostrar Ruta", ImVec2(100, 40))) {
            int fromIndex = appVariables->GetMap()->CityIndex(*appVariables->GetFromCity());
            int toIndex = appVariables->GetMap()->CityIndex(*appVariables->GetToCity());
            appVariables->GetMap()->dijkstra(appVariables->GetMap(), fromIndex, toIndex);
        }

        ImGui::EndGroup();
        ImGui::End();
    }
};


#endif //WAZEOFTHRONES_DISPLAYROUTE_H
