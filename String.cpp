//
// Created by hubert on 20.04.2023.
//

#include "String.h"

String::String() {
    size=1;
    array = new char[size];
    array[0]='\0';
}

String::String(const String &other) {
    size = other.size;
    array = new char[size];
    for (int i = 0; i < size; i++) {
        array[i] = other.array[i];
    }
    array[size-1] = '\0';
}

void String::inputString(char buff[LENGTH_BUFF], int size) {
    if(array!= nullptr){
        delete [] array;
    }
    this->size=size+1;
    if(buff == nullptr) {
        size = 0;
        array = new char[1];
        array[0] = '\0';
    }
    else {
        array = new char[this->size];
        for (int i = 0; i < size; i++) {
            array[i] = buff[i];
        }
    }
    array[this->size-1]='\0';
}

int String::getSize() const {
    return size;
}

std::ostream& operator<<(std::ostream& out, const String& string)
{
    for(int i=0;i<string.size-1;i++) {
        out << string.array[i];
    }
    return out;
}

bool String::operator==(const String &other) const {
    if(other.getSize()==size){
        for(int i=0;i<size;i++){
            if(other.array[i]==array[i]);
            else return false;
        }
        return true;
    }
    return false;
}

String &String::operator=(const String &other) {
    if(this != &other) {
        delete[] array;
        size = other.size;
        array = new char[size];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[i];
        }
        array[size - 1] = '\0';
    }
    return *this;
}

String::~String() {
    if (array != nullptr) {
        delete[] array;
    }
}

bool String::isEmpty() {
    if(array[0]=='\0') return true;
    return false;
}

char& String::operator[](int index) const {
    if (index >= 0 && index < size - 1) {
        return array[index];
    } else {
        return array[size - 1];
    }
}

bool String::operator!=(const String &other) {
    return !(*this==other);
}

