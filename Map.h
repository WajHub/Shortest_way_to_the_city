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
    int width=0;
    int height=0;
    void find_location(City &city);
public:
    Map();
    void name_of_city_and_location(Vector<City> &cities);
    bool is_city(int x,int y);
    bool is_way(int a, int b);
    bool is_without_way_and_cities(int x, int y, int direction_x[], int direction_y[]);
    int get_width();
    int get_height();
    void setWidth(int width);
    void setHeight(int height);
    void set_size_map();
    void print();
    char* operator[](int index);
    ~Map();
};


#endif //SHORTEST_WAY_TO_THE_CITY_MAP_H
