#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <limits>
#define MAX 500000

using namespace std;

enum colors {BLACK, WHITE, GRAY};
int color[MAX], d[MAX], p[MAX], f[MAX], low[MAX], t, n, m;
int NIL = numeric_limits<int>::min();

vector<int> nodes[MAX];
vector< pair<int,int> > bridge;
vector< pair<int,int> >::iterator it;

vector<int> island[MAX];
vector<int> islandBridge[MAX];
int islandReverse[MAX];

vector<int> vicereTmp;
vector<int> vicere;
bool nodesBool[MAX];

int giveMeTheVicere(int vicere) {
  if(island[islandReverse[vicere]].size() == 1)
    return island[islandReverse[vicere]][0];

  int index = 0;
  int islandIndex = islandReverse[vicere];

  int bridgeOfTheCurrentIsland = islandBridge[islandIndex][0];
  if(bridgeOfTheCurrentIsland == vicere && vicere == island[islandIndex][0])
    index = 1;
  return island[islandIndex][index];
}

void DFS_VISIT(vector<int> G[], int u) {
  t++;
  d[u] = low[u] = t;
  color[u] = GRAY;
  for(int i=0; i<G[u].size(); i++) {
    int v = G[u][i];
    if(color[v] == WHITE) {
      p[v] = u;
      DFS_VISIT(G,v);
      if(low[v] > d[u])
        bridge.push_back(make_pair(u,v));
      low[u] = min(low[u],low[v]);
    }
    else if(p[u] != v)
      low[u] = min(low[u],d[v]);
  }
  color[u] = BLACK;
  t++;
  f[u] = t;
}

void DFS(vector<int> G[]) {
  for(int u=0; u<n; u++) {
    color[u] = WHITE;
    p[u] = NIL;
  }
  t = 0;
  for(int u=0; u<n; u++) {
    if(color[u] == WHITE) {
      DFS_VISIT(G,u);
    }
  }
}

void ARTICULATION_BRIDGE(vector<int> G[]) {
  DFS(G);
  sort(bridge.begin(), bridge.end());
}

int main(void) {
  int u, v, cc = -1;
  bool same;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> n >> m;

  for(int e=0; e<m; e++) {
    in >> u >> v;
    nodes[u].push_back(v);
    nodes[v].push_back(u);
  }

  ARTICULATION_BRIDGE(nodes);

  for(it=bridge.begin(); it != bridge.end(); ++it) {
    int index = find(nodes[it->first].begin(), nodes[it->first].end(), it->second) - nodes[it->first].begin();
    nodes[it->first].erase(nodes[it->first].begin() + index);

    index = find(nodes[it->second].begin(), nodes[it->second].end(), it->first) - nodes[it->second].begin();
    nodes[it->second].erase(nodes[it->second].begin() + index);
  }

  for(int i=0; i<n; i++)
    nodesBool[i] = false;

  for(int i=0; i<n; i++) {
    if(!nodesBool[i]) {
      queue<int> q;
      q.push(i);
      nodesBool[i] = true;
      cc++;
      island[cc].push_back(i);
      islandReverse[i] = cc;

      while(!q.empty()){
        int u, v;
        v = q.front();
        q.pop();
        for(int j=0; j<nodes[v].size(); j++){
          u = nodes[v][j];
          if(!nodesBool[u]) {
            q.push(u);
            nodesBool[u] = true;
            island[cc].push_back(u);
            islandReverse[u] = cc;
          }
        }
      }
    }
  }

  if (cc == 0) {  // cerchio
    out << "2\n0 1";
    return 0;
  }

  for(it=bridge.begin(); it != bridge.end(); ++it) {
    islandBridge[islandReverse[it->first]].push_back(it->first);
    islandBridge[islandReverse[it->second]].push_back(it->second);
  }

  for(int i=0; i<=cc; i++) {
    same = true;

    if(islandBridge[i].size() == 1)
      vicereTmp.push_back(islandBridge[i][0]);
    else if(islandBridge[i].size() > 1) {
      for(int j=1; j<islandBridge[i].size(); j++) {
        if(islandBridge[i][j-1] != islandBridge[i][j]) {
          same=false;
          break;
        }
      }
      if(same)
        if(island[islandReverse[islandBridge[i][0]]].size() > 1)
          vicereTmp.push_back(islandBridge[i][0]);
    }
  }

  for(int i=0; i<vicereTmp.size(); i++)
    vicere.push_back(giveMeTheVicere(vicereTmp[i]));

  out << vicere.size() << endl;

  for(int i=0; i<vicere.size(); i++)
    out << vicere[i] << " ";

  return 0;
}
