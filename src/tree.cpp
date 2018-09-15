#include "tree.h"
#include "node.h"

#include <iostream>
#include <cmath>

using namespace std;


void Tree::addChild(Node *node, Node *newNode) {
    node->children.push_back(newNode);
    newNode->parent = node;
}


double Tree::calcDistance(Node *node1, Node *node2) {
    return sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
}


Node* Tree::findClosestNode(Node *node, double &distance) {
    // conduct a DFS search

    Node *closest, *p;
    vector<Node *> stack;
    double minDistance, myDistance = -1.0;

    stack.push_back(node);

    while (!stack.empty()) {
        p = stack.back();
        myDistance = calcDistance(node, p);
        if (-1 == minDistance || myDistance < minDistance) {
            minDistance = myDistance;
            closest = p;
        }
        for (auto child : p->children) {
            stack.push_back(child);
        }
    }
    distance = minDistance;
    return closest;
}

bool Tree::extendNewNode(Node *node) {
    const float epsilon = 0.1;  // the very short distance we're gonna move
    double minDistance = 0.0;
    Node *closest = findClosestNode(node, minDistance);
    if (closest == NULL)
        return false;

    float deltaX = node->x - closest->x;
    float deltaY = node->y - closest->y;
    float theta = atan2(deltaY, deltaX);
    float xNewX = closest->x + epsilon * cos(theta);
    float xNewY = closest->y + epsilon * sin(theta);

    Node XNew = Node(xNewX, xNewY, 0);
    addChild(closest, &XNew);
    return true;
}
