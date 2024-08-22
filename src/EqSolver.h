#ifndef __EqSolver__
#define __EqSolver__

#include "Vec.h"
#include "FCmatrix.h"
#include "FCmatrixAlgorithms.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"


class EqSolver{
 public:
  EqSolver();
  EqSolver(const FCmatrixFull&, const Vec&);
  EqSolver(const FCmatrixFull&); //entrar logo com a aumentada
  EqSolver(const FCmatrixBanded&, const Vec&);  

  //void SetMatrixBandend, etc.. can also be added.
  //In that case, we need to at a private member of the same type
  
  void SetMatrixFull(const FCmatrixFull&); 
  void SetConstants(const Vec&);

  Vec GaussEliminationSolver(int decomp=0, int flag=0);
  Vec LUdecompositionSolver(int decomp=0, int flag=0);
  Vec LUBandedSolver();


  void Print();
 private:
  FCmatrixFull Ab; //augmented matrix  //afinal acho que n é preciso
  FCmatrixFull A; //matrix of coeffs
  FCmatrixBanded Band;
  Vec b; //vector of constants
  
};

#endif

