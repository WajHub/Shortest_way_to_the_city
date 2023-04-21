//
// Created by hubert on 21.04.2023.
//

#include "Graph.h"

Graph::Graph(Vector<City> &cities) {
    this->size = cities.getSize();
    for (int i = 0; i < cities.getSize(); ++i) {
        vertices.push_back(new Vertex(cities[i]));
    }
}



void Graph::add_edge(City &city1, City &city2, int distance) {
//    adjacencyList[city1.get_id()].push_back(city2);
//    adjacencyList[city1.get_id()].set_distance(distance);
}

Graph::~Graph() {
for (int i = 0; i < vertices.getSize(); ++i) {
        delete vertices[i];
    }
}

void Graph::print() {

}


