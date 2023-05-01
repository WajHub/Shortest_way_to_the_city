//
// Created by hubert on 21.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#define SHORTEST_WAY_TO_THE_CITY_GRAPH_H
#include "List.h"
#include "City.h"
#include "Vector.h"
#include "HashMap.h"

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
        int id;
        City city;
    public:
        Vector<Edge> edges;
        Vertex(){

        }
        Vertex(City &city, int id){
            this->city = city;
            this->id = id;
        };
        int getId(){
            return id;
        }
        City &getCity()  {
            return city;
        }
        ~Vertex(){

        };
    };
    int size;
    Vector<Vertex*> vertices;
public:
    void dijkstra(String &source, String &destination, int order,HashMap &hash_map);
    Graph(Vector<City> &cities);
    Vertex &get_vertex(String &name);
    Vertex &get_vertex(int x, int y);
    Vertex &get_vertex(int index);
    int getSize() const;
    int getId(const String &name);
    void add_edge(Vertex &v1, Vertex &v2, int distance);
    void add_edge_one_direction(Vertex &v1, Vertex &v2, int distance);
    void print();
    ~Graph();
};


#endif //SHORTEST_WAY_TO_THE_CITY_GRAPH_H
