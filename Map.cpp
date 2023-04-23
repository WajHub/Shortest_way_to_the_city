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
        delete  map[i];
    }
    delete [] map;
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
    if(x>width || y>height || x<0 || y<0){
        return false;
    }
    else {
        if(map[y][x]=='#') return true;
        else return false;
    }
}


bool Map::is_location(int x, int y) {
    if(x>width || y>height || x<0 || y<0){
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
        if(is_location(x,y)){
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
        if(is_location(x,y)){
            city.setX(x);
            city.setY(y);
            return;
        }
    }
}

 Map::Point Map::find_city(int **visited_map,int x, int y) {
//    int direction_x[4]={1,0,-1,0};
//    int direction_y[4]={0,1,0,-1};
//    for(int i=0;i<4;i++){
//        int x1=x+direction_x[i];
//        int y1=y+direction_y[i];
//        if(is_way(x1,y1)){
//            if(visited_map[y1][x1]==0){
//                visited_map[y1][x1]=1;
//                return Point(x1,y1);
//            }
//        }
//    }
}

