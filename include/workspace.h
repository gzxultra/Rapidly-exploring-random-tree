#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <vector>
#include "tree.h"
#include "node.h"
#include "obstacle.h"


using namespace std;


class WorkSpace {
  public:
    WorkSpace(float x1, float y1, float x2, float y2);
    Node* generateRandomValidNode(Tree* tree);
    bool addObstacle(CubeObstacle* o);
    bool isValidMoveOnWorkSpace(Node* fromNode, Node* toNode);
    bool isCloseToTheGoal(Node* node);
    bool setSrc(Node* src) {this->src = src; return true;}
    bool setGoal(Node* goal) {this->goal = goal; return true;}
    vector<Node*> getRRTPath(Tree* tree);
    vector<Node*> getSmoothPath(vector<Node*> preliminaryPath);
  private:
    float x1, y1, x2, y2;
    Node* src;
    Node* goal;
    vector<CubeObstacle*> obstacles;
};

#endif
