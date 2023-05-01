//
// Created by hubert on 01.05.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_PRIORITY_QUEUE_H
#define SHORTEST_WAY_TO_THE_CITY_PRIORITY_QUEUE_H
#include "Vector.h"


template<typename T>
class Priority_queue {
private:
    class Node {
    public:
        T value;
        int priority;
        Node(){
            this->value = nullptr;
            this->priority = 0;
        }
        Node(T value, int priority) {
            this->value = value;
            this->priority = priority;
        }
        ~Node() {
        }
    };
    Vector<Node*> nodes;
    int size;
public:
    int back_priority(){
        return nodes[size-1]->priority;
    }
    T back_value(){
        T value = nodes[--size]->value;
        nodes.delete_element(size);
        return value;
    }
    bool is_empty() {
        if (size == 0) return true;
        return false;
    }
    void push(T value, int priority) {
        Node *node = new Node(value, priority);
        nodes.push_back(node);
        for(int i=nodes.getSize()-1;i>0;i--){
            if(nodes[i]->priority > nodes[i-1]->priority){
                Node *temp = nodes[i];
                nodes[i] = nodes[i-1];
                nodes[i-1] = temp;
            }
        }
        size++;
    }
    void print(){
        for(int i=0;i<nodes.getSize();i++){
            std::cout<<nodes[i]->value<<": "<<nodes[i]->priority<<std::endl;
        }
    }
    Priority_queue() {
        this->size = 0;
    }
    ~Priority_queue() {
        for (int i = 0; i < nodes.getSize(); ++i) {
            delete nodes[i];
        }
    }
};


#endif //SHORTEST_WAY_TO_THE_CITY_PRIORITY_QUEUE_H
