//
// Created by hubert on 30.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
#define SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
#include "String.h"
#define SIZE 174990

class HashMap {
private:
    class Node {
    public:
        String name;
        int value;
        Node(String name, const int& value) : name(name), value(value) {}
        bool operator==(const Node& other) const {
            return name == other.name;
        }
        Node *next=NULL;
    };
    Node **table;

    unsigned int hash(const String& str) const {
        uint32_t h = 0;
        int len = str.getSize();
        for(int i = 0; i < len; i++){
            h += str[i];
            h *= 0x5bd1e995;
            h ^= str[i] >> 15;
        }
        return (unsigned int)(h)%174990;
    }

public:
    HashMap() {
        table = new Node*[SIZE];
        for (int i = 0; i < SIZE; i++) {
            table[i] = NULL;
        }
    }
    void put(String name, int value) {
        unsigned long hashValue = hash(name);
        Node* prev = NULL;
        Node* node = table[hashValue];
        while (node != NULL && node->name != name) {
            prev = node;
            node = node->next;
        }
        if (node == NULL) {
            node = new Node(name, value);
            if (prev == NULL)
                table[hashValue] = node;
            else
                prev->next = node;
        } else {
            node->value = value;
        }
    }

    int get(const String &name) const {
        unsigned long hashValue = hash(name);
        Node* node = table[hashValue];
        while (node != NULL && node->name!= name)
            node = node->next;
        if (node == NULL)
            return -1;
        else
            return node->value;
    }

    ~HashMap() {
        for (int i = 0; i < SIZE; i++) {
            Node* node = table[i];
            while (node != NULL) {
                Node* prev = node;
                node = node->next;
                delete prev;
            }
        }
        delete[] table;
    }
    friend std::ostream& operator<<(std::ostream& os, const HashMap& map) {
        for (int i = 0; i < SIZE; i++) {
            HashMap::Node* node = map.table[i];
            while (node != nullptr) {
                os << "(" << node->name<< ") -> " << node->value << std::endl;
                node = node->next;
            }
        }
        return os;
    }
};


#endif //SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
