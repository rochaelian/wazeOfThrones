//
// Created by tsegura on 4/13/2023.
//

#include "../header/City.h"

City::City(string name, float posX, float posY, int index) {
    this->index = index;
    this->name = name;
    this->next = nullptr;
    this->posX = posX;
    this->posY = posY;
}

string City::GetName() {
    return this->name;
}
void City::SetName(string value) {
    this->name = value;
}

City *City::GetNext() {
    return this->next;
}
void City::SetNext(City *value) {
    this->next = value;
}

int City::GetIndex() {
    return this->index;
}
void City::SetIndex(int value) {
    this->index = value;
}

float City::GetPosX() {
    return this->posX;
}
void City::SetPosX(float value) {
    this->posX = value;
}

float City::GetPosY() {
    return this->posY;
}
void City::SetPosY(float value) {
    this->posY = value;
}

bool City::IsHighlighted() {
    return this->isHighlighted;
}

void City::SetIsHighlighted(bool value) {
    this->isHighlighted = value;
}