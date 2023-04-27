//
// Created by hubert on 21.04.2023.
//

#ifndef SHORTEST_WAY_TO_THE_CITY_MAP_H
#define SHORTEST_WAY_TO_THE_CITY_MAP_H

#include "City.h"
#include "Vector.h"

class Map {
private:
    char **map;
    int width=0;
    int height=0;
    void find_location(City &city);
public:
    class Point{
    private:
        int x;
        int y;
        int distance;
    public:
        Point(){
            this->x=0;
            this->y=0;
            this->distance=0;
        }
        Point(int x,int y,int distance){
            this->x=x;
            this->y=y;
            this->distance=distance;
        }
        void visit(Vector<Point> &visited){
            visited.push_back(*this);
            distance++;
        }
        bool operator==(const Point& other) const{
            return x==other.x && y==other.y;
        }
        void setX(int x) {
            Point::x = x;
        }
        void setY(int y) {
            Point::y = y;
        }
        void setDistance(int distance) {
            Point::distance = distance;
        }
        int getX() const {
            return x;
        }
        int getY() const {
            return y;
        }
        int getDistance() const {
            return distance;
        }
        void increase_distance(){
            distance++;
        }
        friend std::ostream &operator<<(std::ostream &os, const Point &point) {
            os << "x: " << point.x << " y: " << point.y << " distance: " << point.distance;
            return os;
        }

    };
    Map();
    void name_of_city_and_location(Vector<City> &cities);
    bool is_city(int x,int y);
    bool is_way(int a, int b);
    int get_width();
    int get_height();
    void setWidth(int width);
    void setHeight(int height);
    void set_size_map();
    void print();
    char* operator[](int index);
    ~Map();
};


#endif //SHORTEST_WAY_TO_THE_CITY_MAP_H
