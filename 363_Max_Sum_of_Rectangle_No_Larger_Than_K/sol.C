#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution {
public:
  int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
    int m = matrix.size(), n = matrix[0].size();
    if (m == 0 || n == 0) return 0;
    
    int dim1 = min(m, n);
    int dim2 = max(m, n);
    bool bRow = (dim1 == m);

    vector<vector<int>> sumMemo(m, vector<int>(n));
  
    calcSumMemo(sumMemo, matrix);
    int maxArea = INT_MIN;

    for (int i1 = 0; i1 < dim1; i1++)
      for(int i2 = i1; i2 < dim1; i2++)
      {
        set<int> sums;
        int areaSum = 0;

        for (int j = 0; j < dim2; j++)
        {
          int newArea = bRow ? sumMemo[i2][j] : sumMemo[j][i2];
          if (j >= 1)
            newArea -= bRow ? sumMemo[i2][j - 1] : sumMemo[j - 1][i2];
          if (i1 >= 1)
            newArea -= bRow ? sumMemo[i1 - 1][j] : sumMemo[j][i1 - 1];
          if (i1 >= 1 && j >= 1)
            newArea += bRow ? sumMemo[i1 - 1][j - 1] : sumMemo[j - 1][i1 - 1];
    
          areaSum += newArea;
  
          sums.insert(newArea - areaSum);
 
          int newMaxArea = *(sums.rbegin());
          if (newMaxArea + areaSum > k)
          {
            auto iter = sums.upper_bound(k - areaSum);
            if (iter != sums.begin())
              iter--;

            newMaxArea = *iter;
          }
  
          if (newMaxArea + areaSum <= k)
            maxArea = max(maxArea, newMaxArea + areaSum);
  
          if (maxArea == k)
            return k;
        }
      }
  
    return (maxArea == INT_MIN) ? 0 : maxArea;
  }
  
  void calcSumMemo(vector<vector<int>>& sumMemo, vector<vector<int>>& matrix)
  {
    int m = matrix.size(), n = matrix[0].size();
  
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
      {
        sumMemo[i][j] = matrix[i][j];
        if (j >= 1)
          sumMemo[i][j] += sumMemo[i][j - 1];
        if (i >= 1)
          sumMemo[i][j] += sumMemo[i - 1][j];
        if (i >= 1 && j >= 1)
          sumMemo[i][j] -= sumMemo[i - 1][j - 1];
      }
  }
};

int main()
{
  Solution sol;
  int m, n;

  cout << "m:";
  cin >> m;
  cout << "n:";
  cin >> n;

  vector<vector<int>> matrix(m, vector<int>(n, 0));

  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++)
cin >> matrix[i][j];
  
  int k;
  cout << "k:";
  cin >> k;

  cout << sol.maxSumSubmatrix(matrix, k) << endl;

  return 0;
}
