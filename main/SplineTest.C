#include "Spline3.h"
#include "TF1.h"

#include "TMath.h"
#include "TApplication.h"

#include <cmath>
#include <iostream>

int main(){

  double x[]={1.,2.,3.,4.,5.};
  double y[]={0.,1.,0.,1.,0.};
  TF1 *func=new TF1("f1","1",0,10);
  Spline3 test(5,x,y,nullptr);
  test.Interpolate(2.5);
  test.Interpolate(4);
  test.Interpolate(5);

  TApplication tapp("app", 0, 0);
  TCanvas* cc = new TCanvas("cc", "", 0, 0, 1000, 800);
  test.Draw();
  cc->Modified();
  cc->Update();
  tapp.Run();

}
