#ifndef __DataPoints__
#define __DataPoints__

#include <string>
#include <iostream>
#include "TGraph.h"

using namespace std;

class DataPoints{
 protected:
  int N; //number of data points
  double *x, *y; //arrays
  TGraph* gPoints;
  double xmin, xmax;
  double ymin, ymax;

  void SetMinMaxX();
  void SetMinMaxY();
  
 public:
  //Constructors
  DataPoints();
  DataPoints(unsigned int, const double*, const double*);
  //Destructor
  virtual ~DataPoints();

  const TGraph& GetGraph() const;
  virtual double Interpolate(double) const {return 0.;}
  virtual void Draw() const;
  virtual void Print(string FILE="");

  friend ostream& operator<<(ostream&, const DataPoints&);
};

#endif
