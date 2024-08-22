#include "ODEsolver.h"

#include "TCanvas.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TROOT.h"

#include <stdexcept>
using namespace std;

////////////////////////////////constructors and destructors
ODEsolver::ODEsolver(const vector<TF1>& fF){
  F = fF;
}

ODEsolver::~ODEsolver(){
  F.clear();
  //points.clear();
}

////////////////////////////////setters
void ODEsolver::SetODEfunc(const vector<TF1>& fF){
  F = fF;
}

////////////////////////////////Taylor methods
vector<ODEpoint> ODEsolver::Euler(ODEpoint P0, double h, double Tmax){
  vector<ODEpoint> points;
  //points.clear(); //limpar, pois pode ter pontos doutros métodos
  points.push_back(P0);
  
  int ndim = P0.GetNdim();
  int Nsteps = 1 + int(Tmax/h);

  ODEpoint cPoint(P0); //current point
  ODEpoint next(P0); //next point

  for(int i=0; i<Nsteps; ++i){
    next[0] = cPoint.T() + h;
    for(int j=0; j<ndim; ++j)
      next[j+1] = cPoint[j+1] + h*F[j].EvalPar(cPoint.GetArray());
    points.push_back(next);
    //cout << points[i] << endl;
    cPoint = next;
  }
  return points;
}

//vector<ODEpoint> ODEsolver::Euler_Cromer(ODEpoint P0, double h, double Tmax)

vector<ODEpoint> ODEsolver::PredictorCorrector(ODEpoint P0, double h, double Tmax){
  vector<ODEpoint> points;
  //points.clear(); 
  points.push_back(P0);
  
  int ndim = P0.GetNdim();
  int Nsteps = 1 + int(Tmax/h);

  ODEpoint cPoint(P0); //current point
  ODEpoint next(P0); //next point

  for(int i=0; i<Nsteps; ++i){
    next[0] = cPoint.T() + h;
    for(int j=0; j<ndim; ++j){
      next[j+1] = cPoint[j+1] + h*F[j].EvalPar(cPoint.GetArray());
      next[j+1] = cPoint[j+1] + (h/2)*(F[j].EvalPar(cPoint.GetArray()) +
					F[j].EvalPar(next.GetArray()));
    }
    points.push_back(next);
    cPoint = next;
  }

  return points;
}

vector<ODEpoint> ODEsolver::LeapFrog(ODEpoint P0, double h, double Tmax){
  vector<ODEpoint> points;
  //points.clear(); //limpar, pois pode ter pontos doutros métodos
  points.push_back(P0);
  
  int ndim = P0.GetNdim();
  int Nsteps = 1 + int(Tmax/h);
  
  ODEpoint previous(P0); //previous point
  ODEpoint cPoint(P0); //current point
  ODEpoint next(P0); //next point

  //First iteration
  //could be in cicle, but needed if statement, and so it loses efficiency
  next[0] = cPoint.T() + h;
  for(int i=0; i<ndim; ++i)
    next[i+1] = cPoint[i+1] + h*F[i].EvalPar(cPoint.GetArray());
  points.push_back(next);
  cPoint = next;
  
  for(int i=1; i<Nsteps; ++i){
    next[0] = cPoint.T() + h;
    for(int j=0; j<ndim; ++j)
      next[j+1] = previous[j+1] + 2*h*F[j].EvalPar(cPoint.GetArray());
    points.push_back(next);
    //cout << points[i] << endl;
    previous = cPoint;
    cPoint = next;
  }
  return points;
}

////////////////////////////////Runge-Kutta methods
vector<ODEpoint> ODEsolver::RK2(ODEpoint P0, double h, double Tmax){
  vector<ODEpoint> points;
  //points.clear();
  points.push_back(P0);
  
  int ndim = P0.GetNdim();
  int Nsteps = 1 + int(Tmax/h);

  ODEpoint cPoint(P0); //current point
  ODEpoint mid(P0); //mid point
  ODEpoint next(P0); //next point

  for(int i=0; i<Nsteps; ++i){
    mid[0] = cPoint.T() + h/2;
    for(int k=0; k<ndim; ++k) //fill mid point (calc of K1 implicit);
      mid[k+1] = cPoint[k+1] + (h/2)*F[k].EvalPar(cPoint.GetArray());
    next[0] = cPoint.T() + h;
    for(int j=0; j<ndim; ++j){
      //double K1 = h*F[j].EvalPar(cPoint.GetArray()); Dont need to calc this
      double K2 = h*F[j].EvalPar(mid.GetArray());
      next[j+1] = cPoint[j+1] + K2;
    }
    points.push_back(next);
    //cout << points[i] << endl;
    cPoint = next;
  }
  return points;
}

