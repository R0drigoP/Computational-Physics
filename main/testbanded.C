#include "FCmatrixBanded.h"
#include "Vec.h"
#include "EqSolver.h"

int main(){
  
  double a[]={1., 2., 3., 4., 5.};
  double b[]={12., 23., 13., 14., 11., 42.};
  double c[]={44., 23., 14., 33., 25.};
  Vec q(6,1);
  FCmatrixBanded mx(b,6,a,5,c,5);
  mx.Print();

  EqSolver Eq(mx,q);
  Vec result(Eq.LUBandedSolver());
  result.Print();
  
  //printf("Determinant::%lf\n",mx.Determinant());
  //mx.GetMid().Print();
  //mx.GetTop().Print();
  //mx.GetDown().Print();
  //FCmatrixBanded mx1(mx);
  //mx1.Print();
  //mx=mx*0;
  //mx.Print();
  //Vec col(mx.GetCol(4));
  //printf("%d\n",mx.GetColMax(4));
  //printf("%lf\n",col[mx.GetColMax(4)]);
 
  
 
  return 0;
}
