#include "EqSolver.h"
#include "FCmatrixAlgorithms.h"
#include "FCmatrix.h"
#include "FCmatrixFull.h"

EqSolver::EqSolver() {;}

EqSolver::EqSolver(const FCmatrixBanded& matrix, const Vec& v){
  Band=matrix;
  b=v;
}


EqSolver::EqSolver(const FCmatrixFull& matrix, const Vec& v){
  A = matrix;
  b = v;
  int n=matrix.GetRowN();
  int j=matrix.GetColN();
  vector<Vec> aux1(n);
  Vec aux3(n,0.);
  for(int i=0; i<n; ++i){
    aux1[i]=aux3;
  }
  
  for(int i=0; i<n ; ++i){
    for(int k=0; k<j-1; ++k){
      
      Vec aux=matrix.GetRow(i);
      aux1[i][k] = aux[k];
      aux1[i][j-1] =0;
      
    }
    }
  FCmatrixFull a(aux1);
  Ab=a;
}


//construtor com a matriz aumentada
EqSolver::EqSolver(const FCmatrixFull& matrix){
  Ab = matrix;
  int n = Ab.GetRowN();
 
  vector<Vec> aux0(n);
  
  b=Ab.GetCol(n);
  
  
  for(int i=0; i<n ;i++){
    Vec aux1(n);
    Vec aux2(Ab.GetRow(i));
    for(int j=0; j<n ;j++){
      aux1[j]=aux2[j];
    } 
    aux0[i]=aux1;
  }

  FCmatrixFull a(aux0);
  A=a;
}

void EqSolver::SetMatrixFull(const FCmatrixFull& matrix){

  A=matrix;
  
}

void EqSolver::SetConstants(const Vec& v){
  b = v;
             
} 

Vec EqSolver::GaussEliminationSolver(int decomp, int flag){

  Vec x(Ab.GetRowN(),0.);  
  if(decomp!=0)
    FCmatrixAlgorithms::GaussElimination(Ab,flag);
    
    
  for(int i=Ab.GetRowN()-1; i>=0; --i){
      
    double sum=0;

    for(int j=i+1; j<Ab.GetRowN() ; ++j){

      sum+=x[j]*Ab[i][j];
	
    }
    Ab.Print();
    x[i]=(Ab[i][Ab.GetColN()-1]-sum)/Ab[i][i];

  }

  
  return x;
}

Vec EqSolver::LUdecompositionSolver(int decomp, int flag){
  if(decomp != 0)
    FCmatrixAlgorithms::LUdecomposition(Ab, flag);
  
  int n = Ab.GetRowN();
  Vec vb(n);
  vb = Ab.GetCol(n);
  Vec y(n, 0.);
  Vec x(n);
  //resolver sistema Ly = Pb
  for(int i=0; i<n; ++i){
    double sum = vb[i];
    for(int j=0; j<i; ++j){
      sum -= Ab[i][j]*y[j];
    }
    y[i] = sum;
  }

  //Resolver Ux = y
  for(int i=n-1; i>=0; --i){
    double sum = y[i];
    for(int j=i+1; j<n; ++j)
      sum -= Ab[i][j]*x[j];
    sum /= Ab[i][i];
    x[i] = sum;
  }
  
  return x;
}

Vec EqSolver::LUBandedSolver(){

  Vec y(Band.GetRowN(),b[0]);
  Vec aux0(Band.GetLdown());

  for(int i=1; i< Band.GetRowN(); ++i){
    
    y[i]=b[i]-aux0[i-1]*y[i-1];
    
  }

  Vec aux1(Band.GetUmid());
  Vec aux2(Band.GetUtop());
  Vec x(Band.GetRowN(), y[Band.GetRowN()-1]/aux1[Band.GetRowN()-1]);
  
  for(int i=Band.GetRowN()-2; i>=0; --i){
       
    x[i]=(y[i]-aux2[i]*x[i+1])/aux1[i];
    
 }
 
  return x;
}