vector<ODEpoint> ODEsolver::RK4(ODEpoint P0, double h, double Tmax){
  vector<ODEpoint> points;
  //points.clear();
  points.push_back(P0);
  
  int ndim = P0.GetNdim();
  int Nsteps = 1 + int(Tmax/h);
  
  ODEpoint cPoint(P0); //current point
  ODEpoint cPoint_cpy(P0); //copy of current point
  ODEpoint mid(P0); //mid point
  ODEpoint next(P0); //next point

  double K1[ndim];
  double K2[ndim];
  double K3[ndim];
  
  for(int i=0; i<Nsteps; ++i){
    cPoint_cpy[0] = cPoint.T() + h;
    next[0] = cPoint.T() + h;
    mid[0] = cPoint.T() + h/2;
    /*for(int k=0; k<ndim; ++k) //fill mid point
    mid[k+1] = cPoint[k+1] + (h/2)*F[k].EvalPar(cPoint.GetArray());*/
    
    //Calculation of K's (no need to store K4's in array, we can
    //just calculate one and use it right away, and then calculate next K4)

    // K1
    for(int k=0; k<ndim; ++k)
      K1[k] = h*F[k].EvalPar(cPoint.GetArray());

    ///K2
    for(int k=0; k<ndim; ++k)
      mid[k+1] = cPoint[k+1] + K1[k]/2;
    for(int k=0; k<ndim; ++k)
      K2[k] = h*F[k].EvalPar(mid.GetArray());

    ///K3
    for(int k=0; k<ndim; ++k)
      mid[k+1] = cPoint[k+1] + K2[k]/2;
    for(int k=0; k<ndim; ++k)
      K3[k] = h*F[k].EvalPar(mid.GetArray());

    ///K4 and aproximation (next point)
    for(int k=0; k<ndim; ++k)
      cPoint_cpy[k+1] += K3[k];
    for(int j=0; j<ndim; ++j){
      //double K1 = h*F[j].EvalPar(cPoint.GetArray());
      //double K4 = h*F[j].EvalPar(mid.GetArray());
      double K4 = h*F[j].EvalPar(cPoint_cpy.GetArray());
      next[j+1] = cPoint[j+1] + (K1[j] + 2*K2[j] + 2*K3[j] + K4) / 6;
    }
    points.push_back(next);
    //cout << points[i] << endl;
    cPoint = next;
    cPoint_cpy = cPoint;
  }
  return points;
}

////////////////////////////////Output
/*
void ODEsolver::Draw() const{
  //No futuro: se o vetor de resultados tiver vazio
  //resolver eq diferencial com RK4 por default
  //ou entao nem sequer desenhar!!
  if(points.size() == 0)
    throw invalid_argument(Form("[%s] Result vector empty...!\n", __PRETTY_FUNCTION__));
  
  int ndim = points[0].GetNdim();

  TCanvas* c = new TCanvas("c","c",800, 600);
  TMultiGraph* mGraph = new TMultiGraph();
  //TLegend* legend = new TLegend(0.1,0.7,0.48,0.9);
  //Eventualmente meter legenda mais bonita
  
  for(int i=0; i<ndim; ++i){
    TGraph* gGraph = new TGraph();
    int color = i+1;
    
    for(unsigned int j=0; j<points.size(); ++j)
      gGraph->SetPoint(gGraph->GetN(), points[j][0], points[j][i+1]);

    gGraph->SetTitle(F[i].GetTitle());
    
    gGraph->SetMarkerStyle(20);
    gGraph->SetMarkerSize(0.3);
    gGraph->SetMarkerColor(color);
    
    gGraph->SetLineWidth(1);
    gGraph->SetLineColor(color);
    
    mGraph->Add(gGraph);
  }
  
  mGraph->Draw("APL");
  c->Draw();
  c->BuildLegend();

  //c->WaitPrimitive();
  //delete c;
  //delete mGraph;
}
*/
