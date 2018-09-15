#ifndef NODE_H
#define NODE_H


#include <vector>

using namespace std;



class Node {
  public:
    float x, y, theta;

    Node(float x, float y, float theta);
    Node *parent;
    vector <Node*> children;
};

#endif
