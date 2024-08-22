#include "NewtonInterpolator.h"
#include <algorithm>
using namespace std;

NewtonInterpolator::NewtonInterpolator(unsigned int fN, const double* fx, const double* fy, const TF1* fF0) : DataPoints(fN, fx, fy), F0(nullptr), cInterpolator(nullptr) {
  if(fF0) F0 = new TF1(*fF0);
  
  FInterpolator = new TF1("FInterpolator", this, &NewtonInterpolator::fInterpolator, 0.9*xmin, 1.1*xmax, 0);
}

//copy constructor
NewtonInterpolator::NewtonInterpolator(const NewtonInterpolator& NI) :
  NewtonInterpolator(NI.N, NI.x, NI.y, NI.F0) {;}

//destructor
NewtonInterpolator::~NewtonInterpolator(){
  if(FInterpolator) delete FInterpolator;
  if(F0) delete F0;
  if(cInterpolator) delete cInterpolator;
}

//////////////////////////////////// interpolation methods

double NewtonInterpolator::Interpolate(double xval) const{
  double a[N]; //array of coefficients

  //copy array 'y' to array 'a'
  copy(y, y+N, a);

  //calc of coeffs
  for(int k=1; k<N; ++k){
    for(int i=k; i<N; ++i)
      a[i] = (a[i] - a[k-1])/(x[i] - x[k-1]);
  }

  double P = a[N-1];

  //cal of polinomial
  for(int k=1; k<N; ++k)
    P = a[N-1-k] + (xval - x[N-1-k])*P;

  return P;
}

void NewtonInterpolator::Draw() const{
  DataPoints::Draw();

  FInterpolator->SetLineColor(kRed);
  FInterpolator->SetLineWidth(2);
  FInterpolator->SetTitle("Newton");
  FInterpolator->Draw("same");

  if(F0){
    F0->SetLineColor(kGreen);
    F0->SetLineWidth(2);
    F0->Draw("same");
  }
}

const TCanvas& NewtonInterpolator::GetCanvas(){
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


//////////////////////////////////////// underlying unction
void NewtonInterpolator::SetFunction(const TF1* fF0){
  if (fF0){
    if(F0) delete F0;
    F0 = new TF1(*fF0);
  }
}

///////////////////////////// output
ostream& operator<<(ostream& s, const NewtonInterpolator& NI){
  s << "Nb points stored: " << NI.N << endl;
  for(int i=0; i<NI.N; ++i)
    s << fixed << setprecision(3)
      << "(" << NI.x[i] << "," << NI.y[i] << ") f(x) =  "
      << NI.Interpolate(NI.x[i]) << " ";
  s << endl;
  
  return s;
}


void NewtonInterpolator::Print(string FILE) {;}
