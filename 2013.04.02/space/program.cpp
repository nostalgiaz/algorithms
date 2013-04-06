#include <fstream>
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <set>
#include <limits>
#define MAX 500000

using namespace std;

enum colors {BLACK, WHITE, GRAY};
int color[MAX], d[MAX], p[MAX], f[MAX], low[MAX], t, n, m, cc=-1;
int NIL = numeric_limits<int>::min();
int u, v, index_, begin, end;

list<int> articulationNodes;
list<int>::iterator it;

vector< vector<int> > nodes;
vector< vector<int> > island;
vector<bool> nodesBool;
vector<int> vicere;

void dfsVisit(int u) {
  t++;
  d[u] = low[u] = t;
  color[u] = GRAY;
  for(int i=0; i<nodes[u].size(); i++) {
    int v = nodes[u][i];
    if(color[v] == WHITE) {
      p[v] = u;
      dfsVisit(v);
      if(d[u] == 1) {
        if(nodes[u].size() >= 2 && low[v] > d[u]) {
          articulationNodes.push_front(u);
        }
      } else if(low[v] >= d[u]) {
        articulationNodes.push_front(u);
      }
      low[u] = min(low[u],low[v]);
    } else if(p[u] != v) {
      low[u] = min(low[u],d[v]);
    }
  }
  color[u] = BLACK;
  t++;
  f[u] = t;
}

void dfs() {
  for(int u=0; u<n; u++) {
    color[u] = WHITE;
    p[u] = NIL;
  }
  t = 0;
  for(int u=0; u<n; u++)
    if(color[u] == WHITE)
      dfsVisit(u);
}

void connectedComponents() {
  for(int i=0; i<n; i++) {
    if(!nodesBool[i]) {
      queue<int> q;
      q.push(i);
      nodesBool[i] = true;
      cc++;
      island[cc].push_back(i);
      while(!q.empty()) {
        int u, v;
        v = q.front();
        q.pop();
        for(int j=0; j<nodes[v].size(); j++) {
          u = nodes[v][j];
          if(!nodesBool[u]) {
            q.push(u);
            nodesBool[u] = true;
            island[cc].push_back(u);
          }
        }
      }
    }
  }
}

int main(void)
{
  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> n >> m;

  nodes.resize(n);
  nodesBool.resize(n, false);
  island.resize(n);

  for(int i=0; i<m; i++) {
    in >> u >> v;
    nodes[u].push_back(v);
    nodes[v].push_back(u);
  }

  dfs();

  articulationNodes.unique();

  for(it=articulationNodes.begin(); it != articulationNodes.end(); ++it)
    nodesBool[*it] = true;

  connectedComponents();

  if(cc == 0) {
    out << "2" << endl << "0 1";
    return 0;
  }

  for(int i=0; i<=cc; i++) {
    set<int> s;

    for(int j=0; j<island[i].size(); j++) {
      s.insert(island[i][j]);
      for(int k=0; k<nodes[island[i][j]].size(); k++) {
        s.insert(nodes[island[i][j]][k]);
      }
    }

    if(s.size() == island[i].size() + 1)
      vicere.push_back(island[i][0]);
  }

  out << vicere.size() << endl;

  for(int i=0; i<vicere.size(); i++)
    out << vicere[i] << " ";

  return 0;
}
