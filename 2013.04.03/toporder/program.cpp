#include <iostream>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

vector< vector<int> > nodes;
vector<int> nodesBool;
stack<int> s;

void dfs(int n) {
  nodesBool[n] = true;

  for (int i=0; i < nodes[n].size(); i++) {
    int tmp = nodes[n][i];
    if(!nodesBool[tmp])
      dfs(tmp);
  }

  s.push(n);
}

int main(void)
{
  int n, m, start, end;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> n >> m;

  nodes.resize(n);
  nodesBool.resize(n);

  for(int i=0; i<n; i++)
    nodesBool[i] = false;

  for(int i=0; i<m; i++) {
    in >> start >> end;
    nodes[start].push_back(end);
  }

  for(int i=0; i<n; i++) {
    if(!nodesBool[i]) {
      dfs(i);
    }
  }

  while(!s.empty()) {
    out << s.top() << " ";
    s.pop();
  }

  return 0;
}
