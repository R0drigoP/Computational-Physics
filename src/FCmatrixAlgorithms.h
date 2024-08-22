#ifndef __FCmatrixAlgorithms__
#define __FCmatrixAlgorithms__

#include "FCmatrixFull.h"

class FCmatrixAlgorithms{
 public:
  //static void GaussElimination(FCmatrix&, Vec& = nullptr);
  //static void LUdecomposition(FCmatrix&, vector<int>);
  
  static int  GaussElimination(FCmatrixFull& , int flag=0);
  static int LUdecomposition(FCmatrixFull&, int flag=0);
};

#endif
