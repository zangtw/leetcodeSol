#include <iostream>
#include <vector>
#include <list>
using namespace std;

typedef struct Interval {
  int start;
  int end;
  Interval() : start(0), end(0) {}
  Interval(int s, int e) : start(s), end(e) {}
} Interval;

class Solution {
public:
  vector<Interval> merge(vector<Interval>& intervals) {
    int n = intervals.size();
    list<Interval> intervalSet;
    vector<Interval> res;
    
    for (int i = 0; i < n; i++)
    {
      auto myInterval = intervals[i];
    
      for (auto it = intervalSet.begin(); it != intervalSet.end(); )
      {
        auto currInterval = *it;
    
        if (haveIntersection(currInterval, myInterval))
        {
          merge(currInterval, myInterval);
          it = intervalSet.erase(it);
        }
        else
          it++;
      }
    
      intervalSet.push_back(myInterval);
    }
    
    for (auto& interval : intervalSet)
      res.push_back(interval);
    
    return res;
  }
  
  bool haveIntersection(Interval a1, Interval a2)
  {
    return (a2.start >= a1.start && a2.start <= a1.end) ||
           (a2.end >= a1.start && a2.end <= a1.end) ||
           (a1.start >= a2.start && a1.start <= a2.end) ||
           (a1.end >= a2.start && a1.end <= a2.end);
  }
  
  void merge(Interval& strt, Interval& dest)
  {
    dest.start = min(strt.start, dest.start);
    dest.end = max(strt.end, dest.end);
  }
};

int main()
{
  Solution sol;

  // need test cases

  return 0;
}
