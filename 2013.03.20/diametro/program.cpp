#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define MAX 10000

using namespace std;

vector<int> nodes [MAX];
int nodesBool [MAX], nodesDepth [MAX];

void bfs(int node) {
  int u, v;
  queue<int> q;

  q.push(node);
  nodesBool[node] = 1;

  while(!q.empty()) {
    v = q.front();
    q.pop();

    for(int i=0; i<nodes[v].size(); i++) {
      u = nodes[v][i];
      if(nodesBool[u] == 0) {
        nodesBool[u] = 1;
        nodesDepth[u] = nodesDepth[v] + 1;
        q.push(u);
      }
    }
  }
}

int main(void)
{
  int n, m, start, end, max_=0;
  vector<int> tmp;

  ifstream in("input.txt");
  in >> n >> m;

  for(int i=0; i<m; i++) {
    in >> start >> end;
    tmp = nodes[start];
    tmp.push_back(end);
    nodes[start] = tmp;
    tmp = nodes[end];
    tmp.push_back(start);
    nodes[end] = tmp;
  }

  for(int i=0; i<n; i++) {
    for(int j=0; j<MAX; j++) {
      nodesBool[j] = 0;
      nodesDepth[j] = 0;
    }
    bfs(i);
    for(int j=0; j<MAX; j++)
      if (nodesDepth[j] > max_)
        max_ = nodesDepth[j];
  }

  ofstream out("output.txt");
  out << max_;

  return 0;
}
