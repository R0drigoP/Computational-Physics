//equações do movimento: dz/dt = -v
//                       dv/dt = g - (k/m)*v 

#include "ODEsolver.h"

#include "TApplication.h"
#include "TGraph.h"

int main(){
  ////////////////////////////////
  // x[0] = t
  // x[1] = z(t)
  // x[2] = v(t)
  ////////////////////////////////

  const double g = 9.81;
  const double m = 80;
  const double k = 0.3;

  unsigned int ndim = 2; //nb of equations/dimensions
  double x[ndim+1] = {0., 8e3, 0};

  ODEpoint P0(ndim, x);
  double step = 1e-2;
  double Tmax = 1500.;

  auto f1 = [] (double* xval, double* par) {return -xval[2];};
  auto f2 = [g, m, k] (double* xval, double* par) {return g - (k/m)*xval[2];};

  vector<TF1> F{ //dar como nome as soluções
    TF1("z(t)", f1, 0., 1000., 0, 3),
    TF1("v(t)", f2, 0., 1000., 0, 3)
  };

  ODEsolver solver(F);

  vector<ODEpoint> vec = solver.RK4(P0, step, Tmax);

  TGraph* graph = new TGraph();
  for(int i=0; i<vec.size(); ++i)
    graph->SetPoint(graph->GetN(), vec[i][0], vec[i][2]);
  
  TApplication tapp("app", 0, 0);
  graph->Draw();
  tapp.Run();

  //v_terminal \approx 2600
  return 0;
}
