#include <iostream>
#include "core/header/ui/SfmlApp.h"
#include "core/header/Map.h"
#include "core/header/Hash.h"
#include "core/header/MapDAO.h"


using namespace std;

void SfmlTest() {
    SfmlApp* app = new SfmlApp();
    app->Run();
}

void GraphTest() {
    Map* map = new Map();
    map->AddCity("A", 0, 0, 1);
    map->AddCity("B", 0, 0, 1);
    map->AddCity("C", 0, 0, 1);

    map->AddRoute("A", "B");
    map->AddRoute("A", "C");
    map->AddRoute("B", "C");

}



Map CitiDAOTest(){
    MapDAO citiDao;
    Map* map = citiDao.InitMap();
   return *map;

}

int main() {

    SfmlTest();

    //GraphTest();

    return 0;
}
