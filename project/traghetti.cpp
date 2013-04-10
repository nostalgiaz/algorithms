#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int>* edges;


vector<int>* maxdfs(int i, vector<int>* maxdepth)
{
<<<<<<< HEAD:traghetti.cpp
    vector<int>* m;
=======
  /*
    vector<int> ret = {0, 2, 3, 5, 7, 8, 10};

    int m = 0;
>>>>>>> 8b3c767f0da37eaabe51c9dda5ccf2629433e075:project/traghetti.cpp
    int tmp;
    vector<int>::iterator foo;

    if (!edges[i].size()) return &maxdepth[i];

    for (vector<int>::iterator it = edges[i].begin(); it != edges[i].end(); it++) {
        foo = find(edges[*it].begin(), edges[*it].end(), i);
        if (foo != edges[*it].end())
           edges[*it].erase(foo);
        m  = maxdfs(*it, maxdepth);
        if (maxdepth[i].size() < m->size())
            maxdepth[i] = *m;
    }

<<<<<<< HEAD:traghetti.cpp
    maxdepth[i].push_back(i);
    return &maxdepth[i];
=======
    maxdepth[i] = m + 1;
    return maxdepth[i];
    */
>>>>>>> 8b3c767f0da37eaabe51c9dda5ccf2629433e075:project/traghetti.cpp
}

vector<int> maxwalk()
{
  /*
    vector<int> nodes[n];
    size_t i;
    size_t startleaf;

    for (i=0; i != n; i++)
        if (edges[i].size() == 1) {
            edges[i].push_back(i);
            startleaf = i;
        }


    maxdfs(startleaf, nodes);

    vector<int> maxpath;
    for (size_t i=0; i!=n; i++)
        if (maxpath.size() < nodes[i].size())
            maxpath = nodes[i];

<<<<<<< HEAD:traghetti.cpp
    return maxpath;
=======
    return *max_element(nodes, nodes+n);
    */
>>>>>>> 8b3c767f0da37eaabe51c9dda5ccf2629433e075:project/traghetti.cpp
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

<<<<<<< HEAD:traghetti.cpp

    vector<int> v = maxwalk();

    for (vector<int>::iterator it = v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout << endl;
=======
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
>>>>>>> 8b3c767f0da37eaabe51c9dda5ccf2629433e075:project/traghetti.cpp

    return 0;
}

