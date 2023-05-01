//
// Created by hubert on 30.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
#define SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
#include "List.h"
#define SIZE 10000

//V - value
template<typename V>
class HashMap {
private:
    class Node {
    public:
        int x;
        int y;
        V value;
        Node(int x, int y, const V& value) : x(x), y(y), value(value) {}
        bool operator==(const Node& other) const {
            return x == other.x && y == other.y;
        }
        Node *next=NULL;
    };
    static const int capacity = SIZE;
    Node *table[capacity]; // Tablica haszująca przechowująca pary (klucz, wartość)
    unsigned int hash(int x, int y) const {
        unsigned long hash = 5381;
        hash = ((hash << 5) + hash) + x;
        hash = ((hash << 5) + hash) + y;
        return hash % SIZE;
    }
public:
    HashMap() {
        for (int i = 0; i < SIZE; i++)
            table[i] = NULL;
    }

    void put(int x, int y, V value) {
        unsigned long hashValue = hash(x, y);
        Node* prev = NULL;
        Node* node = table[hashValue];
        while (node != NULL && node->x != x && node->y != y) {
            prev = node;
            node = node->next;
        }
        if (node == NULL) {
            node = new Node(x, y, value);
            if (prev == NULL)
                table[hashValue] = node;
            else
                prev->next = node;
        } else {
            node->value = value;
        }
    }

    V *get(int key1, int key2) const {
        unsigned long hashValue = hash(key1, key2);
        Node* node = table[hashValue];
        while (node != NULL && node->x != key1 && node->y != key2)
            node = node->next;
        if (node == NULL)
            return nullptr;
        else
            return &(node->value);
    }

    ~HashMap() {
        for (int i = 0; i < SIZE; i++) {
            Node* node = table[i];
            while (node != NULL) {
                Node* prev = node;
                node = node->next;
                delete prev;
            }
            table[i] = NULL;
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const HashMap& map) {
        for (int i = 0; i < SIZE; i++) {
            HashMap::Node* node = map.table[i];
            while (node != nullptr) {
                os << "(" << node->x << ", " << node->y << ") -> " << node->value << std::endl;
                node = node->next;
            }
        }
        return os;
    }
};


#endif //SHORTEST_WAY_TO_THE_CITY_HASHMAP_H
