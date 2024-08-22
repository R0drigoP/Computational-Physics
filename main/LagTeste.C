#include "LagrangeInterpolator.h"

#include "TMath.h"
#include "TApplication.h"
#include "TFormula.h"
#include <cmath>
#include <iostream>

using namespace std;

int main(){

  auto f = [](double x) {return sin(TMath::TwoPi()*x) + exp(x);};
  
  int N=10;
  double vx[N], vy[N];
  double step = 1./N;
  for(int i=0; i<N; ++i){
    vx[i] = i*step;
    vy[i] = f(vx[i]);
  }


  LagrangeInterpolator LI(N, vx, vy, nullptr);
  TF1 *fa2 = new TF1("fa2","sin(TMath::TwoPi()*x) + exp(x)",0,10);   
  LI.SetFunction(fa2);
  TF1 inter(LI.GetInterpolationFunction());
  
  cout << LI << endl;

  TApplication tapp("app", 0, 0);
  TCanvas* cc = new TCanvas("cc", "", 0, 0, 1000, 800);
  LI.Draw();
  cc->Modified();
  cc->Update();
  tapp.Run();
			 
  return 0;
}
