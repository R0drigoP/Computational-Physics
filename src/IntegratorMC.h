#ifndef __IntegratorMC__
#define __IntegratorMC__

#include "Func1D.h"
#include "TF1.h"

using namespace std;

class IntegratorMC: public Func1D{

 public:
  IntegratorMC(double fx0, double fx1, TF1*fp);
  IntegratorMC(const IntegratorMC& MC);
  ~IntegratorMC(){;}
  
  // set function
  void SetIntegrandFunction(TF1*);

  // simple integration
  void IntegralMC(double xmin, double xmax, int& N,double& result, double& error);

  // importance sampling
  void IntegralMCIS(double xmin, double xmax,int& N,
		    double& result, double& error, TF1&pdf, TF1&x);

  // acceptance-rejection
  void IntegralMCAR(double xmin, double xmax,
		    int& N,double& result, double& error);

  // other methods(...)
 protected:
  double x0, x1; // integrand limits
};

#endif
