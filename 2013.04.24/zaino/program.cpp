#include <iostream>
#include <fstream>
#define C 100001
#define N 1000

using namespace std;

int p [N];
int v [N];
int matrix[2][C];
int n, c;

int zaino() {
  for(int i=0; i<=c; i++)
    matrix[0][i] = 0;

  for(int i=1; i<=n; i++) {
    int currStep = i % 2;
    int prevStep = 1 - currStep;

    matrix[currStep][0] = 0;

    for(int j=1; j<=c; j++) {
      if(p[n-i] > j)
        matrix[currStep][j] = matrix[prevStep][j];
      else {
        matrix[currStep][j] = max(
            matrix[prevStep][j],
            matrix[prevStep][j-p[n-i]] + v[n-i]
            );
      }
    }
  }

  return matrix[n % 2][c];
}

int main (void) {
  int a, b;

  ifstream in("input.txt");
  ofstream out("output.txt");

  in >> c >> n;

  for(int i=0; i<n; i++) {
    in >> a >> b;
    p[i] = a;
    v[i] = b;
  }

  out << zaino();
}
