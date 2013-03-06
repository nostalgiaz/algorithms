#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main(void) {
  int n, s, f;
  vector< pair<int, int> > intervals, r;
  pair<int, int> p1, p2;

  ifstream in("input.txt");
  in >> n;

  for(int i=0; i<n; i++) {
    in >> s;
    in >> f;
    intervals.push_back(make_pair(s, f));
  }

  sort(intervals.begin(), intervals.end());

  r.push_back(intervals[0]);

  for(int i=1; i<n; i++) {
    p1 = r.back();
    p2 = intervals[i];
    if(p1.second >= p2.first) {  // intersezione
      r.pop_back();
      if (p1.second >= p2.second) // compreso
        r.push_back(p1);
      else r.push_back(make_pair(p1.first, p2.second));
    }
    else r.push_back(p2);
  }

  pair<int, pair<int, int> > p;
  int tmp = r[0].second;
  p = make_pair(tmp, make_pair(tmp, tmp));

  for(int i=1; i<r.size(); i++) {
    if(p.second.first - p.first < r[i].first - p.second.second) {
      p = make_pair(p.second.second, r[i]);
    } 
    else p.second.second = r[i].second;
  }

  ofstream out("output.txt");

  if (p.first == p.second.first)
    out << "0";
  else out << p.first << " " << p.second.first;

  return 0;
}
