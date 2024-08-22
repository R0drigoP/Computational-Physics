#ifndef __Spline3__
#define __Spline3__

#include "DataPoints.h"
#include "TF1.h"
#include "TCanvas.h"
#include "Vec.h"
#include "FCmatrixBanded.h"

class Spline3: public DataPoints{

 private:
  double fInterpolator(double *fx, double *par) {return Interpolate(fx[0]);}
  TF1* FInterpolator; //interpolation function
  TF1* F0; //eventual underlying function
  TCanvas* cInterpolator; //includes data points and curve
  Vec K_coef;

 public:

  Spline3(unsigned int N=0,const double *fx=nullptr,const double *fy=nullptr,
	  const TF1* fF0=nullptr);
  Spline3(const Spline3&);
  ~Spline3();


  //Interpolation methods
  double Interpolate(double x) const;
  void Draw() const; //draw everything (points and interpolation function)
  const TF1& GetInterpolationFunction() const {return *FInterpolator;};
  const TCanvas& GetCanvas();

  void SetFunction(const TF1*);//underlying function

  //output
  friend ostream& operator<<(ostream&, const Spline3&);

};



#endif
