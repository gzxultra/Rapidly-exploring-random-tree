#include <iostream>
#include "node.h"
#include "tree.h"
#include "obstacle.h"
#include "workspace.h"

using namespace std;


int main() {
    cout << "hello world!" << endl;
    WorkSpace w = WorkSpace(0, 0, 20, 20);
    CubeObstacle* o1 = new CubeObstacle(2, 2, 2, 2);
    CubeObstacle* o2 = new CubeObstacle(15, 12, 6, 4);
    CubeObstacle* o3 = new CubeObstacle(16, 16, 2, 2);
    w.addObstacle(o1);
    w.addObstacle(o2);
    w.addObstacle(o3);

    Node* root = new Node(0, 0, 0);
    Tree* t = new Tree(root);

    Node* node = NULL;
    double distance = 0;
    Node* nearestNodeOnTree = NULL;
    Node* newNode = NULL;

    const int K = 10000;
    for (int k = 1; k < K; k++) {
        node = w.generateRandomValidNode(t);
        nearestNodeOnTree = t->findClosestNode(node, distance);
        newNode = t->extendNewNode(node, nearestNodeOnTree);
        if (w.isValidMoveOnWorkSpace(nearestNodeOnTree, newNode)) {
            t->addChild(nearestNodeOnTree, newNode);
            cout << "newChild Added " << distance << endl;
        } else {
            cout << "Not Valid!" << endl;
        }
    }
    cout << "yes!" << endl;
    return 0;
}
