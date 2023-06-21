//
// Created by tsegura on 4/13/2023.
//

#include "../header/Route.h"

Route::Route(string name, float distance, float time) {
    this->name = name;
    this->distance = distance;
    this->time = time;
}

float Route::GetDistance() {
    return this->distance;
}
void Route::SetDistance(float value) {
    this->distance = value;
}

float Route::GetTime() {
    return this->time;
}
void Route::SetTime(float value) {
    this->time = value;
}

bool Route::IsHighlighted() {
    return this->isHighlighted;
}
void Route::SetIsHighlighted(bool value) {
    this->isHighlighted = value;
}