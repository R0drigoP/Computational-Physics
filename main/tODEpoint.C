#include "ODEpoint.h"

int main(){
  int ndim = 1;
  double* x1 = new double[ndim+1];
  x1[0] = 1.;
  x1[1] = 2.5;
  
  double x2[ndim+1] = {0., 1.1};
  
  ODEpoint P1(1, x1);
  P1.Print();

  ODEpoint P2(P1);
  P2.Print();

  ODEpoint P3(ndim , x2);
  P3.Print();
  P3 = P2;
  P3.Print();

  P3 = P2*2;
  P3.Print();

  P3 = P2+P2;
  P3.Print();

  P3 = P2-P1;
  P3.Print();

  cout << "cout: " << P3 << endl;

  cout << P2[1] << endl;
  
  return 0;
}
