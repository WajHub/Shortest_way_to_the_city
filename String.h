//
// Created by hubert on 20.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_STRING_H
#define SHORTEST_WAY_TO_THE_CITY_STRING_H

#pragma once
#include <iostream>
#define LENGTH_BUFF 256

class String {
private:
    int size=0;
    char *array;
public:
    String();
    String(const String &other);
    void inputString(char buff[LENGTH_BUFF], int size);
    int getSize() const;
    bool operator==(const String& other) const;
    bool isEmpty();
    String& operator=(const String& other);
    friend std::ostream& operator<<(std::ostream& out, const String& string);
    ~String();
};


#endif //SHORTEST_WAY_TO_THE_CITY_STRING_H
