//
// Created by hubert on 21.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_MAP_H
#define SHORTEST_WAY_TO_THE_CITY_MAP_H


#include "City.h"
#include "Vector.h"

class Map {
private:
    char **map;
    int width;
    int height;
    bool is_location(int x,int y);
    void find_location(City &city);
public:
    Map();
    void name_of_city_and_location(Vector<City> &cities);

    int get_width();
    int get_height();
    void setWidth(int width);
    void setHeight(int height);
    void set_size_map();
    char* operator[](int index);
    ~Map();
};


#endif //SHORTEST_WAY_TO_THE_CITY_MAP_H
