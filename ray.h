#pragma once
#include <iostream>
#include "rectangle.h"
#include <string>
using namespace std;

// ray class
class Ray {
    Vec2D ap;
    double slope;
    int direction;
    public:
    Ray();
    Ray(const Vec2D &ap, const double &slope, const int &direction);
    Vec2D get_ap() const;
    double get_slope() const;
    bool get_vertical() const;
    int get_direction() const;
    void set_ap(const Vec2D &new_ap);
    void set_slope(const double &new_slope);
    void set_direction(const int &new_direction);
    friend ostream& operator<< (ostream& outs, const Ray &ray);
    friend istream& operator>> (istream& ins, Ray& ray);
    bool hit(const Rectangle &rect, const bool &output) const;
};
