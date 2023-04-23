#include <iostream>
#include <string.h>
#include <fstream>
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


void bfs(Map &map, Graph &graph){
    Vector<City>visited_city;
    for(int i=0;i<graph.getSize();i++){
        Vector<Map::Point>visited_way;
        visited_city.push_back(graph.get_vertex(i).getCity());
        City city = graph.get_vertex(i).getCity();
        List <Map::Point> queue;
        Map::Point point(city.getX(),city.getY(),0);
        queue.push(point);
        while(!queue.isEmpty()){
            point = queue.get_element(1);
            queue.delete_element(1);
            point.visit(visited_way);
            int direction_x [4]={-1,0,1,0};
            int direction_y [4]={0,-1,0,1};
            for(int j=0;j<4;j++){
                int x = point.getX()+direction_x[j];
                int y = point.getY()+direction_y[j];
                if(map.is_city(x,y) && !visited_way.exists(Map::Point(x,y,0))){
                    if(!visited_city.exists(graph.get_vertex(x,y).getCity())){
                        graph.add_edge(graph.get_vertex(i),
                                       graph.get_vertex(x,y),point.getDistance());
                        visited_way.push_back(Map::Point(x,y,0));
                    }
                }
                else if(map.is_way(x,y) && !visited_way.exists(Map::Point(x,y,0))){
                    Map::Point new_point(x,y,point.getDistance());
                    queue.push(new_point);
                }
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    Map map;
    Vector<City> cities;
    read_map(cities,map);
    map.name_of_city_and_location(cities);
    Graph graph(cities);
    bfs(map,graph);
    graph.print();
    return 0;
}
