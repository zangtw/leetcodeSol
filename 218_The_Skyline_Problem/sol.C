#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

class Solution {
public:
  vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
    int n = buildings.size();
    vector<pair<int, int>> res;
    
    map<int, unordered_set<int>> edge2Height;
    
    for (auto& building : buildings)
    {
      int leftEdge = building[0], rightEdge = building[1];
      int height = building[2];

      edge2Height[leftEdge].insert(height);
      edge2Height[rightEdge].insert(-height);
    }
  
    map<int, int> heightCount;
    int maxHeightOld = INT_MIN;

    for (auto& iter : edge2Height)
    {
      int edge = iter.first;

      for (auto height : iter.second)
      {
        if (height > 0)
          heightCount[height]++;
        else
        {
          height = -height;
          heightCount[height]--;
          if (heightCount[height] == 0)
            heightCount.erase(height);
        }
      }

      int maxHeight = 0;
      if (!heightCount.empty())
        maxHeight = (*(heightCount.rbegin())).first;

      if (maxHeight != maxHeightOld)
        res.push_back(make_pair(edge, maxHeight));
    
      maxHeightOld = maxHeight;
    }
  
    return res;
  }
};

int main()
{
  Solution sol;
  int n;

  cout << "n:";
  cin >> n;

  vector<vector<int>> buildings(n, vector<int>(3, 0));

  for (int i = 0; i < n; i++)
    for (int j = 0; j < 3; j++)
      cin >> buildings[i][j];
  
  auto res = sol.getSkyline(buildings);
  for (auto& building : res)
  {
    cout << building.first << '\t';
    cout << building.second << endl;
  }

  return 0;
}
