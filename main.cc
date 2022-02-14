#include <iostream>
#include <iomanip>
#include "rectangle.h"
#include "ray.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// die function
void die(string error_message) {
    cout << error_message << endl;
    exit(EXIT_FAILURE);
}
// outputs mode of a vector
int winner(vector<int> v) {
    int winner = 0;
    int highest = 0;
    for (size_t i = 0; i < v.size(); i++) {
        if (v.at(i) > highest) {
            winner = i;
            highest = v.at(i);
        }
    }
    return winner;
}
// allows output of vectors using <<
template <class T>
ostream& operator<<(ostream &outs, const vector<T> &vec) {
    for (const auto &a : vec) outs << a << " ";
    return outs;
}
// rectangle collision function
void collisions(vector<Rectangle> v) {
    bool overlap = false;
    for (size_t i = 0; i < v.size() - 1; i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[i].get_isSolid() == 1 and v[j].get_isSolid() == 1 and (v[i].overlap(v[j]) or v[i].contains_rectangle(v[j]) or v[j].contains_rectangle(v[i]))) {
                cout << "Box " << i << " and " << "Box " << j << " intersect." << endl;
                overlap = true;
            }
        }
    }
    if (!overlap) cout << "No boxes overlapped!" << endl;
}
// parses map data and prints it;
void print_map(string filename) {
    vector<Rectangle> vectangle;
    ifstream ins(filename);
    string s;
    int child = 0;
    while (ins) {
        if (!ins) break;
        getline(ins, s);
        istringstream iss(s);
        while (iss) {
            vector<int> children = {};
            for (int x : children) children.pop_back();
            Rectangle temp;
            iss >> temp;
            if (!iss) break;
            while (iss) {
                iss >> child;
                if (!iss) break;
                children.push_back(child);
            }
            if (temp.get_isSolid() == 0) temp.set_children(children);
            vectangle.push_back(temp);
        }
    }
    for (auto x : vectangle) {
        cout << x << endl;
    }
}

// parses map data and returns vector of rectangles
vector<Rectangle> load_map(string filename) {
    vector<Rectangle> vectangle;
    ifstream ins(filename);
    string s;
    int child = 0;
    while (ins) {
        if (!ins) break;
        getline(ins, s);
        istringstream iss(s);
        while (iss) {
            vector<int> children = {};
            for (int x : children) children.pop_back();
            Rectangle temp;
            iss >> temp;
            if (!iss) break;
            while (iss) {
                iss >> child;
                if (!iss) break;
                children.push_back(child);
            }
            if (!temp.get_isSolid()) temp.set_children(children);
            vectangle.push_back(temp);
        }
    }
    return vectangle;
}

// parses shots data and prints it
void print_shots(string filename) {
    ifstream ins(filename);
    vector<Ray> vray = {};
    while (ins) {
        if (!ins) break;
        string s = "";
        getline(ins,s);
        istringstream iss(s);
        while (iss) {
            Ray temp;
            iss >> temp;
            if (!iss) break;
            vray.push_back(temp);
        }
    }
    for (auto x : vray) cout << x << endl;
}
// parses shots data and returns vector of rays
vector<Ray> load_shots(string filename) {
    ifstream ins(filename);
    vector<Ray> vray = {};
    while (ins) {
        if (!ins) break;
        string s = "";
        getline(ins,s);
        istringstream iss(s);
        while (iss) {
            Ray temp;
            iss >> temp;
            if (!iss) break;
            vray.push_back(temp);
        }
    }
    return vray;
}
// checks map for correctness
void map_vet(string filename) {
    bool map_correct = true;
    int child = 0;
    string s;
    vector<Rectangle> map = load_map(filename);
    for (size_t i = 0; i < map.size();i++) {
        if(!map.at(i).get_isSolid()) {
            for(size_t j = 0; j < map.at(i).get_children().size();j++) {
                 if (!map.at(i).contains_rectangle(map.at(i+j+1))) {
                     map_correct = false;
                     cout << "Map Error: Box " << i+j+1 << endl;
                     break;
                 }
                 if (!map_correct) break;
            }
        }
    }
    if(map_correct) cout << "Map Correct" << endl;
}
// function that vets the min/max point pair for each rectangle in a map
bool min_max_vet(const vector<Rectangle> &v) {
    bool result = true;
    for (auto rect : v) {
        //cout << v << endl;
        if ((rect.get_p1().x >= rect.get_p2().x) or (rect.get_p1().y >= rect.get_p2().y)) {
            result = false;
            break;
        }
    }
    return result;
}
// map-wide rectangle-ray collision function
void map_collision(const vector<Rectangle> &vectangle, const vector<Ray> &vray) {
    Rectangle r_temp = {};
    Ray s_temp = {};
    vector<Rectangle> parents = {};
    for (Rectangle r : vectangle) {
        if (!r.get_isSolid()) parents.push_back(r);
        //cout << r << endl;
    }
    size_t map_size = vectangle.size();
    size_t num_shots = vray.size();
    size_t num_parents = parents.size();
    vector<int> score(map_size);
    for (size_t x = 0; x < map_size; x++) score.at(x) = 0;
    for (size_t i = 0; i < num_shots; i++) {
        s_temp = vray.at(i);
        for (size_t j = 0; j < num_parents; j++) {
            r_temp = parents.at(j);
            if (s_temp.hit(r_temp,false)) {
                for (size_t k = 0; k < r_temp.get_children().size(); k++) {
                    if (s_temp.hit(vectangle.at(r_temp.get_children().at(k)),false)) {
                        score.at(r_temp.get_children().at(k))++;
                        break;
                    }
                }
            }
        }
    }
    cout << "Box " << winner(score)  << " was hit " << score.at(winner(score)) << " times" << endl;
}

