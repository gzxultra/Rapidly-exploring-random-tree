#include "workspace.h"
#include "node.h"
#include "tree.h"
#include <random>

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
    uniform_int_distribution<> distX(x1, x2);
    uniform_int_distribution<> distY(y1, y2);
    while (true) {
        Node randomNode = Node(distX(eng), distY(eng), 0);

        // test if node already on the tree
        double distance = 0;
        Node* closet = tree->findClosestNode(&randomNode, distance);
        if (distance == 0) {
            continue;
        }

        // test if node been obstructed
    }
}


