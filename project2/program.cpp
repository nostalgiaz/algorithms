#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int night, moment, maxChanges;
bool **matrix;
string tmp;

int main (void) {
  ifstream in("input.txt");
  in >> night >> moment >> maxChanges;

  matrix = new bool *[night];
  for(int i=0; i<night; i++)
    matrix[i] = new bool[moment];

  for(int i=0; i<night; i++) {
    in >> tmp;
    for(int j=0; j<tmp.size(); j++)
      matrix[i][j] = tmp[j] == 'H';
  }

  for(int i=0; i<night; i++) {
    for(int j=0; j<moment; j++)
      cout << matrix[i][j];
    cout << endl;
  }

  ifstream out("output.txt");
}
