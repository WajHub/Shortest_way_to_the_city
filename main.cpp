#include <iostream>
#include <string.h>
#include <fstream>
#include "Vector.h"
#include "City.h"
#include "Map.h"
#include "Graph.h"
#include "Point.h"
#include <list>

#include <fstream>


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
    while((ch=getchar())&& ch!=' '){
        buff[it]=ch;
        it++;
    }
    int tmp=convert_to_int(buff);
    map.setWidth(tmp);
    it=0;
    while((ch=getchar())&& ch!='\n'){
        buff[it]=ch;
        it++;
    }
    map.setHeight(convert_to_int(buff));
    map.set_size_map();
    for(int i=0;i<map.get_height();i++){
        it=0;
        memset(buff, '\0', sizeof(buff));
        for(int j=0;j<map.get_width();j++){
            (ch=getchar());
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
        (ch=getchar());
    }
}

void read_amount(int &amount){
    char buff[LENGTH_BUFF];
    char ch=' ';
    int it=0;
    memset(buff, '\0', sizeof(buff));
    while((ch=getchar())&& ch!='\n'){
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
    while((ch=getchar()) && ch!=' '){
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
//    std::ofstream file("example.txt"); // otwarcie pliku do zapisu
    int direction_x[4] = {1, 0, -1, 0};
    int direction_y[4] = {0, -1, 0, 1};
    int map_height= map.get_height();
    int map_width= map.get_width();
    int graph_size= graph.getSize();
    bool **visited_way;
    visited_way = new bool*[map.get_height()];
    for(int j=0;j<map_height;j++){
        visited_way[j]=new bool[map_width];
    }
    Vector<Point> points;
    for(int i = 0; i < graph_size; i++){
        for(int z=0;z<map_height;z++){
            for(int j=0;j<map_width;j++){
                visited_way[z][j]=false;
            }
        }
        City *city = &graph.get_vertex(i).getCity();
        Point point(city->getX(),city->getY(),0);
        visited_way[point.getY()][point.getX()]=true;
        points.push_back(point);
        while(!points.is_empty()){
            for(int z=0;z<points.getSize();z++) {
//                for(int h=0;h<map_height;h++){
//                    for(int w=0;w<map_width;w++){
//                        if(visited_way[h][w]) file<<"1";
//                        else file<<"0";
//                    }
//                    file<<std::endl;
//                }
//                file<<std::endl;
//                file<<std::endl;
                //Visit point
                points[z].increase_distance();
                //move
                int directions=0;
                point = points[z];
                for(int j=0;j<4;j++){
                    point.setX(point.getX()+direction_x[j]);
                    point.setY(point.getY()+direction_y[j]);
                    if (map.is_way(point.getX(), point.getY())) {
                        if (!visited_way[point.getY()][point.getX()]) {
                            if(directions==0){
                                directions++;
                                points[z].setX(points[z].getX()+direction_x[j]);
                                points[z].setY(points[z].getY()+direction_y[j]);
                                visited_way[points[z].getY()][points[z].getX()] = true;
                            }
                            else{
                                visited_way[point.getY()][point.getX()] = true;
                                points.push_back(Point(point.getX(),point.getY(),point.getDistance()));
                            }
                        }
                    } else if (map.is_city(point.getX(), point.getY())) {
                        if(!visited_way[point.getY()][point.getX()]){
                            if (graph.get_vertex(point.getX(), point.getY()).getId() > i) {
                                graph.add_edge(graph.get_vertex(i),
                                               graph.get_vertex(point.getX(),point.getY()), point.getDistance());
                                visited_way[point.getY()][point.getX()] = true;
                            }
                        }
                    }
                    point.setX(point.getX() - direction_x[j]);
                    point.setY(point.getY() - direction_y[j]);
                }
                if(directions==0){
                    points.delete_element(z);
                    z--;
                }
            }
        }
    }
    //delete visited_way
    for(int i=0;i<map_height;i++){
        delete [] visited_way[i];
    }
    delete [] visited_way;
//    file.close(); // zamknięcie pliku
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