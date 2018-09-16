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

    while (true) {
        randomNode = new Node(distX(eng), distY(eng), 0);
        cout << randomNode->x << ' ' << randomNode->y << endl;

        // test if node already on the tree
        double distance = 0;
        closest = tree->findClosestNode(randomNode, distance);
        if (closest != NULL and distance == 0) {
            cout << "distance == 0" << closest << endl;
            break;
            continue;
        }

        // test if node been obstructed
        for (CubeObstacle* co : obstacles) {
            if (!co->isValidNode(randomNode)) {
                cout << randomNode->x << ' ' << randomNode->y << "obstructed" << endl;
                continue;
            }
        }
    }

    return randomNode;
}


