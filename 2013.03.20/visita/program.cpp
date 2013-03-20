#include <iostream>
#include <vector>
#include <fstream>
#define MAX 10000

using namespace std;

vector<int> nodes [MAX];
int nodesBool [MAX];
int sum = 0;

int maxLength(int n) {
  nodesBool[n] = 1;
  for(int i=0; i<nodes[n].size(); i++)
    if(nodesBool[nodes[n][i]] == 0) {
       maxLength(nodes[n][i]);
       sum++;
    }
  return sum;
}

int main(void)
{
  int n, m, s, start, end;
  vector<int> tmp;

  ifstream in("input.txt");
  in >> n >> m >> s;

  for(int i=0; i<MAX; i++)
    nodesBool[i] = 0;

  for(int i=0; i<m; i++) {
    in >> start >> end;
    tmp = nodes[start];
    tmp.push_back(end);
    nodes[start] = tmp;
  }

  ofstream out("output.txt");
  out << 1 + maxLength(s);

  return 0;
}
