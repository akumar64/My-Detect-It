//
//  main.cpp
//  TreePathSum
//
//  Created by ARJUN KUMAR on 8/31/17.
//  Copyright © 2017 ARJUN KUMAR. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode
{
    int x;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
    
    TreeNode(int inX)
    {
        x = inX;
    }
};

int findIndex(vector<int>& vector, int searchX)
{
    int foundInd = -1;
    for (int ind = 0; ind < vector.size(); ind++)
    {
        if (vector.at(ind) == searchX)
        {
            foundInd = ind;
            break;
        }
    }
    return foundInd;
}

shared_ptr<TreeNode> buildTree(vector<int>& preOrder, vector<int>& inOrder)
{
    // no duplicates allowed
    if (preOrder.size() == 0)
    {
        return nullptr;
    }
    else
    {
        int rootNum = preOrder[0];
        shared_ptr<TreeNode> rootNode(new TreeNode(rootNum));
        if (preOrder.size() > 1)
        {
            int foundInd = findIndex(inOrder, rootNum);
            
            vector<int> leftTreeInVec(inOrder.begin(), inOrder.begin()+foundInd);
            vector<int> rightTreeInVec(inOrder.begin()+foundInd+1, inOrder.end());
            
            vector<int> leftTreePreVec(preOrder.begin()+1, preOrder.begin()+1+leftTreeInVec.size());
            vector<int> rightTreePreVec(preOrder.begin()+1+leftTreeInVec.size(), preOrder.end());
            
            rootNode->left = buildTree(leftTreePreVec, leftTreeInVec);
            rootNode->right = buildTree(rightTreePreVec, rightTreeInVec);
        }
        return rootNode;
    }
}

vector<vector<int> > pathSum(shared_ptr<TreeNode> rootNode, int sum)
{
    stack<shared_ptr<TreeNode> > nodeStack;
    stack<int> levelStack;
    stack<int> sumStack;
    
    vector<int> currentPath;
    vector<vector<int> > allPaths;
    
    nodeStack.push(rootNode);
    levelStack.push(0);
    sumStack.push(rootNode->x);

    while (!nodeStack.empty())
    {
        shared_ptr<TreeNode> topNode = nodeStack.top();
        
        int levelPathInd = levelStack.top();
        int topNodeSum = sumStack.top();
        if (levelPathInd == currentPath.size())
        {
            currentPath.push_back(topNode->x);
        }
        else
        {
            currentPath.at(levelPathInd) = topNode->x;
        }
        nodeStack.pop();
        levelStack.pop();
        sumStack.pop();
        if (topNode->left == nullptr && topNode->right == nullptr)
        {
            if (topNodeSum == sum)
            {
                vector<int> addPath(currentPath.begin(), currentPath.begin()+levelPathInd+1);
                allPaths.push_back(addPath);
            }
        }
        else
        {
            if (topNode->left != nullptr)
            {
                nodeStack.push(topNode->left);
                levelStack.push(levelPathInd+1);
                sumStack.push(topNode->left->x + topNodeSum);
            }
            if (topNode->right != nullptr)
            {
                nodeStack.push(topNode->right);
                levelStack.push(levelPathInd+1);
                sumStack.push(topNode->right->x + topNodeSum);
            }
        }

    }
    return allPaths;
    //return {{}};
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    vector<int> preOrder = {5, 4, 11, 7, 2, 8, 9, 3, 6, 1};
    vector<int> inOrder = {7, 11, 2, 4, 5, 9, 8, 6, 3, 1};
    /*              5
                4       8
            11        9     3
          7    2          6   1
    */
    cout << buildTree(preOrder, inOrder)->x << endl;
    
    shared_ptr<TreeNode> rootNode = buildTree(preOrder, inOrder);
    
    vector<vector<int> > allPaths = pathSum(buildTree(preOrder, inOrder), 22);
        
    return 0;
}
