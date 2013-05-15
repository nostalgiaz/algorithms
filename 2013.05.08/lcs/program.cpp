#include <iostream>
#include <fstream>

using namespace std;

string s1, s2;

int lcs(int n1, int n2) {
  int ** matrix = new int * [n1 + 1];
  for(int i=0; i<n1 + 1; i++)
    matrix[i] = new int[n2 + 1];

  for(int i=0; i<n1+1; i++)
    matrix[i][0] = 0;

  for(int j=0; j<n2+1; j++)
    matrix[0][j] = 0;

  for(int i=1; i<n1+1; i++)
    for(int j=1; j<n2+1; j++)
      if(s1[i-1] == s2[j-1])
          matrix[i][j] = matrix[i-1][j-1] + 1;
      else matrix[i][j] = max(matrix[i][j-1], matrix[i-1][j]);

  return matrix[n1][n2];
}

int main () {
  ifstream in ("input.txt");
  ofstream out ("output.txt");

  in >> s1 >> s2;
  out << lcs(s1.size(), s2.size());

  return 0;
}
