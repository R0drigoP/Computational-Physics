#include "Spline3.h"
#include "EqSolver.h"

#include <cstdio>
#include <cmath>

//Construtor
Spline3::Spline3(unsigned int N,const double *fx, const  double *fy,
		 const TF1* fF0):
  DataPoints(N,fx,fy),F0(nullptr),cInterpolator(nullptr),K_coef(N,0.){

  if(fF0) F0 = new TF1(*fF0);

  FInterpolator = new TF1("FInterpolator", this,
			  &Spline3::fInterpolator,
			  1.1*xmin, 0.9*xmax, 0);

  Vec mid(N-2, 0.), top(N-3, 0.), down(N-3, 0.), cons(N-2, 0.);


  for(int i=0; (i+2)<N ; ++i){

    if(i+2<N-1){
      down[i]=fx[i+1]-fx[i+2];
      top[i]=down[i];
    }

    mid[i]=(fx[i]-fx[i+2])*2;
    cons[i]=
      6*((fy[i]-y[i+1])/(fx[i]-fx[i+1])-(fy[i+1]-fy[i+2])/(fx[i+1]-fx[i+2]));

  }

  FCmatrixBanded band(down, mid, top);
  EqSolver Eq(band,cons);
  band.Print();
  cons.Print();
  Vec K(Eq.LUBandedSolver());
  //K.Print();

  //double k0=(6*( (y[0]-y[1])/(x[0]-x[1]) - (y[1]-y[2])/(x[1]-x[2]) ) -K[1]*(x[1]-x[2]) -2*K[0]*(x[2]-x[0]) ) / (x[0]-x[1]);
  // K_coef[0]=k0;

  for(int i=1;i<N-1;++i){
    K_coef[i]=K[i-1];
  }

  //K_coef.Print();

}

//copy constructor
Spline3::Spline3(const Spline3& Sp) :
  Spline3(Sp.N, Sp.x, Sp.y, Sp.F0) {;}

//destrutor
Spline3::~Spline3(){
  if(FInterpolator) delete FInterpolator;
  if(F0) delete F0;
  if(cInterpolator) delete cInterpolator;
}

double Spline3::Interpolate(double xval) const{

  unsigned int index, max=N-1, min=0;
  double result=0;
  if(N%2==0)
    index=(N/2)-1;
  else
    index=N/2;

  while(1){

    if(x[index]==xval){
    }
    else if(x[index]<xval){
      min=index;
      index=(max+index)/2;
    }
    else{
      max=index;
      index=(min+index)/2;
    }

    if(x[index]<=xval && xval<=x[index+1])
      break;

  }
  printf("Index->%d, Xi=%lf Xi+1=%lf\n",index, x[index],x[index+1]);
  //printf("Ki=%lf\n", K_coef[index]);


  result=K_coef[index]/6*
    (pow((xval-x[index+1]),3)/(x[index]-x[index+1])-(xval-x[index+1])*(x[index]-x[index+1]))-K_coef[index+1]/6*
    (pow((xval-x[index]),3)/(x[index]-x[index+1])-(xval-x[index])*(x[index]-x[index+1]))+(y[index]*(xval-x[index+1])-y[index+1]*(xval-x[index]))/(x[index]-x[index+1]);

  printf("Result=%lf\n",result);

  return result;
}

void Spline3::Draw() const{
  DataPoints::Draw();

  FInterpolator->SetLineColor(kRed);
  FInterpolator->SetLineWidth(2);
  FInterpolator->SetTitle("Spline3");
  FInterpolator->Draw("same");

  if(F0){
    F0->SetLineColor(kGreen);
    F0->SetLineWidth(2);
    F0->Draw("same");
  }

}

const TCanvas& Spline3::GetCanvas(){

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

void Spline3::SetFunction(const TF1* fF0){
  if (fF0){
    if(F0) delete F0;
    F0 = new TF1(*fF0);
  }
}

ostream& operator<<(ostream& s, const Spline3& Sp){
  s << "Nb points stored: " << Sp.N << endl;
  for(int i=0; i<Sp.N; ++i)
    s << fixed << setprecision(3)
      << "(" << Sp.x[i] << "," << Sp.y[i] << ") f(x) =  "
      << Sp.Interpolate(Sp.x[i]) << " ";
  s << endl;

  return s;
}

