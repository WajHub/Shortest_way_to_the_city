#include <iostream>
#include <cstring>
#include "Vector.h"
#include "City.h"
#include "Map.h"
#include "Graph.h"
#include "Point.h"
#include "HashMap.h"



int convert_to_int(char *buff) {
    int it = 0;
    int number = 0;
    while (buff[it] != '\0') {
        number = number * 10 + (buff[it] - '0');
        it++;
    }
    memset(buff, '\0', sizeof(buff));
    return number;
}

void read_map(Vector<City> &cities, Map &map) {
    char buff[LENGTH_BUFF];
    char ch = ' ';
    int it = 0;
    memset(buff, '\0', sizeof(buff));
    while ((ch = getchar()) && ch != ' ') {
        buff[it] = ch;
        it++;
    }
    int tmp = convert_to_int(buff);
    map.setWidth(tmp);
    it = 0;
    while ((ch = getchar()) && ch != '\n') {
        buff[it] = ch;
        it++;
    }
    map.setHeight(convert_to_int(buff));
    map.set_size_map();
    for (int i = 0; i < map.get_height(); i++) {
        it = 0;
        memset(buff, '\0', sizeof(buff));
        for (int j = 0; j < map.get_width(); j++) {
            (ch = getchar());
            map[i][j] = ch;
            if (ch != '#' && ch != '.' && ch != '*' && ch != '\n') {
                it++;
                if (it == 1) {
                    City city;
                    city.setXLocationFirstLetter(j);
                    city.setYLocationFirstLetter(i);
                    cities.push_back(city);
                }
            } else it = 0;
        }
        (ch = getchar());
    }
}

void read_amount(int &amount) {
    char buff[LENGTH_BUFF];
    char ch = ' ';
    int it = 0;
    memset(buff, '\0', sizeof(buff));
    while ((ch = getchar()) && ch != '\377' && ch != '\n') {
        buff[it] = ch;
        it++;
    }
    amount = convert_to_int(buff);
}

void read_name(String &name) {
    char buff[LENGTH_BUFF];
    char ch = ' ';
    int it = 0;
    memset(buff, '\0', sizeof(buff));
    while ((ch = getchar()) && ch != ' ') {
        buff[it] = ch;
        it++;
    }
    name.inputString(buff, it);
}

void add_airline(Graph &graph,HashMap &hash_map){
    int amount_airline_connections = 0;
    read_amount(amount_airline_connections);
    for (int i = 0; i < amount_airline_connections; i++) {
        String city1;
        String city2;
        int distance;
        read_name(city1);
        read_name(city2);
        read_amount(distance);
        graph.add_edge_one_direction(graph.get_vertex(hash_map.get(city1)), graph.get_vertex(hash_map.get(city2)), distance);
    }
}

void run_order(Graph &graph,HashMap &hash_map) {
    int amount_orders = 0;
    read_amount(amount_orders);
    for (int i = 0; i < amount_orders; i++) {
        String city1;
        String city2;
        int order;
        read_name(city1);
        read_name(city2);
        read_amount(order);
        graph.dijkstra(city1, city2, order,hash_map);
    }
}

void bfs(Map &map, Graph &graph) {
    int direction_x[4] = {1, 0, -1, 0};
    int direction_y[4] = {0, -1, 0, 1};
    int map_height = map.get_height();
    int map_width = map.get_width();
    int graph_size = graph.getSize();
    bool **visited_way;
    visited_way = new bool *[map.get_height()];
    for (int j = 0; j < map_height; j++) {
        visited_way[j] = new bool[map_width];
    }
    List<Point> points;
    for (int i = 0; i < graph_size; i++) {
        City *city = &graph.get_vertex(i).getCity();
        if(!map.is_without_way_and_cities(city->getX(),city->getY(),direction_x,direction_y)){
            Point point(city->getX(), city->getY(), 0);
            for (int z = 0; z < map_height; z++) {
                for (int j = 0; j < map_width; j++) {
                    visited_way[z][j] = false;
                }
            }
            visited_way[point.getY()][point.getX()] = true;
            points.push(point);
            while (!points.isEmpty()) {
                Point *temp_point = &points.get_element(1);
                //Visit point
                temp_point->increase_distance();
                //move
                for (int j = 0; j < 4; j++) {
                    temp_point->setX(temp_point->getX() + direction_x[j]);
                    temp_point->setY(temp_point->getY() + direction_y[j]);
                    if (map.is_way(temp_point->getX(), temp_point->getY())) {
                        if (!visited_way[temp_point->getY()][temp_point->getX()]) {
                            visited_way[temp_point->getY()][temp_point->getX()] = true;
                            points.emplace_back(Point(temp_point->getX(), temp_point->getY(), temp_point->getDistance()));
                        }
                    } else if (map.is_city(temp_point->getX(), temp_point->getY())) {
                        if (!visited_way[temp_point->getY()][temp_point->getX()]) {
                            if (graph.get_vertex(temp_point->getX(), temp_point->getY()).getId() > i) {
                                graph.add_edge(graph.get_vertex(i),
                                               graph.get_vertex(temp_point->getX(), temp_point->getY()),
                                               temp_point->getDistance());
                                visited_way[temp_point->getY()][temp_point->getX()] = true;
                            }
                        }
                    }
                    temp_point->setX(temp_point->getX() - direction_x[j]);
                    temp_point->setY(temp_point->getY() - direction_y[j]);
                }
                points.delete_element(1);
            }
        }
    }
    //delete visited_way
    for (int i = 0; i < map_height; i++) {
        delete[] visited_way[i];
    }
    delete[] visited_way;
}

void build_hash_map(HashMap &hash_map, Vector<City> &cities){
    for (int i = 0; i < cities.getSize(); ++i) {
        hash_map.put(cities[i].getName(), i);
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
    Map map;
    Vector<City> cities;
    HashMap hash_map;

    read_map(cities, map);

    map.name_of_city_and_location(cities);
    //Build Graph
    Graph graph(cities);
    //Build hash map
    build_hash_map(hash_map, cities);

    add_airline(graph,hash_map);

    bfs(map, graph);

//    graph.print();
    run_order(graph,hash_map);



    return 0;
}