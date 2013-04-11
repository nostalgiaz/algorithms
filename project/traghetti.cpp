#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, start, end;
vector<int>* edges;
bool* visited;
vector<int> path;

int ret[4];


vector<int> bfs(int node) {
  int u, v;
  queue<int> q;
  vector<int> parent(n, -1);
  vector<int> maxPath;

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

  fill(visited, visited+n, false);
  tmp = bfs(0);
  fill(visited, visited+n, false);
  return bfs(tmp[0]);
}

void printPath(vector<int> cucu) {
  for(int i=0; i<cucu.size(); i++)
    cout << cucu[i] << " ";
  cout << endl;
}

void doSomething() {
  pair<int, int> zombieEdge, zombieEdgeR;
  pair<int, int> newEdge, newEdgeR;
  vector<int> left, right, leftR, rightR, *v;
  start = (path.size()  - 1)/ 2 - path.size()%2;
  end = start + 1;

  zombieEdge = make_pair(path[start], path[end]);


    fill(visited, visited+n, false);
  visited[zombieEdge.second] = true;
  left = bfs(zombieEdge.first);

  cout << "LEFT :";
  printPath(left);

  fill(visited, visited+n, false);
  visited[zombieEdge.first] = true;
  right = bfs(zombieEdge.second);

  cout << "RIGHT :";
  printPath(right);

  cout << "CASO 1: " << zombieEdge.first << " " << zombieEdge.second << endl;

  if(path.size() % 2 == 1) {  // odd

    v = &edges[zombieEdge.second];
    v->erase(find(v->begin(), v->end(), zombieEdge.first));
    v = &edges[zombieEdge.first];
    v->erase(find(v->begin(), v->end(), zombieEdge.second));

  newEdge = make_pair(left[left.size() / 2], right[right.size() /2]);
  edges[newEdge.first].push_back(newEdge.second);
  edges[newEdge.second].push_back(newEdge.first);

    fill(visited, visited+n, false);
    vector<int> m1 = maxwalk();
    cout << newEdge.first << " " << newEdge.second << endl;
    cout << "M1: ";
    printPath(m1);

    edges[zombieEdge.second].push_back(zombieEdge.first);
    edges[zombieEdge.first].push_back(zombieEdge.second);

    v = &edges[newEdge.first];
    v->erase(find(v->begin(), v->end(), newEdge.second));
    v = &edges[newEdge.second];
    v->erase(find(v->begin(), v->end(), newEdge.first));

    // restored graph

    int startR = start + 1;
    int endR = end + 1;
    zombieEdgeR = make_pair(path[startR], path[endR]);

    fill(visited, visited+n, false);
    visited[zombieEdgeR.second] = true;
    leftR = bfs(zombieEdgeR.first);

    fill(visited, visited+n, false);
    visited[zombieEdgeR.first] = true;
    rightR = bfs(zombieEdgeR.second);

    newEdgeR = make_pair(leftR[leftR.size() / 2], rightR[rightR.size() /2]);

    edges[newEdgeR.second].push_back(newEdgeR.first);
    edges[newEdgeR.first].push_back(newEdgeR.second);

    v = &edges[zombieEdgeR.first];
    v->erase(find(v->begin(), v->end(), zombieEdgeR.second));
    v = &edges[zombieEdgeR.second];
    v->erase(find(v->begin(), v->end(), zombieEdgeR.first));

    cout << "CASO 2: " << zombieEdgeR.first << " " << zombieEdgeR.second << endl;
    fill(visited, visited+n, false);
    vector<int> m2 = maxwalk();

    cout << newEdgeR.first << " " << newEdgeR.second << endl;
    cout << "M2: ";
    printPath(m2);
    cout << "DIFFERENCE " << m1.size() << " - " << m2.size() << endl;

    if(m1.size() <= m2.size()) {
      ret[0] = zombieEdge.first;
      ret[1] = zombieEdge.second;
      ret[2] = newEdge.first;
      ret[3] = newEdge.second;
    }
    else {
      ret[0] = zombieEdgeR.first;
      ret[1] = zombieEdgeR.second;
      ret[2] = newEdgeR.first;
      ret[3] = newEdgeR.second;
    }
  }
  else {
    ret[0] = path[start];
    ret[1] = path[end];
    ret[2] = left[left.size() / 2];
    ret[3] = right[right.size() / 2];
  }
}

int main(int argc, char **argv)
{
  ifstream in(argc > 1 ? argv[1] : "input.txt");
  ofstream out("output.txt");

  in >> n >> m;
  edges = new vector<int>[n];
  visited = new bool[n];

  for (size_t i=0; i!=m; i++) {
    in >> start >> end;
    edges[start].push_back(end);
    edges[end].push_back(start);
  }

  path = maxwalk();

  doSomething();

  out << ret[0] << " " << ret[1] << endl
    << ret[2] << " " << ret[3];

  return 0;
}

