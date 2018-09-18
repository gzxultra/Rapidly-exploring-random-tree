#include "tree.h"
#include "node.h"

#include <iostream>
#include <cmath>

using namespace std;


Tree::Tree(Node *root) {
    this->root = root;
}

void Tree::addChild(Node *node, Node *newNode) {
    node->children.push_back(newNode);
    newNode->parent = node;
}

double Tree::calcDistance(Node *node1, Node *node2) {
    return sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
}

Node* Tree::findClosestNode(Node *node, double &distance) {
    // conduct a DFS search
    if (root == NULL) {
        cout << "ehh, no closest!" << endl;
        return NULL;
    }

    Node *closest, *p;
    vector<Node *> stack;
    double minDistance = -1;
    double myDistance = -1.0;

    stack.push_back(root);

    while (!stack.empty()) {
        p = stack.back();
        stack.pop_back();

        myDistance = calcDistance(node, p);
        if (-1.0 == minDistance || myDistance < minDistance) {
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

Node* Tree::extendNewNode(Node *node, Node* closest) {
    const float epsilon = 0.1;  // the very short distance we're gonna move
    double minDistance = 0.0;
    closest = findClosestNode(node, minDistance);
    if (closest == NULL)
        return NULL;

    float deltaX = node->x - closest->x;
    float deltaY = node->y - closest->y;
    float theta = atan2(deltaY, deltaX);
    float xOfNewNode = closest->x + epsilon * cos(theta);
    float yOfNewNode = closest->y + epsilon * sin(theta);

    Node* newNode = new Node(xOfNewNode, yOfNewNode, 0);
    return newNode;
}


int Tree::countTotalNodes() {
    vector<Node*> stack;
    stack.push_back(root);
    int nNodes = 0;
    Node* p;

    while (!stack.empty()) {
        p = stack.back();
        stack.pop_back();
        if (p == NULL) continue;
        else nNodes ++;

        for (auto child: p->children) {
            stack.push_back(child);
        }
    }
    return nNodes;
}