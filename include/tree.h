#ifndef TREE_H
#define TREE_H

#include <vector>
#include "node.h"


using namespace std;


class Tree {
  public:
    Node getParent();
    vector<Node> getChildren();
    void addChild(Node *node, Node *newNode);
    double calcDistance(Node *node1, Node *new2);
    Node* findClosestNode(Node *node, double &distance);
    Node* extendNewNode(Node *node, Node* closest);

  private:
    Node *root;
};

#endif
