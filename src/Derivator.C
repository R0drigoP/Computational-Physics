#include "Derivator.h"

#include "TROOT.h"

#include <stdexcept>

/////////////////////////////////////////////// Constructors and destructor
Derivator::Derivator(const TF1* fF) : Func1D(fF) {;}

Derivator::Derivator(const TF1& fF) : Func1D(fF) {;} //Isto ou dar referência??

Derivator::~Derivator(){;}

/////////////////////////////////////////////// Calc of Derivatives
double Derivator::Derivative_1(double xval, double h) const{
  if(!F)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));
  
  return ((F->Eval(xval-2*h) - 8*F->Eval(xval-h)) - (-8*F->Eval(xval+h) + F->Eval(xval+2*h)))/(12*h);
}

double Derivator::Derivative_2(double xval, double h) const{
  if(!F)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));
  
  return (-F->Eval(xval-2*h) + 16*F->Eval(xval-h) - 30*F->Eval(xval) + 16*F->Eval(xval+h) - F->Eval(xval+2*h))/(12*h*h);
}

double Derivator::Derivative_3(double xval, double h) const{
  if(!F)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));
  
  return ((F->Eval(xval+2*h) + 2*F->Eval(xval-h)) - (2*F->Eval(xval+h) + F->Eval(xval-2*h)))*3*2/(12*h*h*h);
}

double Derivator::Derivative_4(double xval, double h) const{
  if(!F)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));
  
  return ((F->Eval(xval+2*h) + F->Eval(xval-2*h)) - 4*(F->Eval(xval+h) + F->Eval(xval-h))+6*F->Eval(xval))/(h*h*h*h);
}
