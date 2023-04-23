//
// Created by hubert on 21.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#define SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#include "List.h"
#include "City.h"
#include "Vector.h"


class Graph {
private:
    class Vertex;
    class Edge {
    private:
        Vertex *neighbour;
        int distance;
    public:
        Edge(Vertex *neighbour, int distance) {
            this->neighbour = neighbour;
            this->distance = distance;
        }
        Edge(){
            this->neighbour = nullptr;
            this->distance = 0;
        }
        Vertex *get_neighbour(){
            return neighbour;
        }
        int getDistance() const {
            return distance;
        }
    };
    class Vertex{
    private:
        City city;
    public:
        Vector<Edge> edges;
        Vertex(City &city){
            this->city = city;
        };
        City &getCity()  {
            return city;
        }
        ~Vertex(){

        };
    };
    int size;
    Vector<Vertex*> vertices;
public:
    Graph(Vector<City> &cities);
    Vertex get_vertex(String &name);
    Vertex &get_vertex(int x, int y);
    City &get_start() ;
    int getSize() const;
    void add_edge(Vertex &v1, Vertex &v2, int distance);
    void print();
    ~Graph();
};


#endif //SHORTEST_WAY_TO_THE_CITY_GRAPH_H
