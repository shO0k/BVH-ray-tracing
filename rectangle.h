#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;
// point class
struct Vec2D {
    double x = 0, y = 0;
    // allows output of a point
    friend ostream& operator<< (ostream& outs, const Vec2D &rhs) {
        return outs << fixed << setprecision(2) << "(" << rhs.x << "," << rhs.y << ")";
    }
    // allows input of a point
    friend istream& operator>> (istream& ins, Vec2D &rhs) {
        return ins >> rhs.x >> rhs.y;
    }
    // allows direct comparison of a point
    bool operator== (const Vec2D &point) const {
        return (x == point.x and y == point.y);
    }
    // allows less than comparison (returns true/false)
    // pseudo implimentation:
    // if point1 < point2 return 1
    // else return 0
    bool operator< (const Vec2D &point) const {
        return (hypot(x,y) < hypot(point.x,point.y));
    }
};
// rectangle class
class Rectangle {
    Vec2D p1;
    Vec2D p2;
    bool isSolid;
    vector <int> children;
    public:
    Rectangle();
    Rectangle(const Vec2D &new_p1, const Vec2D &new_p2, const bool &new_isSolid, const vector<int> &new_children);
    Vec2D get_p1() const;
    Vec2D get_p2() const;
    bool get_isSolid() const;
    vector<int> get_children() const;
    void set_p1(const Vec2D &new_p1);
    void set_p2(const Vec2D &new_p2);
    void set_isSolid(const bool &new_isSolid);
    void set_children(const vector<int> &new_children);
    friend ostream& operator<< (ostream& outs, const Rectangle& rect);
    friend istream& operator>> (istream& ins, Rectangle& rect);
    Vec2D get_tl() const;
    Vec2D get_br() const;
    bool contains_point(const Vec2D &point) const;
    bool contains_rectangle(const Rectangle &rect) const;
    bool overlap(const Rectangle &rect) const;
};
