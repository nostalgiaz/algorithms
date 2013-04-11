#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m;
vector<int>* edges;

vector<int> bfs(int node) {
  int u, v;
  queue<int> q;
  vector<int> parent (n, -1);
  vector<bool> nodesBool (n, false);
  vector<int> maxPath;

  q.push(node);
  nodesBool[node] = true;

  while(!q.empty()) {
    v = q.front();
    q.pop();

    for(int i=0; i<edges[v].size(); i++) {
      u = edges[v][i];
      if(!nodesBool[u]) {
        parent[u] = v;
        nodesBool[u] = true;
        q.push(u);
      }
    }
  }

  while(v != -1) {
    maxPath.push_back(v);
    v = parent[v];
  }

  return maxPath;
}

vector<int> maxwalk()
{
    vector<int> nodes[n];
    vector<int> maxPath;
    vector<int> tmp;
    size_t i;

    tmp = bfs(0);
    return bfs(tmp[0]);

    return maxPath;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int start, end;

    in >> n >> m;
    edges = new vector<int>[n];

    for (size_t i=0; i!=m; i++) {
        in >> start >> end;
        edges[start].push_back(end);
        edges[end].push_back(start);
    }

    vector<int> path = maxwalk();

    pair<int, int> zombieEdge;
    pair<int, int> newEdge;

    start = end = (path.size() - 1 + path.size() %2) / 2;
    end++;
    cout << start << path.size() << endl;

    zombieEdge = make_pair(path[start], path[end]);

    vector<int>* v = &edges[zombieEdge.first];
    v->erase(find(v->begin(), v->end(), zombieEdge.second));

    v = &edges[zombieEdge.second];
    v->erase(find(v->begin(), v->end(), zombieEdge.first));

  vector<int> left = bfs(path[0]);
  vector<int> right = bfs(path[path.size() -1]);

  cout << "PATH: ";
  for(int i=0; i<path.size(); i++)
    cout << path[i] << " ";
  cout << endl;

  cout << "LEFT: ";
  for(int i=0; i<left.size(); i++)
    cout << left[i] << " ";
  cout << endl;

  cout << "RIGHT: ";
  for(int i=0; i<right.size(); i++)
    cout << right[i] << " ";
  cout << endl;

   newEdge = make_pair(left[left.size() / 2], right[right.size() / 2]);

    out << zombieEdge.first << " " << zombieEdge.second << endl;
    out << newEdge.first << " " << newEdge.second;

    return 0;
}

