//
// Created by hubert on 20.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_VECTOR_H
#define SHORTEST_WAY_TO_THE_CITY_VECTOR_H

template<typename T>
class Vector {
private:
    int size=0;
    int capacity=2;
    T *array;
    void reallocate();
public:
    T& operator[](int n);
    void push_back(T &obj);
    void push_back_value(T obj);
    int getSize() const;
    Vector();
    Vector(int size);
    ~Vector();
};

template<typename T>
Vector<T>::Vector(int size) {
    this->size = size;
    capacity = size*2;
    array = new T[capacity];
}


template<typename T>
T &Vector<T>::operator[](int n) {
    return array[n];
}


template<typename T>
void Vector<T>::push_back(T &obj) {
    if(size==capacity){
        reallocate();
    }
    array[size++] = obj;
}

template<typename T>
void Vector<T>::push_back_value(T obj) {
    if(size==capacity){
        reallocate();
    }
    array[size++] = obj;
}

template<typename T>
void Vector<T>::reallocate() {
    capacity = capacity*2;
    T* new_arr = new T[capacity];
    for(int i=0;i<size;i++){
        new_arr[i] = array[i];
    }
    delete [] array;
    array = new T[capacity];
    for(int i=0;i<size;i++){
        array[i] = new_arr[i];
    }
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