int main() {
    string user_choice = "";
    string user_input1 = "";
    string user_input2 = "";
    string filename1 = "";
    string filename2 = "";
    // load map data here:
    (void)!system("/usr/bin/figlet RTX ON");
    cout << "Please enter the map filename:\n";
    getline(cin, filename1);
    vector<Rectangle> boxes = load_map(filename1);
    if (!boxes.size()) die("Could not open file");
    if (!min_max_vet(boxes)) die("Min must always be < max");
    cout << "Please enter filename with the shots:\n";
    getline(cin, filename2);
    vector<Ray> shots = load_shots(filename2);
    if (!shots.size()) die("Could not open file");
    cout << "Menu:\n" <<
        "1) Print the world of boxes\n" <<
        "2) Print the list of shots\n" <<
        "3) Check the boxes for correctness\n" <<
        "4) See if two rectangles overlap\n" <<
        "5) See if a ray hits a rectangle\n" <<
        "6) Output a list of all solid boxes colliding\n" <<
        "7) Fire all shots and see which box is getting hit the most\n" <<
        "Please enter choice:\n";
    getline(cin,user_choice);
    if (user_choice == "1") { // TO-DO
        //print world of boxes here
        print_map(filename1);
    }
    else if (user_choice == "2") { // TO DO
        //print list of shots
        print_shots(filename2);
    }
    else if (user_choice == "3") { // TO DO
        //map check here
        map_vet(filename1);
    }
    else if (user_choice == "4") { // DONE
        // rectangle-rectangle intersection here
        Rectangle rect1, rect2;
        Vec2D p1, p2, p3, p4;
        cout << "Please enter the min and max points for a Rectangle (example: 0 0 10 20 to make a box from (0,0) to (10,20)):" << endl;
        getline(cin, user_input1);
        stringstream iss1(user_input1);
        iss1 >> p1.x >> p1.y >> p2.x >> p2.y;
        rect1.set_p1(p1);
        rect2.set_p2(p2);
        cout << "And then again for a second Rectangle:" << endl;
        getline(cin, user_input2);
        stringstream iss2(user_input2);
        iss2 >> p3.x >> p3.y >> p4.x >> p4.y;
        rect2.set_p1(p3);
        rect2.set_p2(p4);
        if (rect1.overlap(rect2) or rect1.contains_rectangle(rect2) or rect2.contains_rectangle(rect1)) cout << "They intersect!" << endl;
        else cout << "They don't intersect" << endl;
    }
    else if (user_choice == "5") { // DONE
        // rectangle-ray intersection here
        Rectangle rect;
        Ray ray;
        Vec2D p1, p2;
        cout << "Please enter the min and max points for a Rectangle (example: 0 0 10 20 to make a box from (0,0) to (10,20)):" << endl;
        getline(cin, user_input1);
        stringstream iss1(user_input1);
        iss1 >> p1.x >> p1.y >> p2.x >> p2.y;
        rect.set_p1(p1);
        rect.set_p2(p2);
        cout << "Please enter a shot (for example: 0 5 1.1 1 means it comes from (0 5) heading up at a slope of 1.1 in the forwards direction):" << endl;
        getline(cin, user_input2);
        stringstream iss2(user_input2);
        iss2 >> ray;
        //cout << ray << endl;
        ray.hit(rect,true);
    }
    else if (user_choice == "6") { // TO-DO
        // map-wide collision detection using overlap function here 
        vector<Rectangle> in = load_map(filename1);
        collisions(in);
    }
    else if (user_choice == "7") { // TO-DO
        // map-wide shot detection using ray-rectangle intersection function here
        map_collision(boxes,shots);
    }
    return 0;
}

