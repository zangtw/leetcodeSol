#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
  public:
  vector<vector<int>> palindromePairs(vector<string>& words) {
    int n = words.size();
    vector<vector<int>> res;
    unordered_map<string, int> strMap;
    
    for (int i = 0; i < n; i++)
      strMap[words[i]] = i;
    
    for (int i = 0; i < n; i++)
    {
      int k = words[i].size();
      if (k == 0) continue;
    
      string tempStr;

      //find its reverse
      tempStr = words[i];
      reverse(tempStr.begin(), tempStr.end());
      if (strMap.find(tempStr) != strMap.end() && strMap[tempStr] > i)
      {
        res.push_back(vector<int>{strMap[tempStr], i});
        res.push_back(vector<int>{i, strMap[tempStr]});
      }

      //find empty string
      tempStr = words[i];
      if (strMap.find("") != strMap.end() && isPalindrome(tempStr))
      {
        res.push_back(vector<int>{strMap[""], i});
        res.push_back(vector<int>{i, strMap[""]});
      }
        
      //left grow
      tempStr = words[i];
      for (int j = 0; j < k - 1; j++)
      {
        tempStr.insert(j, 1, words[i][k - 1 - j]);
    
        string tempStr2 = tempStr.substr(0, j + 1);
    
        if (strMap.find(tempStr2) != strMap.end() && isPalindrome(tempStr))
          if (strMap[tempStr2] != i)
            res.push_back(vector<int>{strMap[tempStr2], i});
      }
      
      //right grow
      tempStr = words[i];
      for (int j = 0; j < k - 1; j++)
      {
        tempStr.insert(k, 1, words[i][j]);
                                                                  
        string tempStr2 = tempStr.substr(k, j + 1);

        if (strMap.find(tempStr2) != strMap.end() && isPalindrome(tempStr))
          if (strMap[tempStr2] != i)
            res.push_back(vector<int>{i, strMap[tempStr2]});
      }
    }
    
    return res;
  }
  
  bool isPalindrome(string& s)
  {
    int n = s.size();
    int lo = 0, hi = n - 1;
    
    while (lo < hi)
    {
      if (s[lo] != s[hi]) break;
      lo++;
      hi--;
    }
    
    return (lo >= hi);
  }
};

int main()
{
  vector<string> words;
  words.push_back("a");
  words.push_back("b");
  words.push_back("c");
  words.push_back("ab");
  words.push_back("ac");
  words.push_back("aa");

  Solution sol;

  vector<vector<int>> res = sol.palindromePairs(words);

  for (int i = 0; i < res.size(); i++)
    cout << res[i][0] << ", " << res[i][1] << endl;

  return 0;
}
