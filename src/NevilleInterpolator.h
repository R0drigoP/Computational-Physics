#ifndef __NevilleInterpolator__
#define __NevilleInterpolator__

#include "DataPoints.h"
#include "TF1.h"
#include "TCanvas.h"

class NevilleInterpolator: public DataPoints{
 private:
  double fInterpolator(double* fx, double* par) {return Interpolate(fx[0]);}
  TF1* FInterpolator; //interpolation function
  TF1* F0; //eventual underlying function
  TCanvas* cInterpolator; //includes data points and curve
  
 public:
  //constructor
  NevilleInterpolator(unsigned int fN=0, const double* fx=nullptr, const double* fy=nullptr, const TF1* fF0=nullptr);

  //copy constructor
  NevilleInterpolator(const NevilleInterpolator&);

  //destructor
  ~NevilleInterpolator();

  //Interpolation methods
  double Interpolate(double) const;
  const TF1& GetInterpolationFunction() const {return *FInterpolator;}
  void SetResolution(int n = 300) const {FInterpolator->SetNpx(n);}
  void Draw() const; //draw everything (points and interpolation function)
  const TCanvas& GetCanvas();

  //underlying function
  void SetFunction(const TF1*);
  
  //output
  friend ostream& operator<<(ostream&, const NevilleInterpolator&);
  void Print(string FILE=""); // print results
  
};


#endif
