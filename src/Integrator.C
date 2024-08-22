#include "Integrator.h"
#include "Derivator.h"

#include <cmath>
#include <vector>
#include <iostream>
using namespace std;

////////////////////////////Constructors
Integrator::Integrator(double fa, double fb, const TF1* fF) :
  a(fa), b(fb), Func1D(fF){;}

Integrator::Integrator(const Integrator& I) :
  Integrator(I.a, I.b, I.F) {;}

////////////////////////////Calculation of Integral
void Integrator::TrapezoidalRule(unsigned int n, double& integral, double& error) {
  // n = nmr de subintervalos
  double result = 0.;
  double h = (b-a)/n;
  //Func1D f(F);
  Derivator D(F);

  integral = 0.;
  error = 0.;

  if(a!=b){
    for(int i=0; i<n; ++i)
      integral += F->Eval(a+i*h) + F->Eval(a+(i+1)*h);
    integral *= h/2;

    for(int i=0; i<n; ++i)
      error += D.Derivative_2(a+i*h, h);
    error *= -h*h*(b-a)/12;
    error = fabs(error);
  }
  
}

void Integrator::SimpsonRule(unsigned int n, double& integral, double& erro){

  double h=(b-a)/n, sum1=0., sum2=0.;
  //Func1D f(F);
  Derivator D(F);
  integral=0;
  erro=0;
  
  if(a!=b && n%2==0){

    for(int i=1; i<=n/2 ;++i){
      if(i<=(n/2-1))
	sum2+=F->Eval(a+(2*i)*h);
      sum1+=F->Eval(a+(2*i-1)*h);
    }
    
    integral=h/3*(F->Eval(a)+F->Eval(b)+4*sum1+2*sum2);

    for(int i=0; i<=n/2; ++i)
      erro += D.Derivative_4(a+i*h, h);
    erro *= -h*h*h*h*h*(b-a)/90;
    erro = fabs(erro);
  }
  else if(a!=b && n%2!=0){

    for(int i=1; i<=(n-1)/2 ;++i){
      if(i<=((n-1)/2-1))
	sum2+=F->Eval(a+(2*i)*h);
      sum1+=F->Eval(a+(2*i-1)*h);
    }
    
    integral=h/3*(F->Eval(a)+F->Eval(b-h)+4*sum1+2*sum2)+h/12*(-F->Eval(b-2*h)+8*F->Eval(b-h)+5*F->Eval(b));

    for(int i=0; i<=n/2; ++i)
      erro += D.Derivative_4(a+i*h, h);
    erro *= -h*h*h*h*h*(b-a)/90;
    erro = fabs(erro);
  }
}

//Nmax -> max order allowed for romberg integration
void Integrator::Romberg(unsigned int& Nmax, double& integral, double& error){

  // check if N is va formula). In any case the new mlid or error
  bool bN = true;
  if (error >0.) {
    //Nmax=0;
    bN = false;
  }

  double h = b-a;
  vector<vector<double>> R; //romberg matrixx
  
  int i = 0;
  double terror = 1.1*error;
  
  //i -> row (i)
  //for loop using k;
  while ( (bN && i < Nmax) || (!bN && terror > error) ){
    int n = (int) ((b-a)/h);
    double T = 0.;
    for(int i=0; i<n; ++i)
      T += F->Eval(a+i*h) + F->Eval(a+(i+1)*h);
    T *= h/2;
    // v->linha atual = R[i]
    vector<double> row;
    row.push_back(T);
    
    for(int k=1; k<i+1; ++k){
      integral = row[k-1] +  (row[k-1] - R[i-1][k-1]) / (pow(4, k) - 1);
      row.push_back(integral);
      terror = fabs(integral-row[k-1]);
    }
    R.push_back(row);
    h /= 2;
    ++i;
  }

  //nb of slices = pow(2, i-1);
  Nmax = i;
  error = terror;
}

////////////////////////////Setters
void Integrator::SetBoundaries(double fa, double fb){
  a = fa;
  b = fb;
}
