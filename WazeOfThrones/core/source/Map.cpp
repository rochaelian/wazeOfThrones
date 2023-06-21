//
// Created by tsegura on 4/13/2023.
//

#include "../header/Map.h"

int NO_PARENT = -1;

int Map::CityIndex(string cityName) {

    if (this->rootCity == nullptr) {
        return -1;
    }

    City* currentCity = this->rootCity;
    int index = 0;

    while (currentCity != nullptr) {
        if (currentCity->GetName() == cityName) {
            return index;
        }
        currentCity = currentCity->GetNext();
        index++;
    }
    return -1;
}

City *Map::CityFromIndex(int cityIndex) {
    if (cityIndex >= this->cityCount) {
        return nullptr;
    }

    City* currentCity = this->rootCity;
    int cont = 0;

    while (currentCity != nullptr) {
        if (cont == cityIndex) {
            break;
        }
        currentCity = currentCity->GetNext();
        cont++;
    }

    return currentCity;
}

void Map::printMatrix() {
    for(int i = 0; i < 29; i++){
        cout << CityFromIndex(i)->GetName() << " : ";
        for(int j = 0; j < 29; j++ ){
            auto test = GetRoutes()[i][j];

            if(test != nullptr) {
                cout << test->GetDistance() << " ";
            }else{
                cout << "0" << " ";
            }
        }

        cout << "\n";
    }
}

Map::Map() {
    this->table = new Hash();

    this->lastCityIndex = 0;
    this->cityCount = 0;
    this->rootCity = nullptr;
    this->routes = new Route**[CITY_CAPACITY];

    for (int i = 0; i < CITY_CAPACITY; i++)
    {
        routes[i] = new Route*[CITY_CAPACITY];
        for (int j = 0; j < CITY_CAPACITY; j++)
        {
            routes[i][j] = nullptr;
        }
    }
}


void Map::highlightPath(Map map, int from, int to, vector<int> parents, bool isFirstCall)
{
    if (to == NO_PARENT) {
        return;
    }

    if(!isFirstCall) {
        map.GetRoutes()[to][from]->SetIsHighlighted(true);
    }

    highlightPath(map, to, parents[to], parents, false);
    cout << to << " -> ";
}


void Map::dijkstra(Map *map, int from, int to) {
    int nVertices = 29;
    vector<int> shortestDistances(nVertices);
    vector<bool> added(nVertices);

    for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
        shortestDistances[vertexIndex] = INT_MAX;
        added[vertexIndex] = false;
    }

    shortestDistances[from] = 0;
    vector<int> parents(nVertices);

    parents[from] = NO_PARENT;

    for (int i = 1; i < nVertices; i++) {

        int nearestVertex = -1;
        int shortestDistance = INT_MAX;
        for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
            if (!added[vertexIndex] && shortestDistances[vertexIndex] < shortestDistance) {
                nearestVertex = vertexIndex;
                shortestDistance = shortestDistances[vertexIndex];
            }
        }

        if(nearestVertex >= 0) {

            added[nearestVertex] = true;

            for (int vertexIndex = 0; vertexIndex < nVertices; vertexIndex++) {
                auto route = map->GetRoutes()[nearestVertex][vertexIndex];

                if (route != nullptr) {
                    int edgeDistance = route->GetDistance();
                    if (edgeDistance > 0 && ((shortestDistance + edgeDistance) < shortestDistances[vertexIndex])) {
                        parents[vertexIndex] = nearestVertex;
                        shortestDistances[vertexIndex] = shortestDistance + edgeDistance;

                    }
                }
            }
        }
    }

    highlightPath(*map, from, to, parents, true);
}

City* Map::GetRoot() {
    return this->rootCity;
}

Route ***Map::GetRoutes() {
    return this->routes;
}

bool Map::AddCity(string name, float posX, float posY, int index) {
    City* newCity = new City(name, posX, posY, index);
    this->table->addCity(newCity->GetIndex(), newCity);

    // Root case
    if (this->rootCity == nullptr) {
        this->rootCity = newCity;
        this->cityCount++;
        return true;
    }

    if (CityIndex(name) != -1) {
        return false;
    }

    City* currentCity = this->rootCity;
    while (currentCity->GetNext() != nullptr) {
        currentCity = currentCity->GetNext();
    }

    currentCity->SetNext(newCity);
    this->cityCount++;
}

bool Map::AddRoute(string from, string to) {
    int fromIndex = CityIndex(from);
    int toIndex = CityIndex(to);

    // Make sure the nodes exist in the graph
    if (fromIndex == -1 || toIndex == -1) {
        return false;
    }

    City* fromCity = CityFromIndex(fromIndex);
    City* toCity = CityFromIndex(toIndex);

    float dist = sqrt(pow(fromCity->GetPosX() - toCity->GetPosX(), 2) + pow(fromCity->GetPosY() - toCity->GetPosY(), 2));
    float time = dist / 5;

    // Double side route
    Route* newRoute = new Route("", dist, time);
    this->routes[fromIndex][toIndex] = newRoute;
    this->routes[toIndex][fromIndex] = newRoute;
    return true;
}

void Map::ClearHighlights() {
    City* currentCity = this->rootCity;

    while (currentCity != nullptr) {
        currentCity->SetIsHighlighted(false);
        currentCity = currentCity->GetNext();
    }

    for (int i = 0; i < CITY_CAPACITY; i++) {
        for (int j = 0; j < CITY_CAPACITY; j++) {
            if (routes[i][j] == nullptr) {
                continue;
            }

            routes[i][j]->SetIsHighlighted(false);
        }
    }
}

void Map::HighlightAdjacentCities(string from) {
    ClearHighlights();
    int cityIndex = CityIndex(from);

    if (cityIndex != -1) {
        for (int i = 0; i < CITY_CAPACITY; i++) {
            if (routes[cityIndex][i] == nullptr) {
                continue;
            }

            CityFromIndex(i)->SetIsHighlighted(true);
            routes[cityIndex][i]->SetIsHighlighted(true);
        }
    }

}

void Map::Print() {
    for (int i = 0; i < CITY_CAPACITY; i++) {
        City *from = CityFromIndex(i);

        if (from == nullptr) {
            continue;
        }

        std::cout << from->GetName();
        for (int j = 0; j < CITY_CAPACITY; j++) {
            if (routes[i][j] == nullptr) {
                continue;
            }

            City *to = CityFromIndex(j);
            if (to != nullptr) {
                std::cout << " -> " << to->GetName();
            }
        }

        std::cout << std::endl;
    }
}

Hash *Map::getTable() {
    return this->table;
}

int Map::getCityCount() {
    this->cityCount;
}