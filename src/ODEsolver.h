#ifndef __ODEsolver__
#define __ODEsolver__

#include "TF1.h"
#include "TGraph.h"

#include "ODEpoint.h"

#include <vector>
#include <iostream>
using namespace std;

class ODEsolver{
 private:
  vector<TF1> F;
  //vector<ODEpoint> points; //guardar valores num vetor para dps desenhar graphs
  //TGraph* gGraph;

 public:
  //constructors and destructor
  ODEsolver() {;}
  ODEsolver(const vector<TF1>&);
  ~ODEsolver();

  //setters
  void SetODEfunc(const vector<TF1>&);

  //inicial point, step, time limit
  //Taylor methdos
  vector<ODEpoint> Euler(ODEpoint, double, double);
  vector<ODEpoint> Euler_Cromer(ODEpoint, double, double); // ?? Falta este 
  vector<ODEpoint> PredictorCorrector(ODEpoint, double, double);
  vector<ODEpoint> LeapFrog(ODEpoint, double, double);

  //Runge-Kutta methods
  vector<ODEpoint> RK2(ODEpoint, double, double);
  vector<ODEpoint> RK4(ODEpoint, double, double);
  vector<ODEpoint> RK4_AS(ODEpoint, double, double); //

  //Output
  void Draw() const;
};

#endif
