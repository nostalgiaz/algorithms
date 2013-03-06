#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int INPUT_SIZE = 1000000;

int partition(int* v, int p, int r)
{
  int pivot = v[r];

  while (p < r)
  {
    while (v[p] < pivot)
      p++;
      while (v[r] > pivot)
        r--;
        if (v[p] == v[r])
            p++;
        else if (p < r)
        {
          int tmp = v[p];
          v[p] = v[r];
          v[r] = tmp;
        }
  }
  return r;
}

void quicksort(int* v, int p, int r)
{
  if (p<r)
  {
    int j = partition(v, p, r);
    quicksort(v, p, j-1);
    quicksort(v, j+1, r);
  }
}

int main()
{
  int n, tmp;
  int v[INPUT_SIZE];

  ifstream in("input.txt");
  in >> n;

  for(int i=0; i<n; i++)
    in >> v[i];

  quicksort(v, 0, n-1);

  ofstream out("output.txt");

  for(int i=0; i<n; i++)
    out << v[i] << " ";

   return 0;
}
