//
// Created by Jocselyn Aguilar on 14/4/23.
//

#include "../header/Hash.h"


Hash::Hash() {


    for (int i = 0; i < MAX; i++){
        this->city [i] = nullptr;
    }
}

void Hash::addCity(int index, City *city) {
    if (this->city[index] == nullptr){
        this->city[index] = city;
    }else {
        City * aux = this->city[index];
        while (aux->GetNext() != nullptr){
            aux = aux->GetNext();
        }

        aux->SetNext(city);
    }
}

bool Hash::equalSIgnoreCase(std::string str1, std::string str2) {
    std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
    std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
    return (str1 == str2);
}


City *Hash::getCity(int index, string name) {
    City *city = this->city[index];

    while (city != nullptr){
        if(city->GetName() == name){
            return city;
        }
        city = city->GetNext();
    }

    return nullptr;
}

int Hash::hashing(int num) {
    return (num%(this->MAX - 1));
}