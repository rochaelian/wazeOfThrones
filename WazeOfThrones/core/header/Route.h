//
// Created by tsegura on 4/13/2023.
//

#ifndef WAZEOFTHRONES_ROUTE_H
#define WAZEOFTHRONES_ROUTE_H

#include <string>

using namespace std;

class Route {
private:
    string name;
    float distance;
    float time;
    bool isHighlighted;

public:
    explicit Route(string name, float distance, float time);

    float GetDistance();
    void SetDistance(float value);

    float GetTime();
    void SetTime(float value);

    bool IsHighlighted();
    void SetIsHighlighted(bool value);
};


#endif //WAZEOFTHRONES_ROUTE_H
