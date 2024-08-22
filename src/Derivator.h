#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"
using namespace std;

class Derivator: public Func1D{
 public:
  ///Constructor and destructor
  Derivator(const TF1* fF = nullptr);
  Derivator(const TF1&);
  ~Derivator();

  ///Calculation of Derivatives
  double Derivative_1(double, double h=1e-7) const; // O(h^4)
  double Derivative_2(double, double h=1e-7) const; // O(h^4)
  double Derivative_3(double, double h=1e-7) const; // O(h^)
  double Derivative_4(double, double h=1e-7) const; // O(h^)
};

#endif
