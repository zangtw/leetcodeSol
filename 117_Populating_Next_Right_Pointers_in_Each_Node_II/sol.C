#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef struct TreeLinkNode {
  int val;
  TreeLinkNode *left, *right, *next;
  TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
}TreeLinkNode;

class Solution {
public:
  void connect(TreeLinkNode *root) {
    if (!root) return;
    
    queue<pair<TreeLinkNode*, int>> bfsQueue;
    
    bfsQueue.push(make_pair(root, 0));
    
    while (!bfsQueue.empty())
    {
      auto info = bfsQueue.front();
      int depth = info.second;
      bfsQueue.pop();
      
      if (info.first->left)
        bfsQueue.push(make_pair(info.first->left, depth + 1));
      if (info.first->right)
        bfsQueue.push(make_pair(info.first->right, depth + 1));
      
      if (!bfsQueue.empty())
      {
        if (bfsQueue.front().second != depth)
        info.first->next = NULL;
        else info.first->next = bfsQueue.front().first;
      }
      else
        info.first->next = NULL;
    }
  }
};

int main()
{
  Solution sol;

  // need test cases

  return 0;
}
