#include "IntegratorMC.h"
#include "Func1D.h"
#include "TRandom3.h"
#include "cmath"
#include "TMath.h"

//construtores
IntegratorMC::IntegratorMC(double fx0, double fx1, TF1*fp):x0(fx0),x1(fx1),Func1D(fp){;}

IntegratorMC::IntegratorMC(const IntegratorMC& MC) :
  IntegratorMC(MC.x0, MC.x1, MC.F) {;}

//definir funcao integranda
void IntegratorMC::SetIntegrandFunction(TF1* func){
  this->F=func;
}


void IntegratorMC::IntegralMC(double xmin, double xmax,
			      int& N,double& result, double& error){
  //falta ifs para o xmin e xmax
  bool check=true;

  if(error>0){
    N=0;
    check=false;
  }

  double sum1=0.,sum2=0.;

  int count=0;
  double terror=1.1*error;
  gRandom->SetSeed(0);

  while(check && count<N || (!check && terror>error)){

    
    double y=gRandom->Uniform();
    double xi=xmin + (xmax-xmin)*y;
    sum2+=this->F->Eval(xi);
    sum1+=this->F->Eval(xi)*this->F->Eval(xi);
    
    //printf("%lf %lf\n",xi,this->F->Eval(xi));

    double fm=sum2/((double) (count+1));
    result=fm*(xmax-xmin);
    double Var=sum1/((double) (count+1))-fm*fm;
    if(count>0)
      terror=(xmax-xmin)/sqrt((double) (count+1))*sqrt(Var);
    
    ++count;
  }
  N=count;
  error=terror;
  //printf("N=%d Valor=%lf, Erro=%lf\n", N, result, error);

  
  /*result=0;
  error=0;
  gRandom->SetSeed(0);
  
  
  double fs=0;
  for(int i=0; i<N ;++i){
    double xi= xmin + (xmax-xmin)*gRandom->Uniform(0,1);
    result+=this->F->Eval(xi);
    fs+=this->F->Eval(xi)*this->F->Eval(xi);
  }

  double fm=result/((double) N);
  result=fm*(xmax-xmin);
  double Var=fs/((double) N)-fm*fm;
  error=(xmax-xmin)/sqrt((double) N)*sqrt(Var);
  */
}


void IntegratorMC::IntegralMCIS(double xmin, double xmax,int& N,
				double& result, double& error,
				TF1&pdf, TF1&x){

  //falta ifs para o xmin e xmax
  bool check=true;

  if(error>0){
    N=0;
    check=false;
  }

  double sum1=0.,sum2=0.;

  int count=0;
  double terror=1.1*error;
  gRandom->SetSeed(0);

  while(check && count<N || (!check && terror>error)){

    double y=gRandom->Uniform();
    double xi=x.Eval(y);
    double ratio=this->F->Eval(xi)/pdf.Eval(xi);
    sum1+=ratio;
    sum2+=ratio*ratio;


    double Var=sum2/((double) (count+1))-sum1*sum1/((double) (count+1))/((double) (count+1));
    
    if(count>0)
      terror=sqrt(Var)/((double) count+1);
    
    ++count;
  }
  
  N=count;
  error=terror;
  result=sum1/((double) N);
  //printf("N=%d Valor=%lf, Erro=%lf\n", N, result, error);

  
  /*result=0;
  error=0;
  gRandom->SetSeed(0);
  //falta ifs para o xmin e xmax
  
  double fs=0;
  for(int i=0; i<N ;++i){
    
    double xi=x.Eval(gRandom->Uniform());

    result+=this->F->Eval(xi)/pdf.Eval(xi);

    fs+=this->F->Eval(xi)*this->F->Eval(xi)/(pdf.Eval(xi)*pdf.Eval(xi));
    
  }

  double fm=result/((double) N);
  result=fm;
  double Var=fs/((double) N)-fm*fm;
  error=(xmax-xmin)/sqrt((double) N)*sqrt(Var);
  */
}


void IntegratorMC::IntegralMCAR(double xmin, double xmax,
				int& N,double& result, double& error){
  result=0;
  error=0;
  gRandom->SetSeed(0);
  //falta ifs para o xmin e xmax
  
  double fmax=this->F->TF1::GetMaximum(xmin,xmax,1.E-10);

  //falat fazer o rand como deve ser
  TRandom3 x;

  int count=0;
  double xr,fr;
  for(int i=0;i<N;++i){
    xr=xmin+(xmax-xmin)*gRandom->Uniform();
    fr=fmax*x.Rndm();
    if(fr<=this->F->Eval(xr)){
      ++count;
    }
  }

  result=(xmax-xmin)*fmax*count/((double)N);
  error=(xmax-xmin)*fmax*sqrt(count*(1-((double)count)/((double)N)))/((double)N);
}
