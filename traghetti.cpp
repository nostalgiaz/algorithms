#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int n, m;
vector<int>* edges;


vector<int>* maxdfs(int i, vector<int>* maxdepth)
{
    vector<int>* m;
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

    maxdepth[i].push_back(i);
    return &maxdepth[i];
}

vector<int> maxwalk()
{
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

    return maxpath;
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


    vector<int> v = maxwalk();

    for (vector<int>::iterator it = v.begin(); it!=v.end(); it++)
        cout << *it << " ";
    cout << endl;

    return 0;
}

