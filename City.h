//
// Created by hubert on 20.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_CITY_H
#define SHORTEST_WAY_TO_THE_CITY_CITY_H
#include "String.h"

class City {
private:
    int x;
    int y;
    int x_location_first_letter;
    int y_location_first_letter;
    String name;
public:
    City();
    City(int x_location_first_letter, int y_location_first_letter);
    bool operator==(const City& other) const;
    virtual ~City();
    void setX(int x);
    void setY(int y);
    void setName(const String &name);
    int getXLocationFirstLetter() const;
    int getYLocationFirstLetter() const;

    void setXLocationFirstLetter(int xLocationFirstLetter);

    void setYLocationFirstLetter(int yLocationFirstLetter);

    int getX() const;
    int getY() const;
    const String &getName() const;
};


#endif //SHORTEST_WAY_TO_THE_CITY_CITY_H
