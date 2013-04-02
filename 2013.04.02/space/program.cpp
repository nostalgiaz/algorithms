#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <limits>
#define MAX 500000

using namespace std;

enum colors {BLACK, WHITE, GRAY};
int color[MAX], d[MAX], p[MAX], f[MAX], low[MAX], t, vertex, edge, bridgeCounter;
int NIL = numeric_limits<int>::min();

vector<int> adjList[MAX];
vector< pair<int,int> > bridge;
vector< pair<int,int> >::iterator it;

vector<int> island[MAX];
vector<int> islandBridge[MAX];
int islandReverse[MAX];
vector<int> vicereTmp;
vector<int> vicere;
int nodeBool[MAX];

int giveMeTheVicere(int cc, int i) {
  for(int j=0; j<=cc; j++) {
    for(int z=0; z<island[j].size(); z++) {
      if(vicereTmp[i] == island[j][z]) {
        if(island[j].size() != 1)
          return island[j][(z == 0? 1 : 0)];
        else return island[j][0];
      }
    }
  }
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
      if(low[v] > d[u]) {
        bridgeCounter++;
        bridge.push_back(make_pair(u,v));
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

void DFS(vector<int> G[]) {
  for(int u=0; u<vertex; u++) {
    color[u] = WHITE;
    p[u] = NIL;
  }
  t = 0, bridgeCounter = 0;
  for(int u=0; u<vertex; u++) {
    if(color[u] == WHITE) {
      DFS_VISIT(G,u);
    }
  }
}

void ARTICULATION_BRIDGE(vector<int> G[]) {
  DFS(G);
  sort(bridge.begin(), bridge.end());
}

int main(void)
{
  int u, v, cc = -1;
  bool same;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> vertex >> edge;

  for(int e=0; e<edge; e++) {
    in >> u >> v;
    adjList[u].push_back(v);
    adjList[v].push_back(u);
  }

  ARTICULATION_BRIDGE(adjList);

  for(it=bridge.begin(); it != bridge.end(); ++it) {
    int index = find(adjList[it->first].begin(), adjList[it->first].end(), it->second) - adjList[it->first].begin();
    adjList[it->first].erase(adjList[it->first].begin() + index);

    index = find(adjList[it->second].begin(), adjList[it->second].end(), it->first) - adjList[it->second].begin();
    adjList[it->second].erase(adjList[it->second].begin() + index);
  }

  for(int i=0; i<vertex; i++)
    nodeBool[i] = 0;

  for(int i=0; i<vertex; i++) {
    if(nodeBool[i] == 0) {
      cc++;
      island[cc].push_back(i);
      islandReverse[i] = cc;
      queue<int> q;
      q.push(i);
      nodeBool[i] = 1;
      while(!q.empty()){
        int u, v;
        v = q.front();
        q.pop();
        for(int j=0; j<adjList[v].size(); j++){
          u = adjList[v][j];
          if(nodeBool[u] == 0) {
            nodeBool[u] = 1;
            island[cc].push_back(u);
            islandReverse[u] = cc;
            q.push(u);
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

    if(islandBridge[i].size() > 1) {
      for(int j=1; j<islandBridge[i].size(); j++) {
        if(islandBridge[i][j-1] != islandBridge[i][j]) {
          same=false;
          break;
        }
      }
      if(same) {
        if(island[islandReverse[islandBridge[i][0]]].size() > 1)
          vicereTmp.push_back(islandBridge[i][0]);
      }
    }
  }

  for(int i=0; i<vicereTmp.size(); i++)
    vicere.push_back(giveMeTheVicere(cc, i));

  out << vicere.size() << endl;

  for(int i=0; i<vicere.size(); i++)
    out << vicere[i] << " ";

  return 0;
}
