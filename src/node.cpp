#include "tree.h"
#include "node.h"
#include <sstream>
#include <iostream>
#include <cmath>
#include <string>


Node::Node(float x, float y, float theta) {
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->parent = NULL;
}

std::string Node::serialize() {
    // inspired by the method from stackoverflow
    // https://stackoverflow.com/a/332132/5159179
    std::ostringstream strs;
    strs << "(" << x << ", " << y << ")";
    std::string str = strs.str();
    return str;
}
