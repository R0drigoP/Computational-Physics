#include "Vec.h"
#include "FCmatrixAlgorithms.h"
#include "EqSolver.h"
#include <iostream>
using namespace std;

int main(){
  double vec[9] = {0., 1., 0., 3., 2., 4., 2., 3., 5.};
  FCmatrixFull Mx(vec, 3, 3);
  Mx.Print();
  int x = FCmatrixAlgorithms::LUdecomposition(Mx, 1);
  cout << x << endl;
  Mx.Print();

  cout << "===================================================" << endl;
  
  double vec1[12] = {0., 1., 0., 2.,  3., 2., 4., 1.,  2., 3., 5., 3.}; //3x3 | 3x1 (aumentada)
  FCmatrixFull Mx1(vec1, 3, 4);
  /*Mx1.Print();
  x = FCmatrixAlgorithms::LUdecomposition(Mx1, 1);
  cout << x << endl;
  Mx1.Print();
  */
  FCmatrixFull Mx3(Mx1);
  Mx3 = Mx;
  Mx3.Print();

  cout << Mx3*Mx1 << endl;
  
  Vec vv(12, vec1);
  cout << vv.size() << endl;
  cout << Mx1.GetColN() << endl;
  
  EqSolver S(Mx1);
  Vec result(3);
  result = S.LUdecompositionSolver(1, 1);
  cout << result << endl;
  
  FCmatrixFull Mx2(Mx1);
  double det_Mx2 = Mx2.Determinant();
  cout << det_Mx2 << endl;
  
  return 0;
}
