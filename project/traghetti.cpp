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

int* lengthOf(int start, int end, int * response) {
  vector<int> tmp2;
  response[1] = path[start];
  response[2] = path[end];

  fill(visited, visited+n, false);
  visited[response[2]] = true;
  tmp2 = bfs(path[0]);
  fill(visited, visited+n, false);
  visited[response[2]] = true;
  vector<int> left = bfs(tmp2[0]);

  cout << "SPACCO A: " << response[1] << " " << response[2] << endl;

  cout << "LEFT :";
  printPath(left);

  fill(visited, visited+n, false);
  visited[response[1]] = true;
  tmp2 = bfs(path[path.size() - 1]);
  fill(visited, visited+n, false);
  visited[response[1]] = true;
  vector<int> right = bfs(tmp2[0]);

  cout << "RIGHT :";
  printPath(right);

  vector<int> *v = &edges[response[2]];
  v->erase(find(v->begin(), v->end(), response[1]));
  v = &edges[response[1]];
  v->erase(find(v->begin(), v->end(), response[2]));

  response[3] = left[left.size() / 2];
  response[4] = right[right.size()/ 2];

  cout << "ATTACCO A: " << response[3] << " " << response[4] << endl;

  edges[response[3]].push_back(response[4]);
  edges[response[4]].push_back(response[3]);

  fill(visited, visited+n, false);
  vector<int> tmp = maxwalk();
  cout << "CAMMINO ORA PIU LUNGO: ";
  printPath(tmp);

  response[0] = tmp.size();

  cout << "DI DIMENSIONE: " << response[0];

  v = &edges[response[4]];
  v->erase(find(v->begin(), v->end(), response[3]));
  v = &edges[response[3]];
  v->erase(find(v->begin(), v->end(), response[4]));

  edges[response[1]].push_back(response[2]);
  edges[response[2]].push_back(response[1]);

  cout << endl << endl;

  return response;
}

void doSomething() {
  // 0 lenght, 1 zombieFirst, 2 zombieLast, 3 newFirst, 4 newLast
  int result[4][5];
  int start = path.size()/ 2 -1;
  int end = start + 1;

  lengthOf(start, end, result[1]);
  lengthOf(start-1, end-1, result[0]);
  lengthOf(start+1, end+1, result[2]);

  if(path.size() % 2 == 1) // odd
    lengthOf(start + 2, end + 2, result[3]);
  else *result[3] = -1;

    cout << result[0][0] << " " << result[1][0] << " " << result[2][0] <<" " << result[3][0] << endl;

    int min_ = result[0][0];
    int index = 0;

    for(int i=1; i<4; i++)
      if(result[i][0] != -1) {
        if(min_ > result[i][0]) {
          min_ = result[i][0];
          index = i;
        }
      }

    for(int i=0; i<4; i++)
      ret[i] = result[index][i+1];
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

