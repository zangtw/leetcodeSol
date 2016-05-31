#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0) return 0;
    int n = matrix[0].size();
    if (n == 0) return 0;
     
    int res = INT_MIN;
    vector<vector<int>> memo(m, vector<int>(n, -1));
    vector<vector<bool>> visited(m, vector<bool>(n, false));
     
    for (int x = 0; x < m; x++)
      for (int y = 0; y < n; y++)
      {
        longestIncreasingPathUtil(matrix, x, y, visited, memo);
    
        res = max(res, memo[x][y]);
      }
    
    return res;
  }
  
  void longestIncreasingPathUtil(vector<vector<int>>& matrix, int x, int y, 
    vector<vector<bool>>& visited, vector<vector<int>>& memo)
  {
    int m = matrix.size(), n = matrix[0].size();
    if (memo[x][y] != -1) return;
    
    // dfs steps
    
    visited[x][y] = true;
    int len = 0;

    // up
    if (x - 1 >= 0 && !visited[x - 1][y] && matrix[x - 1][y] > matrix[x][y])
    {
      if (memo[x - 1][y] == -1)
        longestIncreasingPathUtil(matrix, x - 1, y, visited, memo);
    
      len = max(len, memo[x - 1][y]);
    }
    
    // down
    if (x + 1 < m && !visited[x + 1][y] && matrix[x + 1][y] > matrix[x][y])
    {
      if (memo[x + 1][y] == -1)
        longestIncreasingPathUtil(matrix, x + 1, y, visited, memo);
    
      len = max(len, memo[x + 1][y]);
    }
    
    // left
    if (y - 1 >= 0 && !visited[x][y - 1] && matrix[x][y - 1] > matrix[x][y])
    {
      if (memo[x][y - 1] == -1)
        longestIncreasingPathUtil(matrix, x, y - 1, visited, memo);
    
      len = max(len, memo[x][y - 1]);
    }
    
    // right
    if (y + 1 < n && !visited[x][y + 1] && matrix[x][y + 1] > matrix[x][y])
    {
      if (memo[x][y + 1] == -1)
        longestIncreasingPathUtil(matrix, x, y + 1, visited, memo);
    
      len = max(len, memo[x][y + 1]);
    }
    
    memo[x][y] = len + 1;
    visited[x][y] = false;
  }
};

int main()
{
  Solution sol;

  // need test cases

  return 0;
}
