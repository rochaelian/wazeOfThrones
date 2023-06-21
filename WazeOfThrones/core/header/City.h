//
// Created by tsegura on 4/13/2023.
//

#ifndef WAZEOFTHRONES_CITY_H
#define WAZEOFTHRONES_CITY_H

#include <string>

using namespace std;

class City {
private:
    string name;
    City* next;
    int index;

    float posX;
    float posY;
    bool isHighlighted;

public:
    explicit City(string name, float posX, float posY, int index);

    string GetName();
    void SetName(string value);

    City* GetNext();
    void SetNext(City* value);

    int GetIndex();
    void SetIndex(int value);

    float GetPosX();
    void SetPosX(float value);

    float GetPosY();
    void SetPosY(float value);

    bool IsHighlighted();
    void SetIsHighlighted(bool value);
};


#endif //WAZEOFTHRONES_CITY_H
