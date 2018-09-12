#ifndef TREE_H
#define TREE_H


#include <vector>

using namespace std;



class TreeNode {
  public:
    float x, y, theta;

    TreeNode(float x, float y, float theta);
    TreeNode *parent;
    vector <TreeNode*> children;
};


class Tree {
  public:
    Tree();

    TreeNode getParent();
    vector<TreeNode> getChildren();
    void addChild(TreeNode *node, TreeNode *newNode);
    double calcDistance(TreeNode *node1, TreeNode *new2);
    TreeNode* findClosestNode(TreeNode *node);

  private:
    TreeNode *root;
};

#endif
