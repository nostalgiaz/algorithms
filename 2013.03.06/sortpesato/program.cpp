#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>

using namespace std;

int s(vector<int> v, int n) {
  int s=0, tmp;

  for(int i=n-1; i>=0; i--)
    for(int j=0; j<n; j++)
      if(v[j] == i+1 && j!=i) {
        tmp = v[j];
        v[j] = v[i];
        v[i] = tmp;
        s++;
        break;
      }

  return s;
}

int searchNumber(vector<int> v, int n, int f, int s) {
   for(int i=s; i<n; i++)
      if(v[i]==f)
        return i;
}

int p(vector<int> v, int n) {
  int p=0, current=0, posCurrent, targetPos, tmpSum, tmpCount, tmp;

  for(int i=0; i<n; i++) {
    tmpSum = 0;
    tmpCount = 0;

    posCurrent = searchNumber(v, n, current+1, i);

    while(current != posCurrent) {
      targetPos = searchNumber(v, n, posCurrent+1, 0);

      tmpSum += v[targetPos];
      tmpCount++;

      tmp = v[targetPos];
      v[targetPos] = v[posCurrent];
      v[posCurrent] = tmp;

      posCurrent = targetPos;
    }
    p += min(
          tmpSum + v[current] * tmpCount,
          2*(1 + v[current]) + tmpSum + 1 * tmpCount
        );

    current++;
  }

  return p;
}

int main(void) {
  int n, tmp;
  vector<int> v, v1;

  ifstream in("input.txt");
  in >> n;

  for(int i=0; i<n; i++) {
    in >> tmp;
    v.push_back(tmp);
    v1.push_back(tmp);
  }

  ofstream out("output.txt");
  out << s(v, n) << " " << p(v1, n);
  return 0;
}
