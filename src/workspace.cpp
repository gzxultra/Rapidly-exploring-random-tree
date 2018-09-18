#include "workspace.h"
#include "node.h"
#include "tree.h"
#include <random>
#include <iostream>

using namespace std;


WorkSpace::WorkSpace(float x1, float y1, float x2, float y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}


bool WorkSpace::addObstacle(CubeObstacle* o) {
    // TODO, test if the obstacle is valid;
    obstacles.push_back(o);
    return true;
}

Node* WorkSpace::generateRandomValidNode(Tree* tree) {
    random_device r;
    seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
    mt19937 eng{seed};

    // a distribution that takes randomness and produces values in specified range
    uniform_real_distribution<> distX(x1, x2);
    uniform_real_distribution<> distY(y1, y2);

    Node* randomNode = NULL;
    Node* closest = NULL;
    bool isObstructed = false;
    bool isValid = false;

    while (true) {
        randomNode = new Node(distX(eng), distY(eng), 0);

        // test if node already on the tree
        double distance = 0;
        closest = tree->findClosestNode(randomNode, distance);
        if (closest == NULL or distance != 0) {
            isValid = true;
        } else {
            continue;
        }

        // test if node been obstructed
        isObstructed = false;
        for (CubeObstacle* co : obstacles) {
            if (!co->isValidNode(randomNode)) {
                isObstructed = true;
                break;
            }
        }
        if (isObstructed == false && isValid == true) break;
    }

    return randomNode;
}

bool WorkSpace::isValidMoveOnWorkSpace(Node* fromNode, Node* toNode) {
    bool isValidMove = true;
    for (CubeObstacle* co : obstacles) {
        if (co->isValidMove(fromNode, toNode)) {
            cout << "Obstructed!" << co->center_x << co->center_y << '(' << fromNode->x << ", " << fromNode->y << ')' << '(' << toNode->x << ", " << toNode->y << ')' <<  endl;
            isValidMove = false;
            break;
        }
    }
    return isValidMove;
}

bool WorkSpace::isCloseToTheGoal(Node* node) {
    const double fitDistance = 1.0;
    double distance = sqrt(pow(goal->x - node->x, 2) + pow(goal->y - node->y, 2));
    if (distance <= fitDistance && isValidMoveOnWorkSpace(goal, node)) {
        return true;
    } else {
        return false;
    }
}

vector<Node*> WorkSpace::getRRTPath(Tree* tree) {
    vector<Node*> path;
    Node* p = goal;
    while (p != NULL and p != src) {
        path.push_back(p);
        p = p->getParentNode();
    }
    return path;
}
