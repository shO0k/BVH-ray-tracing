#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include "ray.h"
#include "rectangle.h"
using namespace std;
// refactor collision function for correct front-end output (see hit function: line 50): DONE
// impliment special case for vertical slope (see hit function: line 50): DONE
Ray::Ray() {}
// constructor for ray, includes anchor point, slope, and direction
Ray::Ray(const Vec2D &new_ap, const double &new_slope, const int &new_direction) {
    ap = new_ap;
    slope = new_slope;
    direction = new_direction;
}
// getter for anchor point
Vec2D Ray::get_ap() const {
    return ap;
}
// getter for slope
double Ray::get_slope() const {
    return slope;
}
// getter for is_vertical
bool Ray::get_vertical() const {
    return isnan(slope);
}
// getter for direction
int Ray::get_direction() const {
    return direction;
}
// setter for anchor point
void Ray::set_ap(const Vec2D &new_ap) {
    ap = new_ap;
}
// setter for slope
void Ray::set_slope(const double &new_slope) {
    slope = new_slope;
}
// setter for direction
void Ray::set_direction(const int &new_direction) {
    direction = new_direction;
}
// allows user to output a ray
ostream& operator<< (ostream &outs, const Ray &ray) {
    if (ray.get_vertical()) {
        if (ray.direction == 0) outs << ray.ap << " Slope: Vertical " << "Backwards";
        else outs << ray.ap << " Slope: Vertical " << "Forwards";
    }
    else {
        if (ray.direction == 0) outs << fixed << setprecision(2) << ray.ap << " Slope: " << setprecision(2) << ray.slope << " Backwards";
        else outs << fixed << setprecision(2) << ray.ap << " Slope: " << ray.slope << " Forwards";
    }
    return outs;
}
// alllows user to input a ray
istream& operator>> (istream &ins, Ray &ray) {
    string slope_temp;
    ins >> ray.ap >> slope_temp >> ray.direction;
    try {
        ray.slope = stod(slope_temp);
    } catch(...) { ray.slope = NAN; }
    return ins;
}
// ray-rectangle collision dectection
bool Ray::hit(const Rectangle &rect, const bool &output) const {
    Vec2D hit_location, hit_special, bottom, top, left, right;
    bool result = false;
    if (rect.contains_point(ap)) {
        hit_location.x = ap.x;
        hit_location.y = ap.y;
        if (output) cout << "HIT! Location: " << hit_location << endl;
        return true;
    }
    //cout << "slope: " << slope << endl;
    bool m_alpha = true;
    Rectangle rect_new;
    double m = 0.0;
    Vec2D bl = rect.get_p1(), tr = rect.get_p2();
    // assign slope, horizontal and vertical shift (make anchor point (0,0))
    double hs = ap.x, vs = ap.y;
    if (!(slope == NAN)) {
        m = slope;
        m_alpha = false;
    }
   else to_string(m) = slope;
    // rectangle extrema for special cases slope = 0 and vertical slope
    double x_smin = bl.x, x_smax = tr.x, y_smin = bl.y, y_smax = tr.y;
    if (!m_alpha) {
        if (m != 0) {
            bl.x -= hs;
            tr.x -= hs;
            bl.y -= vs;
            tr.y -= vs;
            rect_new.set_p1(bl);
            rect_new.set_p2(tr);
            double x_min = bl.x, x_max = tr.x, y_min = bl.y, y_max = tr.y;
            right.x = x_max, right.y = m*x_max;
            left.x = x_min, left.y = m*x_min;
            top.x = y_max/m, top.y = y_max;
            bottom.x = y_min/m, bottom.y = y_min;
        }
    }
    if (slope == NAN) {
        if (direction == 1 and ap.x >= bl.x and ap.x <= tr.x and y_smin >= ap.y ) {
            hit_special.x = ap.x;
            hit_special.y = y_smin;
            result = true;
        }
        else if (direction == 0 and ap.x >= bl.x and ap.x <= tr.x and y_smax <= ap.y) {
            hit_special.x = ap.x;
            hit_special.y = y_smax;
            result = true;
        }
    }
    else {
        if (direction == 1) {
            if (m > 0) {
                if (rect_new.contains_point(left) and left.x >= ap.x and left.y >= ap.y) {
                    hit_location = left;
                    result = true;
                }
                else if (rect_new.contains_point(bottom) and bottom.x >= ap.x and bottom.y >= ap.y) {
                    hit_location = bottom;
                    result = true;
                }
            }
            // special case for slope = 0
            else if (m == 0) {
                if (ap.y >= bl.y and ap.y <= tr.y and ap.x <= x_smin) {
                    hit_special.x = x_smin;
                    hit_special.y = ap.y;
                    result = true;
                }
            }
           // if m < 0
            else {
                if (rect_new.contains_point(left) and ap.x <= left.x and ap.y >= left.y) {
                    hit_location = left;
                    cout << "left: " << left << endl;
                    result = true;
                }
                else if (rect_new.contains_point(top) and ap.x <= top.x and ap.y >= top.y) {
                    hit_location = top;
                    cout << "top: " << top << endl;
                    result = true;
                }
            }
        }
        else if (direction == 0) {
            if (m > 0) {
                if (rect_new.contains_point(right) and ap.x >= right.x and ap.y >= right.y) {
                    hit_location = right;
                    result = true;
                }
                else if (rect_new.contains_point(top) and ap.x >= top.x and ap.y >= top.y) {
                    hit_location = top;
                    result = true;
                }
            }
            // special case for slope = 0
            else if (m == 0) {
                if (ap.y >= bl.y and ap.y <= tr.y and ap.x >= x_smax) {
                    hit_special.x = x_smax;
                    hit_special.y = ap.y;
                    result = true;
                }
            }
            // if m < 0
            else {
                if (rect_new.contains_point(bottom) and ap.x >= bottom.x and ap.y <= bottom.y) {
                    hit_location = bottom;
                    result = true;
                }
                else if (rect_new.contains_point(right) and ap.x >= right.x and ap.y <= right.y) {
                    hit_location = right;
                    result = true;
                }
            }
        }
    }
    if (m != 0) {
        hit_location.x += hs;
        hit_location.y += vs;
    }
    if (output) {
        if (result)  {
            if (m != 0 and !(slope == NAN)) cout<< "HIT! Location: " << hit_location << endl;
            else cout  << "HIT! Loction: " << hit_special << endl;
            result = false;
        }
        else cout << "MISS!" << endl;
    }
    return result;
}
