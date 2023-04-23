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


Graph::~Graph() {
for (int i = 0; i < vertices.getSize(); ++i) {
        delete vertices[i];
    }
}

void Graph::print() {
    std::cout<<"Graph: "<<std::endl;
    for(int i = 0; i < vertices.getSize(); ++i) {
        std::cout<<vertices[i]->getCity().getName()<<"-> ";
        for (int j = 0; j < vertices[i]->edges.getSize(); ++j) {
            std::cout<<vertices[i]->edges[j].get_neighbour()->getCity().getName()<<": "<<vertices[i]->edges[j].getDistance()<<" ";
        }
        std::cout<<std::endl;
    }
}

Graph::Vertex Graph::get_vertex(String &name) {
    for (int i = 0; i < vertices.getSize(); ++i) {
        if (vertices[i]->getCity().getName() == name) {
            return *vertices[i];
        }
    }
}

Graph::Vertex &Graph::get_vertex(int x, int y) {
    for (int i = 0; i < vertices.getSize(); ++i) {
        if (vertices[i]->getCity().getX() == x && vertices[i]->getCity().getY() == y) {
            return *vertices[i];
        }
    }
}

void Graph::add_edge(Graph::Vertex &v1, Graph::Vertex &v2, int distance) {
    v1.edges.push_back(*new Edge(&v2, distance));
    v2.edges.push_back(*new Edge(&v1, distance));
}

int Graph::getSize() const {
    return size;
}

City &Graph::get_start() {
    return vertices[0]->getCity();
}

Graph::Vertex &Graph::get_vertex(int index) {
    return *vertices[index];
}





