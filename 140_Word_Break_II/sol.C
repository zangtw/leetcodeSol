#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
  vector<string> wordBreak_botup(string s, unordered_set<string>& wordDict) 
  {
    int n = s.size();
    if (n == 0) return vector<string>();
    
    vector<vector<string>> wordBreak_dp(n, vector<string>());
    
    for (int i = n - 1; i >= 0; i--)
      wordBreakUtil_botup(s, i, wordDict, wordBreak_dp);
    
    return wordBreak_dp[0];
  }
  
  void wordBreakUtil_botup(string& s, int idx, unordered_set<string>& wordDict,
    vector<vector<string>>& wordBreak_dp)
  {
    for (int i = idx; i < s.size(); i++)
    {
      string subStr = s.substr(idx, i - idx + 1);
  
      if (wordDict.find(subStr) != wordDict.end())
      {
        if (i == s.size() - 1)
          wordBreak_dp[idx].push_back(subStr);
        else if (wordBreak_dp[i + 1].size() > 0)
        {
          for (auto& str : wordBreak_dp[i + 1])
            wordBreak_dp[idx].push_back(subStr + " " + str);
        }
      }
    }
  }
  
  vector<string> wordBreak_topdn(string s, unordered_set<string>& wordDict) 
  {
    int n = s.size();
    if (n == 0) return vector<string>();
    
    vector<bool> visited(n, false);
    vector<vector<string>> wordBreak_memo(n, vector<string>());
    
    wordBreakUtil_topdn(s, 0, wordDict, wordBreak_memo, visited);
    
    return wordBreak_memo[0];
  }
  
  void wordBreakUtil_topdn(string& s, int idx, unordered_set<string>& wordDict,
    vector<vector<string>>& wordBreak_memo, vector<bool>& visited)
  {
    visited[idx] = true;

    for (int i = idx; i < s.size(); i++)
    {
      string subStr = s.substr(idx, i - idx + 1);
  
      if (wordDict.find(subStr) != wordDict.end())
      {
        if (i == s.size() - 1)
          wordBreak_memo[idx].push_back(subStr);
        else 
        {
          if (!visited[i + 1])
            wordBreakUtil_topdn(s, i + 1, wordDict, wordBreak_memo, visited);
        
          if (wordBreak_memo[i + 1].size() > 0)
            for (auto& str : wordBreak_memo[i + 1])
              wordBreak_memo[idx].push_back(subStr + " " + str);
        }
      }
    }
  }
};

int main()
{
  Solution sol;
  string s = "catsanddog";
  unordered_set<string> wordDict;

  wordDict.insert("cat");
  wordDict.insert("cats");
  wordDict.insert("and");
  wordDict.insert("sand");
  wordDict.insert("dog");

  vector<string> res = sol.wordBreak_topdn(s, wordDict);

  for (auto& singleRes : res)
      cout << singleRes << endl;

  return 0;
}
