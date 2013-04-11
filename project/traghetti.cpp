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
  vector<int> parent(n, -1);
  bool visited[n];
  vector<int> maxPath;

  fill(visited, visited+n, false);
  visited[node] = true;
  q.push(node);

  while(!q.empty()) {
    v = q.front();
    q.pop();

    for(size_t i=0; i<edges[v].size(); i++) {
      u = edges[v][i];
      if (!visited[u]) {
        parent[u] = v;
        visited[u] = true;
        q.push(u);
      }
    }
  }

  for (; v != -1; v = parent[v])
    maxPath.push_back(v);

  return maxPath;
}

vector<int> maxwalk()
{
    vector<int> nodes[n];
    vector<int> maxPath;
    vector<int> tmp;
    size_t i;

    for (i=0; i != n; i++)
        if (edges[i].size() == 1) {
            tmp = bfs(i);
            return bfs(tmp[0]);
        }
    return maxPath;
}

int main()
{
    int start, end;
    int ret[4];
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<int> path;


    in >> n >> m;
    edges = new vector<int>[n];

    for (size_t i=0; i!=m; i++) {
        in >> start >> end;
        edges[start].push_back(end);
        edges[end].push_back(start);
    }

    path = maxwalk();
    start = end = (path.size()- (1+path.size())%2) / 2;
    if(path.size() % 2 == 1) // odd
      end++;
    else
      start--;

    ret[0] = path[start];
    ret[1] = path[end];

    vector<int>* v = &edges[ret[0]];
    v->erase(find(v->begin(), v->end(), ret[1]));

    v = &edges[ret[1]];
    v->erase(find(v->begin(), v->end(), ret[0]));

    vector<int> left = bfs(path[0]);
    vector<int> right = bfs(path[path.size()-1]);
    ret[2] = left[left.size() / 2];
    ret[3] = right[right.size() / 2];

    out << ret[0] << " " << ret[1] << endl
        << ret[2] << " " << ret[3];

    return 0;
}

