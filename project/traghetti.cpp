#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int n, m;
vector<int>* edges;


vector<int> maxdfs(int i, vector<int>* maxdepth)
{
  /*
    vector<int> ret = {0, 2, 3, 5, 7, 8, 10};

    int m = 0;
    int tmp;

    if (!maxdepth[i].size()) return maxdepth[i];

    for (vector<int>::const_iterator it = edges[i].begin(); it != edges[i].end(); it++) {
        maxdepth[i] = maxdfs(*it, maxdepth);
        if (maxdepth[i].size() > m) m = maxdepth[i].size();
    }

    maxdepth[i] = m + 1;
    return maxdepth[i];
    */
}

vector<int> maxwalk()
{
  /*
    vector<int> nodes[n];
    size_t i;

    fill(nodes, nodes+n, 0);

    for (i=0; i != n; i++)
        if (edges[i] == 1)
            break;

    maxdfs(i, nodes);

    return *max_element(nodes, nodes+n);
    */
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

    vector<int> path;
    path.push_back(0);
    path.push_back(2);
    path.push_back(3);
    path.push_back(5);
    path.push_back(7);
    path.push_back(8);
    path.push_back(10);

    pair<int, int> zombieEdge;
    pair<int, int> newEdge;

    start = end = path.size() / 2;
    if(path.size() % 2 == 1) // odd
      end++;
    else // pair
      start--;

    zombieEdge = make_pair(path[start], path[end]);

    newEdge = make_pair(path[start / 2], path[path.size() - (end / 2)]);

    cout << "zombie: " << zombieEdge.first << "-" << zombieEdge.second;
    cout << endl << "new: " << newEdge.first << "-" << newEdge.second;

    return 0;
}

