//
// Created by hubert on 20.04.2023.
//

#include "City.h"

int City::getX() const {
    return x;
}

int City::getY() const {
    return y;
}

const String &City::getName() const {
    return name;
}

void City::setX(int x) {
    City::x = x;
}

void City::setY(int y) {
    City::y = y;
}

void City::setName(const String &name) {
    City::name = name;
}

City::City(int x_location_first_letter, int y_location_first_letter)
: x_location_first_letter(x_location_first_letter), y_location_first_letter(y_location_first_letter) {}

bool City::operator==(const City &other) const {
    if(this->getName()==other.getName()) return true;
    else return false;
}

City::~City() {

}

City::City() {}

int City::getXLocationFirstLetter() const {
    return x_location_first_letter;
}

int City::getYLocationFirstLetter() const {
    return y_location_first_letter;
}

void City::setXLocationFirstLetter(int xLocationFirstLetter) {
    x_location_first_letter = xLocationFirstLetter;
}

void City::setYLocationFirstLetter(int yLocationFirstLetter) {
    y_location_first_letter = yLocationFirstLetter;
}


