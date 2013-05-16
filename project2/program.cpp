#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

int N, moments, C;
bool **matrix;
string s;

int** M;
int** T;


void t(size_t s_i) {
    bool* s = matrix[s_i];
    size_t c;

    int** TT[2] ;
    TT[0] = new int*[C];
    TT[1] = new int*[C];
    for (c=0; c!=C; c++) {
        TT[0][c] = new int[moments];
        TT[1][c] = new int[moments];
    }


    for (c=0; c!=C; c++) {
        TT[0][c][moments-1] = s[moments-1] == 0;
        TT[1][c][moments-1] = s[moments-1] == 1;

        for (int i=moments-2; i>=0; i--)
            for (size_t mask=0; mask!=2; mask++)
                if (mask == s[i])
                    TT[mask][c][i] = TT[mask][c][i+1] + 1;
                else if (c == 0)
                    TT[mask][c][i] = TT[mask][c][i+1];
                else
                    TT[mask][c][i] = max(TT[mask][c][i+1],
                                         TT[1-mask][c-1][i+1]+1);
    }

    for (c=0; c!=C; c++)
        T[s_i][c+1] = max(TT[0][c][0], TT[1][c][0]);
}


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

  for (size_t i=0; i != N; i++) t(i);

  cout << endl;
  cout << "### T ###" << endl;
  for (size_t i=0; i!=N; i++) {
      for (size_t j=0; j!=C+1; j++)
          cout << T[i][j] << ", ";
      cout << endl;
  }
  cout << m() << endl;
}
