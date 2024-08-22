#include "Integrator.h"

#include <iomanip>
#include<iostream>
using namespace std;

int main(){
  TF1* f = new TF1("f", "exp(x)", 0, 10);
  Integrator I(0, 1, f);

  double integral = 0., error = 0.;
  I.TrapezoidalRule(100, integral, error);
  cout << "Integral: " << integral << endl;
  cout << "Error: " << error << endl;

  integral = 0.;
  error = 1e-3;
  unsigned int N = 10;
  I.Romberg(N, integral, error);
  cout << "Integral: " << integral << endl;
  cout << "Error: " << setprecision(7) << error << endl;

  return 0;
}
