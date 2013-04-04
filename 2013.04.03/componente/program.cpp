#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > nodes;
vector<vector<int> > nodesTrans;
vector<bool> nodesBool;
stack<int> s;
int counter;

void dfs(int n) {
    nodesBool[n] = true;

    for (int i=0; i < nodes[n].size(); i++) {
        int tmp = nodes[n][i];
        if (!nodesBool[tmp])
            dfs(tmp);
    }

    s.push(n);
}


void dfsTrans(int n) {
    nodesBool[n] = true;
    counter++;

    for (int i=0; i < nodesTrans[n].size(); i++) {
        int tmp = nodesTrans[n][i];
        if (!nodesBool[tmp]) {
            dfsTrans(tmp);
        }
    }
}


int main() {
    int n, m, start, end, max_=0;

    ifstream in("input.txt");
    in >> n >> m;

    nodes.resize(n);
    nodesTrans.resize(n);
    nodesBool.resize(n);

    for (int i=0; i<m; i++) {
        in >> start >> end;
        nodes[start].push_back(end);
        nodesTrans[end].push_back(start);  // Grafo trasposto
    }

    for (int i=0; i<n; i++)
        nodesBool[i] = false;

    for (int i=0; i<n; i++) {
        if (!nodesBool[i]) {
            dfs(i);
        }
    }

    // resetto visitato
    for (int i=0; i<n; i++)
      nodesBool[i] = false;

    // Visito di nuovo, pero' trasposto
    while (!s.empty()) {
        int top = s.top();
        s.pop();

        counter = 0;

        if (!nodesBool[top]) {
            dfsTrans(top);

            max_ = max(counter, max_);
        }
    }

    ofstream out("output.txt");
    out << max_ << endl;

    return 0;
}
