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

  private:
    float x1, y1, x2, y2;
    vector<CubeObstacle*> obstacles;
};

#endif
