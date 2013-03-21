#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#define MAX 10000

using namespace std;

vector<int> nodes [MAX];
int nodesBool [MAX], nodesDepth[MAX];
int acc=0, depth=0;

int bfs(int s, int t) {
  int tmp, u;
  queue<int> q;

  q.push(s);
  nodesBool[s] = 1;

  while (!q.empty()) {
    tmp = q.front();
    q.pop();

    if (tmp == t)
      return nodesDepth[tmp];

    for (int i=0; i<nodes[tmp].size(); i++) {
       u = nodes[tmp][i];
      if (nodesBool[u] == 0) {
        q.push(u);
        nodesBool[u] = 1;
        nodesDepth[u] = nodesDepth[tmp] + 1;
      }
    }
  }
  return -1;
}

int dfs(int n, int t, int len) {
  int u;
  nodesBool[n] = 1;
  depth++;

  for(int i=0; i<nodes[n].size(); i++) {
    u = nodes[n][i];
    if(nodesBool[u] == 0) {
      if(depth <= len) {
        if(u == t) {
          if(depth == len) {
            acc++;
          }
        }
        dfs(u, t, len);
      } else {
        depth++;
      }
      nodesBool[u] = 0;
      depth--;
    }
  }
  return acc;
}

int main(void)
{
  int n, m, s, t, start, end, len;
  vector<int> tmp;

  ifstream in("input.txt");
  in >> n >> m >> s >> t;

  for(int i=0; i<MAX; i++) {
    nodesBool[i] = 0;
    nodesDepth[i] = 0;
  }

  for(int i=0; i<m; i++) {
    in >> start >> end;
    tmp = nodes[start];
    tmp.push_back(end);
    nodes[start] = tmp;
  }

  len = bfs(s, t);

  for(int i=0; i<MAX; i++)
    nodesBool[i] = 0;

  ofstream out("output.txt");
  out << len << " " << dfs(s, t , len);
  return 0;
}
