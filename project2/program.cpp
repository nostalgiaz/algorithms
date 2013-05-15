#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int night, moment, maxChanges;
bool **matrix;
string s;

int t(bool * s, bool v, int i, int c) {
  if(v==s[i])
    return t(s, v, i+1, c) + 1;

}

int main (void) {
  ifstream in("input.txt");
  in >> night >> moment >> maxChanges;

  matrix = new bool *[night];
  for(int i=0; i<night; i++)
    matrix[i] = new bool[moment];

  for(int i=0; i<night; i++) {
    in >> s;
    for(int j=0; j<s.size(); j++)
      matrix[i][j] = s[j] == 'H';
  }

  for(int i=0; i<night; i++) {
    for(int j=0; j<moment; j++)
      cout << matrix[i][j];
    cout << endl;
  }

  ifstream out("output.txt");
}
