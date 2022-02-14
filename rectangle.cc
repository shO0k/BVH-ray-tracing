#include <vector>
#include "rectangle.h"
#include "ray.h"
#include <iostream>
using namespace std;
// TO_DO: impliment isSolid bool for contain functions
template <class T>
ostream& operator<<(ostream &outs, const vector<T> &vec) {
    for (const auto &a : vec) outs << a << " ";
    return outs;
}
Rectangle::Rectangle() {}
// constructor for rectangle, bottom left corner, top right corner, bool for rectangle solid/not
Rectangle::Rectangle(const Vec2D &new_p1, const Vec2D &new_p2, const bool &new_isSolid, const vector<int> &new_children) {
    p1 = new_p1;
    p2 = new_p2;
    isSolid = new_isSolid;
    vector<int> children = new_children;
}
// getter for bottom left corner
Vec2D Rectangle::get_p1() const{
    return p1;
}
// getter for top right corner
Vec2D Rectangle::get_p2() const{
    return p2;
}
// getter for bool
bool Rectangle::get_isSolid() const {
    return isSolid;
}

// getter for vector of children
vector<int> Rectangle::get_children() const {
    return children;
}

// setter for bottom left
void Rectangle::set_p1(const Vec2D &new_p1) {
    p1 = new_p1;
}
// setter for top right
void Rectangle::set_p2(const Vec2D &new_p2) {
    p2 = new_p2;
}
// setter for bool
void Rectangle::set_isSolid(const bool &new_isSolid) {
    isSolid = new_isSolid;
}

// setter for vector of children
void Rectangle::set_children(const vector<int> &new_children) {
    for (int x : new_children) children.push_back(x);
}
// allows user to output a rectangle
ostream& operator<< (ostream &outs, const Rectangle &rect) {
    if (rect.isSolid) {
        outs << rect.p1 << " to " << rect.p2 << " SOLID";
    }
    else outs << rect.p1 << " to " << rect.p2 << " NOT SOLID Children: " << rect.children;
    return outs;
}
// allows user to input a rectangle
istream& operator>> (istream &ins, Rectangle &rect) {
    ins >> rect.isSolid >> rect.p1 >> rect.p2;
    return ins;
}
// generates the coordinate of the top left corner
Vec2D Rectangle::get_tl() const {
    Vec2D output;
    output.x = p1.x;
    output.y = p2.y;
    return output;
}
// generates the coordinate of the bottom right corner
Vec2D Rectangle::get_br() const {
    Vec2D output;
    output.x = p2.x;
    output.y = p1.y;
    return output;
}
// checks if a point is contained within a rectangle
// rect.contains_point(point);
bool Rectangle::contains_point(const Vec2D &point) const {
    return ((point.x >= p1.x and point.x <= p2.x)
            and (point.y >= p1.y and point.y <= p2.y));
}
// checks if a rectangle is contained within another rectangle
// rect1.contains_rectangle(rect2);
bool Rectangle::contains_rectangle(const Rectangle &rect) const {
    vector <int> v = {};
    Rectangle outer(p1,p2, false, v);
    Vec2D tl2 = rect.get_tl();
    Vec2D br2 = rect.get_br();
    return ((outer.contains_point(rect.p1)
            and outer.contains_point(rect.p2)
            and outer.contains_point(tl2)
            and outer.contains_point(br2)));
}
// checks if two rectangles overlap
// rect1.overlap(rect2);
bool Rectangle::overlap(const Rectangle &rect) const {
    return ((((p1.x <= rect.p2.x and p1.x >= rect.p1.x) or (p2.x <= rect.p2.x and p2.x >= rect.p1.x)) and ((rect.p1.y <= p2.y and rect.p1.y >= p1.y) or (rect.p2.y <= p2.y and rect.p2.y >= p1.y)))
            or (((rect.p1.x <= p2.x and rect.p1.x >= p1.x) or (rect.p2.x <= p2.x and rect.p2.x >= p1.x)) and ((p2.y <= rect.p2.y and p2.y >= rect.p1.y) or (p2.y <= rect.p2.y and p2.y >= rect.p1.y))));
}
