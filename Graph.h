//
// Created by hubert on 21.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#define SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#include "List.h"
#include "City.h"
#include "Vector.h"

class Edge;

class Graph {
private:
    class Vertex{
    private:
        City city;
    public:
        const City &getCity() const {
            return city;
        }
        Vertex(City &city){
            this->city = city;
        };
        ~Vertex(){

        };

    };
    int size;
    Vector<Vertex*> vertices;
public:
    Graph(Vector<City> &cities);
    void add_edge(City &city1, City &city2, int distance);
    void print();
    ~Graph();
};

class Edge {
private:
    City city1;
    City city2;
    int distance;
};
#endif //SHORTEST_WAY_TO_THE_CITY_GRAPH_H
