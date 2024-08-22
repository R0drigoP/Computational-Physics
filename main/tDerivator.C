#include "Derivator.h"

#include <cmath>
#include <iostream>
using namespace std;

int main(){
  TF1* f = new TF1("f", "exp(x)", 0, 10);
  Derivator D(f);

  double First_Derivative, Second_Derivative, d3, d4;
  First_Derivative = D.Derivative_1(0, 1e-2);
  Second_Derivative = D.Derivative_2(0, 1e-2);
  d3= D.Derivative_3(0, 1e-2);
  d4= D.Derivative_4(0, 1e-2);

  cout << "First Derivative: " << First_Derivative << endl;
  cout << "Second Derivative: " << Second_Derivative << endl;
  cout << "Third Derivative: " << d3 << endl;
  cout << "Fourth Derivative: " << d4 << endl;
  
  return 0;
}
