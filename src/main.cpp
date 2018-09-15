#include <iostream>
#include "node.h"
#include "tree.h"
#include "obstacle.h"

using namespace std;

int main() {
    cout << "hello world!" << endl;
    CubeObstacle o = CubeObstacle(1, 1, 2, 2);
    Node node1 = Node(1, 3, 0);
    Node node2 =  Node(1, 1, 0);
    cout << "is valid?" << o.isValidMove(&node1, &node2);
    return 0;
}
