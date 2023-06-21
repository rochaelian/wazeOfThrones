//
// Created by Jocselyn Aguilar on 14/4/23.
//

#ifndef WAZEOFTHRONES_HASH_H
#define WAZEOFTHRONES_HASH_H


#include "City.h"
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Hash {
public:
    Hash();
    City *getCity(int, string);
    enum {MAX = 29};
    int hashing(int);
    void addCity(int, City*);

private:
    City *city[MAX];
    bool equalSIgnoreCase(string, string);

};


#endif //WAZEOFTHRONES_HASH_H
