#include "tree.h"
#include <iostream>
#include <cmath>


using namespace std;


TreeNode::TreeNode(float x, float y, float theta) {
    this->x = x;
    this->y = y;
    this->theta = theta;
    this->parent = NULL;
}

void Tree::addChild(TreeNode *node, TreeNode *newNode) {
    node->children.push_back(newNode);
    newNode->parent = node;
}


double Tree::calcDistance(TreeNode *node1, TreeNode *node2) {
    return sqrt(pow(node1->x - node2->x, 2) + pow(node1->y - node2->y, 2));
}


TreeNode* Tree::findClosestNode(TreeNode *node) {
    // conduct a DFS search

    TreeNode *closest, *p;
    vector<TreeNode *> stack;
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
