#include "Func1D.h"

#include "TCanvas.h"
#include "TApplication.h"

#include <iostream>
using namespace std;

int main(){
  TF1 *f = new TF1("fa2","sin(TMath::TwoPi()*x) + exp(x)",0,1);
  Func1D function(f);

  double x = function.Evaluate(1);
  cout << x << endl;
  
  TApplication tapp("app", 0, 0);                                              
  TCanvas* cc = new TCanvas("cc", "", 0, 0, 1000, 800);
  function.Draw();
  cc->Modified();
  cc->Update();
  tapp.Run();
  
  return 0;
}
