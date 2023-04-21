#include <iostream>
#include <string.h>
#include "Vector.h"
#include "City.h"
#include "Map.h"
#include "Graph.h"

int convert_to_int(char buff[LENGTH_BUFF]){
    int it = 0;
    int number = 0;
    while(buff[it]!='\0'){
        number = number*10 +(buff[it]-'0');
        it++;
    }
    memset(buff, '\0', sizeof(buff));
    return number;
}

void read_map(Vector<City> &cities,Map &map){
    char buff[LENGTH_BUFF];
    char ch=' ';
    int it=0;
    while(std::cin.get(ch) && ch!=' '){
        buff[it]=ch;
        it++;
    }
    map.setWidth(convert_to_int(buff));
    it=0;
    while(std::cin.get(ch) && ch!='\n'){
        buff[it]=ch;
        it++;
    }
    map.setHeight(convert_to_int(buff));
    map.set_size_map();
    for(int i=0;i<map.get_height();i++){
        it=0;
        memset(buff, '\0', sizeof(buff));
        for(int j=0;j<map.get_width();j++){
            std::cin.get(ch);
            map[i][j]=ch;
            if(ch!='#' && ch!='.' && ch!='*' && ch!='\n'){
                it++;
                if(it==1){
                    City city;
                    city.setXLocationFirstLetter(j);
                    city.setYLocationFirstLetter(i);
                    cities.push_back(city);
                }
            }
            else it=0;
        }
        std::cin.get(ch);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    Map map;
    Vector<City> cities;
    read_map(cities,map);
    map.name_of_city_and_location(cities);
    Graph graph(cities);

    return 0;
}
