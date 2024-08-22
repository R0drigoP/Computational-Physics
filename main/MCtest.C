#include "IntegratorMC.h"
#include "TF1.h"
#include "TMath.h"
#include <cstdio>

int main(){

  double xmin=0.2*TMath::Pi();
  double xmax=0.5*TMath::Pi();
  double result=0;
  double error=0;
  
  TF1 *func= new TF1("f1","cos(x)",xmin,xmax);
  TF1 *func1= new TF1("f2","1./2.",xmin,xmax);
  TF1 *func2= new TF1("f3","x",xmin,xmax);
  TF1 *pdf= new TF1("pdf","exp(-x)",xmin,xmax);

  IntegratorMC mc(xmin,xmax,func);

  printf("f(x)=cos(x)\n");
  mc.IntegralMC(xmin,xmax,10000,result,error);
  printf("Result=%lf\nErro=%lf\n\n",result,error);

  mc.SetIntegrandFunction(func1);
  printf("f(x)=1/2\n");
  mc.IntegralMC(xmin,xmax,10000,result,error);
  printf("Result=%lf\nErro=%lf\n\n",result,error);

  mc.SetIntegrandFunction(func2);
  printf("f(x)=x\n");
  mc.IntegralMC(xmin,xmax,10000,result,error);
  printf("Result=%lf\nErro=%lf\n\n",result,error);

  mc.SetIntegrandFunction(func);
  printf("f(x)=cos(x)\n");
  mc.IntegralMCIS(xmin,xmax,10000,result,error,*pdf,*pdf);
  printf("Result=%lf\nErro=%lf\n\n",result,error);


  mc.IntegralMCAR(xmin,xmax,100,result,error);
  printf("Result=%lf\nErro=%lf\n",result,error);
  


  return 0;
}
