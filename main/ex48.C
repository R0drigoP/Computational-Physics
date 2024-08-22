#include "Vec.h"
#include "FCtools.h"

int main(){

  //Constructors and operators
  
  Vec v1(10);
  Vec v2(10, 5.);

  double a[]={1.2, 3.0, 5.4, 5.2, 1.};
  Vec v3(5, a);
  Vec v4(v3);

  
  Vec v5(5);
  v5 = v3 + v4;
  cout << v5 << endl;
  v5 = v3 - v4;
  cout << v5 << endl;
  v5 = v3*v3;
  cout << v5 << endl;
  v5 = v3*2;
  cout << v5 << endl;

  cout << v1 << endl << v2 << endl << v3 << endl << v4 << endl;
  cout << "---------------------------------" << endl;
  double cm[][5] = {
    {1., 7., 5., 3., -3.},
    {5., 2., 8., -2., 4.},
    {1., -5., -4., 6., 7.6},
    {0., -5., 3., +3.2, 3.3},
    {1., 7., 2., 2.1, 1.2}
  };

  //-----------------Set Entries e leitura de matriz

  Vec cv[5];
  
  for(int i=0; i<5; ++i){
    cv[i].SetEntries(5, a);
    cout << cv[i] << endl;
  }

  int n = 5;
  Vec* cvp = FCtools::ReadFile2Vecp("matrix.txt", n);
  for(int i=0; i<n; ++i)
    cout << cvp[i] << endl;

  //-------------------
  
  return 0;
}
