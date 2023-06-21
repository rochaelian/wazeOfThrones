//
// Created by tsegura on 4/22/2023.
//

#ifndef WAZEOFTHRONES_APPVARIABLES_H
#define WAZEOFTHRONES_APPVARIABLES_H


#include <vector>
#include "header/Map.h"

#include <SFML/Graphics.hpp>
using namespace sf;

class AppVariables {
private:
    // Visuals
    Vector2f cameraPosition = Vector2f(1000, 800);
    float cameraZoom = 2;

    // Logic
    Map* map;
    City* selectedCity;

    // Static input fields
    string city;
    string fromCity;
    string toCity;

    int menuOption;
    int selectCityOption;
    int selectedRouteOption;

public:
    explicit AppVariables();

    Vector2f GetCameraPosition();
    void SetCameraPosition(Vector2f cameraPosition);

    float GetCameraZoom();
    void SetCameraZoom(float cameraZoom);

    Map *GetMap() const;
    void SetMap(Map *map);

    vector<int> GetAdjacentCities();
    void SetAdjacentCities(vector<int> adjacentCities);

    vector<int> GetPathRoutes();
    void SetPathRoutes(vector<int> pathRoutes);

    string* GetCity();
    void SetCity(string city);

    string* GetFromCity();
    void SetFromCity(string fromCity);

    string* GetToCity();
    void SetToCity(string toCity);

    int GetMenuOption();
    void SetMenuOption(int menuOption);

    int GetSelectCityOption();
    void SetSelectCityOption(int selectCityOption);

    int GetSelectedRouteOption();
    void SetSelectedRouteOption(int selectedRouteOption);
};


#endif //WAZEOFTHRONES_APPVARIABLES_H
