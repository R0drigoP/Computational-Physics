#include "LagrangeInterpolator.h"

//Construtor
LagrangeInterpolator::LagrangeInterpolator(unsigned int N,
					   const double *fx, const  double *fy, const TF1* fF0):
  DataPoints(N,fx,fy),F0(nullptr),cInterpolator(nullptr){
  
  if(fF0) F0 = new TF1(*fF0);
  
  FInterpolator = new TF1("FInterpolator", this,
			  &LagrangeInterpolator::fInterpolator,
			  0.9*xmin, 1.1*xmax, 0);
}

//copy constructor
LagrangeInterpolator::LagrangeInterpolator(const LagrangeInterpolator& LI) :
  LagrangeInterpolator(LI.N, LI.x, LI.y, LI.F0) {;}

//destrutor
LagrangeInterpolator::~LagrangeInterpolator(){
  if(FInterpolator) delete FInterpolator;
  if(F0) delete F0;
  if(cInterpolator) delete cInterpolator;
}

double LagrangeInterpolator::Interpolate(double xval) const{

  double result=0;
  
  for(int i=0;i<N;++i){
    double lx=1.;
    for(int j=0;j<N;++j){
      if(j!=i)
	lx*=(xval-x[j])/(x[i]-x[j]);
    }
    result+=y[i]*lx;
  }
  return result;
}

void LagrangeInterpolator::Draw() const{
  DataPoints::Draw();
  
  FInterpolator->SetLineColor(kRed);
  FInterpolator->SetLineWidth(2);
  FInterpolator->SetTitle("LagrangeInterpolator");
  FInterpolator->Draw("same");
  
  if(F0){
    F0->SetLineColor(kGreen);
    F0->SetLineWidth(2);
    F0->Draw("same");
  }
  
}

const TCanvas& LagrangeInterpolator::GetCanvas(){

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

void LagrangeInterpolator::SetFunction(const TF1* fF0){
  if (fF0){
    if(F0) delete F0;
    F0 = new TF1(*fF0);
  }
}

ostream& operator<<(ostream& s, const LagrangeInterpolator& LI){
  s << "Nb points stored: " << LI.N << endl;
  for(int i=0; i<LI.N; ++i)
    s << fixed << setprecision(3)
      << "(" << LI.x[i] << "," << LI.y[i] << ") f(x) =  "
      << LI.Interpolate(LI.x[i]) << " ";
  s << endl;

  return s;
}
