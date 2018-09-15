#ifndef OBSTACLE_H
#define OBSTACLE_H


#include <vector>
#include "node.h"


class BaseObstacle {
    public:
        BaseObstacle(float center_x, float center_y);
        virtual bool isValidMove(Node *fromNode, Node *toNode) {return true;}
        virtual bool isValidNode(Node *node) {return true;}
        float center_x, center_y;

};

class CubeObstacle: public BaseObstacle {
    float width, height;
    public:
      CubeObstacle(float center_x, float center_y, float width, float height);
      bool isValidMove(Node *fromNode, Node *toNode);
      bool isValidNode(Node *node);
};

#endif
