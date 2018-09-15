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


Node* Tree::findClosestNode(Node *node) {
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

    return closest;
}
