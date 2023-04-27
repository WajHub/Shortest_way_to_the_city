//
// Created by hubert on 20.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_VECTOR_H
#define SHORTEST_WAY_TO_THE_CITY_VECTOR_H

#include <iostream>

template<typename T>
class Vector {
private:
    int size=0;
    int capacity=2;
    T *array;
    void reallocate();
public:
    T& operator[](int n);
    void push_back(const T &obj);
    void delete_element(int index);
    bool exists(const T &obj);
    bool is_empty();
    int getSize() const;
    Vector();
    Vector(int size);
    Vector& operator=(const Vector& other);
    friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
        os << "[";
        for (int i = 0; i < vec.size; ++i) {
            os << vec.array[i];
            if (i < vec.size - 1) {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
    ~Vector();
};

template<typename T>
bool Vector<T>::is_empty() {
    return size==0;
}

template<typename T>
void Vector<T>::delete_element(int index) {
    for(int i=index;i<size-1;i++){
        array[i]=array[i+1];
    }
    size--;
}

template<typename T>
bool Vector<T>::exists(const T &obj) {
    for(int i=0;i<size;i++){
        if(array[i]==obj) return true;
    }
    return false;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this == &other) {
        return *this;
    }

    // Deallocate old memory
    delete[] array;

    size = other.size;
    capacity = other.capacity;
    array = new T[capacity];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }

    return *this;
}

template<typename T>
Vector<T>::Vector(int size) {
    this->size = size;
    capacity = size;
    array = new T[capacity];
}


template<typename T>
T &Vector<T>::operator[](int n) {
    return array[n];
}


template<typename T>
void Vector<T>::push_back(const T &obj) {
    if(size==capacity){
        reallocate();
    }
    array[size++] = obj;
}

template<typename T>
void Vector<T>::reallocate() {
    capacity *= 2;
    T* new_arr = new T[capacity];
    for(int i = 0; i < size; i++){
        new_arr[i] = array[i];
    }
    delete [] array;
    array = new_arr;
}

template<typename T>
int Vector<T>::getSize() const {
    return size;
}

template<typename T>
Vector<T>::Vector() {
    array = new T[2];
}


template<typename T>
Vector<T>::~Vector() {
    if (array != nullptr) {
        delete[] array;
    }
}

#endif //SHORTEST_WAY_TO_THE_CITY_VECTOR_H
