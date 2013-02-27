#include <fstream>

using namespace std;

int main()
{
    int r, c, sum=0, sumTmp=0;

    ifstream in("input.txt");
    in >> r >> c;

    int** matrix = new int*[r];

    for (int i=0; i<r; i++)
          matrix[i] = new int[c];

    for(int i=0; i<r; i++)
        for(int j=0; j<c; j++)
            in >> matrix[i][j];

    int *columnSum = new int[c];
    for(int z=0; z<r; z++)
    {
        for(int i=0; i<c; i++)
            columnSum[i] = 0;

        for(int x=z; x<r; x++)
        {
            int here=0;
            for(int i=0; i<c; i++)
            {
                columnSum[i] += matrix[x][i];
                here = max(here + columnSum[i], 0);
                sumTmp = max(here, sumTmp);
            }
            sum = max(sumTmp, sum);
        }
    }
    ofstream out("output.txt");
    out << sum << "\n";
    return 0;
}
