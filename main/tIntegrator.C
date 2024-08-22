#include "Integrator.h"

#include <iomanip>
#include <iostream>
using namespace std;

int main(){
  TF1* f = new TF1("f", "cos(x)", 0, 10);
  Integrator I(0, 1, f);
  
  double integral, error;
  I.TrapezoidalRule(10000, integral, error);
  cout << "Integral: " << setprecision(7) << integral << endl;
  cout << "Error: " << setprecision(7) << error << endl;

  I.SimpsonRule(10000, integral, error);
  cout << "Integral_Simpson: " << setprecision(7) << integral << endl;
  cout << "Error_Simpson: " << setprecision(7) << error << endl;
  
  return 0;
}
