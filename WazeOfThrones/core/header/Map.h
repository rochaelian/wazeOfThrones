//
// Created by tsegura on 4/13/2023.
//

#ifndef WAZEOFTHRONES_MAP_H
#define WAZEOFTHRONES_MAP_H

#define CITY_CAPACITY 400

#include <vector>
#include <math.h>

#include "City.h"
#include "Route.h"
#include "iostream"
#include "Hash.h"


class Map {
private:
    int lastCityIndex;
    int cityCount;
    City* rootCity;
    Route*** routes;
    Hash *table;

public:
    explicit Map();

    void highlightPath(Map , int , int , vector<int> parents, bool );

    void dijkstra(Map *map, int from, int to);

    int getCityCount();

    void printMatrix();

    City* GetRoot();
    Route*** GetRoutes();

    int CityIndex(string cityName);

    City* CityFromIndex(int cityIndex);

    bool AddCity(string name, float posX, float posY, int index);

    bool AddRoute(string from, string to);

    Hash *getTable();

    void ClearHighlights();

    void HighlightAdjacentCities(string from);

    void Print();
};


#endif //WAZEOFTHRONES_MAP_H
