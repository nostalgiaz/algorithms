#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int N, moments, C;
bool **matrix;
int ***Tmiddle;
string s;

int t(bool * s, bool v, int i, int c) {
  if (i == moments)
      return 0;

  if (v == s[i]) // tengo
      return t(s, v, i+1, c) + 1;
  else if (v != s[i] && c == 0) // ignoro
      return t(s, v, i+1, c);
  else if (v != s[i] && c > 0) // ignoro o cambio
      return max(
            t(s, v, i+1, c),
            t(s, !v, i+1, c-1) +1
      );
}


int** M;
int** T;

int m(void) {
    C++;

    M = new int*[2];
    M[0] = new int[C];
    M[1] = new int[C];

    copy(T[N-1], T[N-1]+C, M[0]);

    for (size_t i=1; i!=N; i++) {
        for (size_t c=0; c!=C; c++)
            for (size_t g=0; g<=c; g++)
                M[i%2][c] = max(M[i%2][c], M[(i-1)%2][g] + T[N-i-1][c-g]);
    }

    return max(*max_element(M[0], M[0]+C),
               *max_element(M[1], M[1]+C));
}



int main(int argc, char** argv) {
  ifstream in(argc > 1 ? argv[1] : "input.txt");
  in >> N >> moments >> C;

  matrix = new bool *[N];
  for(int i=0; i<N; i++)
    matrix[i] = new bool[moments];

  for(int i=0; i<N; i++) {
    in >> s;
    for(int j=0; j<s.size(); j++)
      matrix[i][j] = s[j] == 'H';
  }

  T = new int*[N];
  for (size_t i=0; i!=N; i++) T[i] = new int[C+1];

  for(size_t i=0; i<N; i++)
    T[i][0] = 0;

  for (size_t i=0; i != N; i++) {
      for (size_t c=1; c != C+1; c++) {
          T[i][c] = max(t(matrix[i], true, 0, c-1),
                        t(matrix[i], false, 0, c-1));
      }
  }
  cout << endl;
  cout << "### T ###" << endl;
  for (size_t i=0; i!=N; i++) {
      for (size_t j=0; j!=C+1; j++)
          cout << T[i][j] << ", ";
      cout << endl;
  }
  cout << m() << endl;
}
