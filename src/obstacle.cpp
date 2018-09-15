#include "obstacle.h"
#include "node.h"
#include "../lib/gjk.c"
#include <iostream>


using namespace std;


BaseObstacle::BaseObstacle(float center_x, float center_y) {
    this->center_x = center_x;
    this->center_y = center_y;
}


bool CubeObstacle::isValidNode(Node *node) {
    if (center_x - width / 2 <= node->x && node->x  < center_x + width / 2 && center_y - height / 2 <= node->y && node->y < height / 2) {
        return true;
    } else {
        return false;
    }
}

bool CubeObstacle::isValidMove(Node *fromNode, Node *toNode) {

    vec2 vertices1[] = {
        { fromNode->x, fromNode->y },
        { toNode->x, toNode->y },
    };

    vec2 vertices2[] = {
        { center_x - width / 2, center_y - height / 2 },
        { center_x - width / 2, center_y + height / 2 },
        { center_x + width / 2, center_y + height / 2 },
        { center_x + width / 2, center_y - height / 2 },
    };
    size_t count1 = sizeof (vertices1) / sizeof (vec2); // == 2
    size_t count2 = sizeof (vertices2) / sizeof (vec2); // == 4
    int collisionDetected = gjk (vertices1, count1, vertices2, count2);

    return collisionDetected;
}

CubeObstacle::CubeObstacle(float center_x, float center_y, float width, float height)
    : BaseObstacle(center_x, center_y) {
    this->width = width;
    this->height = height;
}
