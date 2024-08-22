#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"

#include "TF1.h"

class Integrator: public Func1D{
 private:
  double a;
  double b;

 public:
  //constructors and destructor
  Integrator(double fa=0, double fb=0, const TF1* fF=nullptr);
  Integrator(const Integrator&); //copy constructor
  ~Integrator() {;}  
  
  //Calculation of Integrals
  void TrapezoidalRule(unsigned int, double&, double&); //(n, integral, error)
  void SimpsonRule(unsigned int, double&, double&); //(n, integral, error)
  void Romberg(unsigned int&, double&, double&); //(nmax, integral, error)
  //n->Number of sub-intervals

  //Setters
  void SetBoundaries(double, double);
};

#endif
