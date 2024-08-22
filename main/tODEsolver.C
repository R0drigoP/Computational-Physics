#include "ODEsolver.h"

#include "TCanvas.h"
#include "TApplication.h"

#include <cmath>

int main(){
  ////////////////////////////////
  // x[0] = time
  // x[1] = theta
  // x[2] = omega
  ////////////////////////////////

  unsigned int ndim = 2; //nb of equations/dimensions
  double x[ndim+1] = {0., 1., -0.5};

  ODEpoint P0(ndim, x);
  double step = 1e-3;
  double Tmax = 20.;

  auto f1 = [] (double* xval, double* par) {return xval[2];};
  auto f2 = [] (double* xval, double* par) {return -sin(xval[1]);};

  vector<TF1> F{ //dar como nome as soluções
    TF1("theta(t)", f1, 0., 1000., 0, 3),
    TF1("omega(t)", f2, 0., 1000., 0, 3)
  };

  ODEsolver solver(F);

  //vector<ODEpoint> v_euler = solver.Euler(P0, step, Tmax);

  //vector<ODEpoint> v_PC = solver.PredictorCorrector(P0, step, Tmax);

  //vector<ODEpoint> v_LF = solver.LeapFrog(P0, step, Tmax);

  //vector<ODEpoint> v_RK2 = solver.RK2(P0, step, Tmax);

  vector<ODEpoint> v_RK4 = solver.RK4(P0, step, Tmax);
  
  TApplication tapp("app", 0, 0);
  //TCanvas* c = new TCanvas("c", "", 0, 0, 800, 600);
  solver.Draw();
  tapp.Run();
  
  return 0;
}
