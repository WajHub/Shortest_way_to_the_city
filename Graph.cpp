//
// Created by hubert on 21.04.2023.
//
#include <iostream>
#include "Graph.h"
#include "Priority_queue.h"

Graph::Graph(Vector<City> &cities) {
    this->size = cities.getSize();
    for (int i = 0; i < cities.getSize(); ++i) {
        vertices.push_back(new Vertex(cities[i],i));
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

Graph::Vertex &Graph::get_vertex(String &name) {
    for (int i = 0; i < vertices.getSize(); ++i) {
        if (vertices[i]->getCity().getName() == name) {
            return *vertices[i];
        }
    }
    return *vertices[0];
}

Graph::Vertex &Graph::get_vertex(int x, int y) {
    for (int i = 0; i < vertices.getSize(); ++i) {
        if (vertices[i]->getCity().getX() == x && vertices[i]->getCity().getY() == y) {
            return *vertices[i];
        }
    }
    return *vertices[0];
}

void Graph::add_edge(Graph::Vertex &v1, Graph::Vertex &v2, int distance) {
    v1.edges.push_back(*new Edge(&v2, distance));
    v2.edges.push_back(*new Edge(&v1, distance));
}

void Graph::add_edge_one_direction(Graph::Vertex &v1, Graph::Vertex &v2, int distance) {
    v1.edges.push_back(*new Edge(&v2, distance));
}


int Graph::getSize() const {
    return size;
}

Graph::Vertex &Graph::get_vertex(int index) {
    return *vertices[index];
}

void Graph::dijkstra(String &source, String &destination, int order,HashMap &hash_map) {
    int min = INT_MAX;
    int id = hash_map.get(source);
    int target_id = hash_map.get(destination);
    int *distance_from_source = new int[vertices.getSize()];
    int *previous = new int[vertices.getSize()];
    for (int i = 0; i < vertices.getSize(); ++i) {
        distance_from_source[i] = INT_MAX;
        previous[i] = -1;
    }
    distance_from_source[id] = 0;
    Priority_queue<Vertex*> queue;
    queue.push(vertices[hash_map.get(source)],0);
    while(!queue.is_empty()){
        Vertex *temp = queue.back_value();
        id=hash_map.get(temp->getCity().getName());
        //Wszyscy sasiedzi sciagnietego z kolejki wierzcholka
        for(int i=0;i< get_vertex(id).edges.getSize();i++){
            Vertex *neighbour = get_vertex(id).edges[i].get_neighbour();
            int neighbour_id = hash_map.get(neighbour->getCity().getName());
            //Jesli dystans od zrodla naszego sasiada jest wieksza niz odleglosc sumy odleglosci calkowitej i krawedzi sasiada
            if(distance_from_source[neighbour_id]>distance_from_source[id]+get_vertex(id).edges[i].getDistance()){
                //zmieniamy calkowita odleglosc od zrolda
                distance_from_source[neighbour_id] = distance_from_source[id]+get_vertex(id).edges[i].getDistance();
                //poprzednik
                previous[neighbour_id] = id;
                queue.push(neighbour,distance_from_source[neighbour_id]);
            }
        }
        if(id==target_id){
            break;
        }
    }
    std::cout<<distance_from_source[target_id]<<" ";
    if(order==1){
        int tmp_id  = previous[target_id];
        int start_id = hash_map.get(source);
        Vector<String> path;
        while(tmp_id!=start_id && tmp_id!=-1){
            path.push_back(vertices[tmp_id]->getCity().getName());
            tmp_id = previous[tmp_id];
        }
        for(int i=path.getSize()-1;i>=0;i--){
            std::cout<<path[i]<<" ";
        }
    }
    std::cout<<std::endl;
    delete[] distance_from_source;
    delete [] previous;
}








