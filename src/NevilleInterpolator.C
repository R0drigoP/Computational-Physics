#include "NevilleInterpolator.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <iostream>

using namespace std;

//constructor
NevilleInterpolator::NevilleInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) : DataPoints(fN, fx, fy), F0(nullptr), cInterpolator(nullptr){
  if(fF0) F0 = new TF1(*fF0);
  
  FInterpolator = new TF1("FInterpolator", this, &NevilleInterpolator::fInterpolator, 0.9*xmin, 1.1*xmax, 0);
}

//destructor
NevilleInterpolator::~NevilleInterpolator(){
  if(FInterpolator) delete FInterpolator;
  if(F0) delete F0;
  if(cInterpolator) delete cInterpolator;
}

//copy constructor
NevilleInterpolator::NevilleInterpolator(const NevilleInterpolator& NI) :
  NevilleInterpolator(NI.N, NI.x, NI.y, NI.F0) {;}

////////////////////////////////////// interpolation methods

double NevilleInterpolator::Interpolate(double xval) const{
  double *yp = new double[N];
  for(int i=0; i<N; ++i)
    yp[i] = y[i]; //auxiliar vector

  for(int k=1; k<N; ++k){ //use extreme x-values
    for(int i=0; i<N-k; ++i)
      yp[i] = ( (xval-x[i+k])*yp[i] - (xval-x[i])*yp[i+1] ) / (x[i]-x[i+k]);

  }

  double A = yp[0];
  delete [] yp;
  return A;
}

void NevilleInterpolator::Draw() const{
  DataPoints::Draw();
  
  FInterpolator->SetLineColor(kRed);
  FInterpolator->SetLineWidth(2);
  //FInterpolator->SetTitle("Neville");
  FInterpolator->Draw("same");

  if(F0){
    F0->SetLineColor(kGreen);
    F0->SetLineWidth(2);
    F0->Draw("same");
  }
}

const TCanvas& NevilleInterpolator::GetCanvas(){
  if(cInterpolator)
    delete cInterpolator;
  cInterpolator = new TCanvas("cInterpolator", "", 0, 0, 800, 600);

  DataPoints::Draw();
  FInterpolator->SetLineColor(kRed);
  FInterpolator->SetLineWidth(2);
  FInterpolator->Draw("same");
  if(F0){
    F0->SetLineColor(kGreen);
    F0->SetLineWidth(2);
    F0->Draw("same");
  }

  return *cInterpolator;
}

///////////////////////////// underlying function
void NevilleInterpolator::SetFunction(const TF1* fF0){
  if (fF0){
    if(F0) delete F0;
    F0 = new TF1(*fF0);
  }
}

///////////////////////////// output
ostream& operator<<(ostream& s, const NevilleInterpolator& NI){
  s << "Nb points stored: " << NI.N << endl;
  for(int i=0; i<NI.N; ++i)
    s << fixed << setprecision(3)
      << "(" << NI.x[i] << "," << NI.y[i] << ") f(x) =  "
      << NI.Interpolate(NI.x[i]) << " ";
  s << endl;

  return s;
}

void NevilleInterpolator::Print(string FILE){;}
