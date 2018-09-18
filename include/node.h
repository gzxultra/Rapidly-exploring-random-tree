#ifndef NODE_H
#define NODE_H


#include <vector>
#include <string>


class Node {
  private:
    Node *parent;

  public:
    Node(float x, float y, float theta);
    std::vector <Node*> children;
    bool setParentNode(Node* parent) { this->parent = parent; return true;}
    Node* getParentNode() { return parent;}
    std::string serialize();

    // sorry, don't have enough time to put it fully OOPmakm
    float x;
    float y;
    float theta;
};

#endif
