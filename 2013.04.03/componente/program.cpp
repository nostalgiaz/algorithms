#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector< vector<int> > nodes;
vector<int> nodesDepth;
vector<int> nodesMask;

int bfs(int s) {
  int parent, u;
  queue<int> q;

  q.push(s);

  while (!q.empty()) {
    parent = q.front();
    q.pop();

    for (int i=0; i<nodes[parent].size(); i++) {
      u = nodes[parent][i];
      q.push(u);
      nodesDepth[u] = nodesDepth[parent] + 1;
    }
  }
  return nodesDepth[u];
}

int main(void)
{
  int n, m, start, end, len=0;

  ifstream in("input.txt");
  in >> n >> m;

  nodes.resize(n);
  nodesDepth.resize(n);
  nodesMask.resize(n);

  for(int i=0; i<n; i++)
    nodesMask[i] = 0;

  for(int i=0; i<m; i++) {
    in >> start >> end;
    nodes[start].push_back(end);
    nodesMask[end] = -1;
  }

  for(int i=0; i<n; i++) {
    if(nodesMask[i] == 0) {
      for(int j=0; j<n; j++)
        nodesDepth[j] = 0;
      len = max(bfs(i), len);
    }
  }

  ofstream out("output.txt");
  out << len;
  return 0;
}
