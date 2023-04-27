//
// Created by hubert on 21.04.2023.
//
#include "Map.h"
#include <string.h>

char* Map::operator[](int index) {
    return map[index];
}

Map::Map() {

}

int Map::get_width() {
    return width;
}

int Map::get_height() {
    return height;
}

Map::~Map() {
    //delete map from memory
    for(int i=0;i<height;i++){
        if(map[i]!= nullptr){
            delete  map[i];
        }

    }
    if(map!= nullptr){
        delete [] map;
    }

}

void Map::setWidth(int width) {
    Map::width = width;
}
void Map::setHeight(int height) {
    Map::height = height;
}

void Map::set_size_map() {
    map=new char*[height];
    for(int i=0;i<height;i++){
        map[i]=new char[width];
    }
}


bool Map::is_way(int x, int y) {
    if(x>=width || y>=height || x<0 || y<0){
        return false;
    }
    else {
        if(map[y][x]=='#') return true;
        else return false;
    }
}


bool Map::is_city(int x, int y) {
    if(x>=width || y>=height || x<0 || y<0){
        return false;
    }
    else {
        if(map[y][x]=='*') return true;
        else return false;
    }
}
void Map::name_of_city_and_location(Vector<City> &cities) {
    for(int i=0;i<cities.getSize();i++){
        String name;
        char buff[LENGTH_BUFF];
        memset(buff, '\0', sizeof(buff));
        int it=0;
        int x = cities[i].getXLocationFirstLetter();
        int y = cities[i].getYLocationFirstLetter();
        while(map[y][x]!='\n' && map[y][x]!='*' && map[y][x]!='#' && map[y][x]!='.' && x<width){
            buff[it++]=map[y][x];
            x++;
        }
        name.inputString(buff,it);
        cities[i].setName(name);
        find_location(cities[i]);
    }
}

void Map::find_location(City &city) {
    const int direction_x[]={-1,0,1,1,1,0,-1,-1};
    const int direction_y[]={-1,-1,-1,0,1,1,1,0};
    for(int j=0;j<8;j++){
        int x = city.getXLocationFirstLetter();
        int y = city.getYLocationFirstLetter();
        x+=direction_x[j];
        y+=direction_y[j];
        if(is_city(x,y)){
            city.setX(x);
            city.setY(y);
            return;
        }
    }
    for(int j=0;j<8;j++){
        int x = city.getXLocationFirstLetter()+city.getName().getSize()-2;
        int y = city.getYLocationFirstLetter();
        x+=direction_x[j];
        y+=direction_y[j];
        if(is_city(x,y)){
            city.setX(x);
            city.setY(y);
            return;
        }
    }
}

void Map::print() {
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            std::cout<<map[i][j];
        }
        std::cout<<std::endl;
    }
}



