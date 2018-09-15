#include "tree.h"
#include "node.h"

#include <iostream>
#include <cmath>

using namespace std;


Node::Node(float x, float y, float theta) {
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->parent = NULL;
}
