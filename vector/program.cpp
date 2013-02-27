#include <fstream>

using namespace std;

int main () {
  int counter, sum=0, here, tmp;

  ifstream in("input.txt");
  in>>counter;
  
  for(int i=0; i<counter; i++) {
    in>>tmp;
    here=max(here + tmp, 0);
    sum=max(here, sum);
  }

  ofstream out("output.txt");
  out<<sum<<"\n";
  return 0;
}
