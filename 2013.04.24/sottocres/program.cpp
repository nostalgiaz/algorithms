#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> v, r;
int n;

int maxSumHelper(int k) {
  int val, max_ = 0;

  if(r[k] == -1) {
    for(int i=0; i<k; i++) {
      val = maxSumHelper(i);
      if(v[i] <= v[k] && val > max_)
        max_ = val;
    }
    r[k] = max_ + v[k];
  }

  return r[k];
}

int maxSum() {
  int max_ = 0;
  for(int i=0; i<n; i++)
    max_ = max(maxSumHelper(i), max_);

  return max_;
}

int main (void) {
  int tmp;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> n;

  r.resize(n, -1);

  for(int i=0; i<n; i++) {
    in >> tmp;
    v.push_back(tmp);
  }

  out << maxSum() << endl;
  return 0;
}
