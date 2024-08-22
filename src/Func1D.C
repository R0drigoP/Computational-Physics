#include "Func1D.h"

////////////////////////////constructor and destructor
Func1D::Func1D(const TF1* fF) : F(nullptr){
  if(fF) F = new TF1(*fF);
}

Func1D::Func1D(const TF1& fF) : Func1D(&fF) {;}

Func1D::~Func1D(){
  if(F) delete F;
}

/////////////////////////// Function methods
void Func1D::SetFunction(const TF1* fF){
  if(fF){
    if(F) delete F;
    F = new TF1(*fF);
  }
}

double Func1D::Eval(double xval) const{
  return F->Eval(xval);
}

////////////////////////// output
void Func1D::Draw() const{
  F->SetLineColor(kRed);
  F->SetLineWidth(2);
  F->SetTitle("Function");
  F->Draw();
}
		
