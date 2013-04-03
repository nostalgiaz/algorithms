#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector< vector<int> > nodes;
vector<bool> nodesMask;
vector<int> nodesDepth;
vector<int> nodesBool;

int max_ = 0;

void bfs(int s) {
  queue<int> q;

  q.push(s);
  nodesDepth[s] = 0;

  while (!q.empty()) {
    s = q.front();
    q.pop();

    nodesBool[s] = true;

    for (int i=0; i < nodes[s].size(); i++) {
      int tmp = nodes[s][i];
      if (nodesDepth[tmp] == -1 || nodesDepth[s] + 1 > nodesDepth[tmp]) {
        q.push(tmp);
        nodesDepth[tmp] = nodesDepth[s] + 1;
      }
    }
  }
}

int main(void)
{
  int n, m, start, end;

  ifstream in("input.txt");
  in >> n >> m;

  nodes.resize(n);
  nodesMask.resize(n);
  nodesBool.resize(n);
  nodesDepth.resize(n);

  for(int i=0; i<n; i++) {
    nodesMask[i] = true;
    nodesBool[i] = true;
    nodesDepth[i] = -1;
  }

  for(int i=0; i<m; i++) {
    in >> start >> end;
    nodes[start].push_back(end);
    nodesMask[end] = false;
  }

  for(int i=0; i<n; i++) {
    if(nodesMask[i]) {
      for(int j=0; j<n; j++)
        nodesDepth[j] = -1;

      bfs(i);

      for(int j=0; j<n; j++)
        max_ = max(nodesDepth[j], max_);
    }
  }

  ofstream out("output.txt");
  out << max_;
  return 0;
}
