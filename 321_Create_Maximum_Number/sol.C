#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) 
  {
    int m = nums1.size(), n = nums2.size();
  
    vector<vector<int>> rangeMaxIdx1(m, vector<int>(m, -1));
    vector<vector<int>> rangeMaxIdx2(n, vector<int>(n, -1));

    createRangeMaxIdx(rangeMaxIdx1, m, nums1);
    createRangeMaxIdx(rangeMaxIdx2, n, nums2);
    
    vector<int> maxSolution(k, -1);
    for (int i = 0; i <= k; i++)
    {
      int j = k - i;
      if (i > m || j > n)
        continue;

      vector<int> partialSolution1 = maxNumber1D(nums1, i, rangeMaxIdx1);
      vector<int> partialSolution2 = maxNumber1D(nums2, j, rangeMaxIdx2);

      vector<int> solution = mergePartial(partialSolution1, partialSolution2);

      int p;
      for (p = 0; p < k; p++)
      {
        if (solution[p] < maxSolution[p])
          break;
        else if (solution[p] > maxSolution[p])
        {
          maxSolution = solution;
          break;
        }
      }
    }
  
    return maxSolution;
  }

  void createRangeMaxIdx(vector<vector<int>>& res, int dim, vector<int>& nums)
  {
    for (int i = 0; i < dim; i++)
    {
      for (int j = i; j < dim; j++)
      {
        if (j == i) 
          res[i][j] = i;
        else if (nums[j] > nums[res[i][j - 1]])
          res[i][j] = j;
        else
          res[i][j] = res[i][j - 1];
      }
    }
  }
    
  vector<int> maxNumber1D(vector<int>& nums, int k, 
      vector<vector<int>>& rangeMaxIdx)
  {
    int n = nums.size();
    int p1 = 0, p2 = n - k;
    vector<int> res;
  
    for (int i = 0; i < k; i++)
    {
      res.push_back(nums[rangeMaxIdx[p1][p2]]);
      p1 = rangeMaxIdx[p1][p2] + 1;
      p2++;
    }
    
    return res;
  }
  
  vector<int> mergePartial(vector<int>& nums1, vector<int>& nums2)
  {
    int m = nums1.size(), n = nums2.size();
    vector<int> res(m + n);
    
    int p = 0;
    int p1 = 0, p2 = 0;
    while (p < m + n)
    {
      bool moveP1;

      if (p1 < m && p2 < n)
      {
        if (nums1[p1] == nums2[p2])
        {
          int q = 0;
          while(p1 + q < m && p2 + q < n && nums1[p1 + q] == nums2[p2 + q])
            q++;

          if (p1 + q >= m && p2 + q < n)
            moveP1 = false;
          else if (p2 + q >= n)
            moveP1 = true;
          else 
            moveP1 = (nums1[p1 + q] > nums2[p2 + q]);
        }
        else
          moveP1 = (nums1[p1] > nums2[p2]);
      }
      else
        moveP1 = (p2 >= n);

      if (moveP1)
        res[p++] = nums1[p1++];
      else
        res[p++] = nums2[p2++];
    }
    
    return res;
  }
};

int main()
{
  int m, n;

  cout << "m: ";
  cin >> m;
  cout << "n: ";
  cin >> n;

  vector<int> nums1(m);
  vector<int> nums2(n);

  for (int i = 0; i < m; i++)
    cin >> nums1[i];

  for (int i = 0; i < n; i++)
    cin >> nums2[i];

  int k;
  cout << "k: ";
  cin >> k;

  Solution sol;
  vector<int> res = sol.maxNumber(nums1, nums2, k);

  for (auto& x : res)
    cout << x;
  cout << endl;

  return 0;
}
