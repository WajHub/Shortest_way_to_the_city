#include <iostream>
#include <string.h>
#include <fstream>
#include "Vector.h"
#include "City.h"
#include "Map.h"
#include "Graph.h"


#include <chrono>
using namespace std;
using namespace std::chrono;


int convert_to_int(char *buff){
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
    memset(buff, '\0', sizeof(buff));
    while(std::cin.get(ch) && ch!=' '){
        buff[it]=ch;
        it++;
    }
    int tmp=convert_to_int(buff);
    map.setWidth(tmp);
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

void read_amount(int &amount){
    char buff[LENGTH_BUFF];
    char ch=' ';
    int it=0;
    memset(buff, '\0', sizeof(buff));
    while(std::cin.get(ch) && ch!='\n'){
        buff[it]=ch;
        it++;
    }
    amount = convert_to_int(buff);
}

void read_name(String &name){
    char buff[LENGTH_BUFF];
    char ch=' ';
    int it=0;
    memset(buff, '\0', sizeof(buff));
    while(std::cin.get(ch) && ch!=' '){
        buff[it]=ch;
        it++;
    }
    name.inputString(buff,it);
}

void add_airline(Graph &graph){
    int amount_airline_connections=0;
    read_amount(amount_airline_connections);
    for(int i=0;i<amount_airline_connections;i++){
        String city1;
        String city2;
        int distance;
        read_name(city1);
        read_name(city2);
        read_amount(distance);
        graph.add_edge_one_direction(graph.get_vertex(city1),graph.get_vertex(city2),distance);
    }
}

void run_order(Graph &graph){
    int amount_orders=0;
    read_amount(amount_orders);
    for(int i=0;i<amount_orders;i++){
        String city1;
        String city2;
        int order;
        read_name(city1);
        read_name(city2);
        read_amount(order);
        graph.dijkstra(city1,city2, order);
    }
}

void bfs(Map &map, Graph &graph){
    int direction_x[4] = {-1, 0, 1, 0};
    int direction_y[4] = {0, -1, 0, 1};
    int map_height= map.get_height();
    int map_width= map.get_width();
    int graph_size= graph.getSize();
    bool **visited_city;
    visited_city = new bool*[map.get_height()];
    bool **visited_way;
    visited_way = new bool*[map.get_height()];
    for(int j=0;j<map_height;j++){
        visited_way[j]=new bool[map_width];
        visited_city[j]=new bool[map_width];
    }
    for(int j=0;j<map_height;j++){
        for(int i=0;i<map_width;i++){
            visited_city[j][i]=false;
        }
    }
    for(int i = 0; i < graph_size; i++){
        for(int z=0;z<map_height;z++){
            for(int j=0;j<map_width;j++){
                visited_way[z][j]=false;
            }
        }
        City *city = &graph.get_vertex(i).getCity();
        int x = city->getX();
        int y = city->getY();
        visited_way[y][x]=true;
        List<Map::Point> points;
        Map::Point point(x,y,0);
        points.push(point);
        auto start = high_resolution_clock::now(); //początkowy czas
        while(!points.isEmpty()){
            point = points.get_element(1);
            points.delete_element(1);
            //Visit point
            point.increase_distance();
            visited_way[point.getY()][point.getX()]=true;
            for(int j=0;j<4;j++){
                x = point.getX()+direction_x[j];
                y = point.getY()+direction_y[j];
                if (map.is_way(x, y)) {
                    if (!visited_way[y][x]) {
                        Map::Point new_point(x, y, point.getDistance());
                        points.push(new_point);
                    }
                } else if (map.is_city(x, y) && !visited_way[y][x]) {
                    if (graph.get_vertex(x, y).getId() > i) {
                        graph.add_edge(graph.get_vertex(i),
                                       graph.get_vertex(x, y), point.getDistance());
                        visited_way[y][x] = true;
                    }
                }
            }

        }
    }
    //delete visited_way
    for(int i=0;i<map_height;i++){
        delete [] visited_way[i];
        delete [] visited_city[i];
    }
    delete [] visited_way;
    delete [] visited_city;
}

int main() {
    freopen("input.txt", "r", stdin);
    Map map;
    Vector<City> cities;

    read_map(cities,map);
    map.name_of_city_and_location(cities);
    //Build Graph
    Graph graph(cities);

    bfs(map,graph);

    add_airline(graph);
    graph.print();
    run_order(graph);




    return 0;
}