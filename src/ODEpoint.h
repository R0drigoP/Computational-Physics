#ifndef __ODEpoint__
#define __ODEpoint__

#include "TROOT.h"

#include <cstdio>

#include <stdexcept>
#include <iostream>
using namespace std;

class ODEpoint{
 private:
  unsigned int ndim; //nb of dependent variables
  double* x; //independent variable + dependent variables (ndim+1)

 public:
  //constructors and destructor
  ODEpoint(unsigned int fndim=0, const double* fx = nullptr);
  ODEpoint(const ODEpoint&);
  ~ODEpoint();

  //getters
  int GetNdim() const {return ndim;}
  double T() const {return x[0];}
  double X(int i) const {return x[i+1];}
  double* GetArray() {return x;}

  //operators
  ODEpoint operator*(double) const; //retornar referencia ??
  ODEpoint operator+(const ODEpoint&) const; //retornar referencia ??
  ODEpoint operator-(const ODEpoint&) const; //retornar referencia ??
  void operator=(const ODEpoint&);
  const double& operator[](int) const;
  double& operator[](int);

  //output
  void Print() const;
  friend ostream& operator<<(ostream&, const ODEpoint&);
};

#endif
