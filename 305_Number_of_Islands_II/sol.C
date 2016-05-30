#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

typedef struct subset{
  int parent;
  int rank;
}subset;

class Solution {
public:
  vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) 
  {
    int s = positions.size();
    vector<int> res;
    unordered_map<int, subset> subsets; 
    
    for (int i = 0; i < s; i++)
    {
      int x = positions[i].first, y = positions[i].second;
      int key = x * n + y;
      int islandNum = (i == 0) ? 0 : res.back();
    
      subsets[key] = subset{key, 0};
      islandNum++;
    
      // up
      if (x - 1 >= 0 && subsets.find(key - n) != subsets.end()) 
        mergeIslands(subsets, key, key - n, islandNum);
     
      // down
      if (x + 1 < m && subsets.find(key + n) != subsets.end())
        mergeIslands(subsets, key, key + n, islandNum);
     
      // left
      if (y - 1 >= 0 && subsets.find(key - 1) != subsets.end()) 
        mergeIslands(subsets, key, key - 1, islandNum);
     
      // right
      if (y + 1 < n && subsets.find(key + 1) != subsets.end())
        mergeIslands(subsets, key, key + 1, islandNum);
     
      res.push_back(islandNum);
    }
     
    return res;
  }
   
  void mergeIslands(unordered_map<int, subset>& subsets, int island1, 
      int island2, int& islandNum)
  {
    int parent1 = find(subsets, island1);
    int parent2 = find(subsets, island2);
    if (parent1 == parent2) return;
  
    int rank1 = subsets[parent1].rank, rank2 = subsets[parent2].rank;
    if (rank1 > rank2)
      subsets[parent2].parent = parent1;
    else if (rank2 > rank1)
      subsets[parent1].parent = parent2;
    else
    {
      subsets[parent2].parent = parent1;
      subsets[parent1].rank++;
    }
  
    islandNum--;
  }
  
  int find(unordered_map<int, subset>& subsets, int island)
  {
    if (subsets[island].parent != island)
    subsets[island].parent = find(subsets, subsets[island].parent);
  
    return subsets[island].parent;
  }
};

int main()
{
  Solution sol;
  vector<pair<int, int>> pos;

  pos.push_back(make_pair<int,int>(0, 0));
  pos.push_back(make_pair<int,int>(7, 1));
  pos.push_back(make_pair<int,int>(6, 1));
  pos.push_back(make_pair<int,int>(3, 3));
  pos.push_back(make_pair<int,int>(4, 1));

  vector<int> res = sol.numIslands2(8, 4, pos);
  for (int i = 0; i < res.size(); i++)
    cout << res[i] << endl;

  return 0;
}
