#include "DataPoints.h"

#include <stdexcept>
#include <algorithm>
#include <iomanip>

#include "TROOT.h"
#include "TAxis.h"

using namespace std;

DataPoints::DataPoints() : N(0), x(nullptr), y(nullptr), gPoints(nullptr) {;}

DataPoints::DataPoints(unsigned int fN, const double* fx, const double* fy) :
  N(fN),
  x(new double[N]),
  y(new double[N]) {
  if(!fx || !fy)
    throw invalid_argument(Form("[%s] null arrays!!", __PRETTY_FUNCTION__));

  //copy arrays
  copy(fx, fx+N, x);
  copy(fy, fy+N, y);

  //Retrieve min and max values
  SetMinMaxX();
  SetMinMaxY();

  //create graph
  gPoints = new TGraph(N, x, y);
  gPoints->SetMarkerStyle(20);
  gPoints->SetMarkerColor(kBlue);
  gPoints->SetMarkerSize(1);

  gPoints->GetXaxis()->SetRangeUser(0.9*xmin, 1.1*xmax);
  gPoints->GetYaxis()->SetRangeUser(0.9*ymin, 1.1*ymax);
}

DataPoints::~DataPoints(){
  if (x) delete [] x;
  if (y) delete [] y;
  if (gPoints) delete gPoints;
}

void DataPoints::Draw() const{
  gPoints->Draw("AP");
}

const TGraph& DataPoints::GetGraph() const{
  return *gPoints;
}

void DataPoints::SetMinMaxX(){
  auto it = minmax_element(x, x+N);
  xmin = *it.first;
  xmax = *it.second;
}

void DataPoints::SetMinMaxY(){
  auto it = minmax_element(y, y+N);
  ymin = *it.first;
  ymax = *it.second;
}

void DataPoints::Print(string FILE){;}

ostream& operator<<(ostream& s, const DataPoints& D){
  s << "Nb points stored: " << D.N << endl;
  for(int i=0; i<D.N; ++i)
    s << fixed << setprecision(3)
      << "(" << D.x[i] << "," << D.y[i] << ")";
  s << endl;
  
  return s;
}
