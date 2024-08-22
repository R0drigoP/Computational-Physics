#include "FCmatrixAlgorithms.h"
#include <cstdio>
#include <stdexcept>
#include <vector>
#include <iostream>
#include <cmath>
#include <cstdio>
#include "TROOT.h"
using namespace std;

int FCmatrixAlgorithms::LUdecomposition(FCmatrixFull& mx, int flag){

  int count = 0; //contador de troca de linhas, para calculo de determinante
  
  if(mx.GetRowN() != mx.GetColN() && mx.GetRowN() != mx.GetColN() - 1)
    throw std::invalid_argument(Form("[%s] Matrix is not square nor augmented...(m=%d n=%d)!\n", __PRETTY_FUNCTION__, mx.GetRowN(), mx.GetColN()));

  //Caso matriz quadrada (ou seja, so a matriz dos coeficientes)
  else if(mx.GetRowN() == mx.GetColN()){
    //sem pivotagem (elemento não nulos (ou pequenos em módulo) nas diagonais
    if(flag == 0){
      vector<double> coef;
      //eliminação
      for(int p=0; p<mx.GetRowN()-1; ++p){
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  double fcorr = mx[i][p]/mx[p][p];
	  mx[i] -= mx[p]*fcorr;
	  coef.push_back(fcorr);
	}
      }
      
      //preencher parte triangular inferior da matriz
      int j = 0;
      for(int p=0; p<mx.GetRowN(); ++p){
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  mx[i][p] = coef[j];
	  ++j;
	}
      }
    }
    
    //com pivotagem || como é de esperar, o resultado vem com linhas trocadas, pois n é possivel fazer sem troca de linhas
    else{
      double tol = 1e-6; //tolerância para pivot ser considerado como baixo. Valor pode ser alterado
      vector<double> coef;
      vector<double> s;
      double vr[mx.GetRowN()];
      
      //preenche o vetor s, com o maior numero em modulo de cada linha
      for(int p=0; p<mx.GetRowN(); ++p){
	int smax = mx.GetRowMax(p);
	if(fabs(mx[p][smax]) < tol)
	  throw std::invalid_argument(Form("[%s] Zero element in s vector...", __PRETTY_FUNCTION__));
	else
	  s.push_back(mx[p][smax]);
      }
      
      for(int p=0; p<mx.GetRowN()-1; ++p){
	int index_max = p; 
	double max = 0.;
	//maximo valor relativo na coluna abaixo do pivot (inclusive)
	for(int r=p; r<mx.GetRowN(); ++r){
	  vr[r] = mx[r][p]/s[r];
	  
	  if(fabs(vr[r]) > max){
	    max = fabs(vr[r]);
	    index_max = r;
	  } 
	}
	//se o valor maximo relativo for pequeno, sair
	if(max < tol)
	  throw std::invalid_argument(Form("[%s] Relative value too small...", __PRETTY_FUNCTION__));  // <- Aqui ja esta certo
	//trocas de linhas da matriz e do vetor s
	if(p != index_max){
	  ++count;
	  mx.swapRows(p, index_max);
	  swap(s[p], s[index_max]);
	}
	//eliminação
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  double fcorr = mx[i][p]/mx[p][p];
	  mx[i] -= mx[p]*fcorr;
	  coef.push_back(fcorr);
	}
      }
      
      //preencher parte triangular inferior
      int j = 0;
      for(int p=0; p<mx.GetRowN(); ++p){
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  mx[i][p] = coef[j];
	  ++j;
	}
      }      
    }
  } 
  
  //=====================================================================

  //Com matriz aumentada. Devolve a matriz LU que resulta de A, e mantem os coeficientes de b inalterados
  //Apenas com linhas trocadas, eventualmente
  
  else{
    //sem pivotagem (elemento não nulos (ou pequenos em módulo) nas diagonais
    if(flag == 0){
      vector<double> coef;

      //guardar a coluna de constantes e colocar coluna a zeros na matriz
      Vec consts = mx.GetCol(mx.GetColN() - 1);
      for(int i=0; i<mx.GetRowN(); ++i)
	mx[i][mx.GetColN() - 1] = 0;

      //eliminação
      for(int p=0; p<mx.GetRowN() - 1; ++p){
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  double fcorr = mx[i][p]/mx[p][p];
	  mx[i] -= mx[p]*fcorr;
	  coef.push_back(fcorr);
	}
      }
      
      //preencher parte triangular inferior da matriz e parte da matriz aumentada
      int j = 0;
      for(int p=0; p<mx.GetRowN(); ++p){
	mx[p][mx.GetColN() - 1] = consts[p];
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  mx[i][p] = coef[j];
	  ++j;
	}
      }
    }
    
    //com pivotagem || como é de esperar, o resultado vem com linhas trocadas, pois n é possivel fazer sem troca de linhas
    else{
      double tol = 1e-6; //tolerância para pivot ser considerado como baixo. Valor pode ser alterado
      vector<double> coef;
      
      //Guardar vetor de constantes e colocar a zeros na matriz
      Vec consts = mx.GetCol(mx.GetColN() - 1);
      for(int i=0; i<mx.GetRowN(); ++i)
	mx[i][mx.GetColN() - 1] = 0;
      
      vector<double> s;
      double vr[mx.GetRowN()];
      
      //preenche o vetor s, com o maior numero em modulo de cada linha
      for(int p=0; p<mx.GetRowN(); ++p){
	int smax = mx.GetRowMax(p);
	if(fabs(mx[p][smax]) < tol)
	  throw std::invalid_argument(Form("[%s] Zero element in s vector...", __PRETTY_FUNCTION__));
	else
	  s.push_back(mx[p][smax]);
      }
      
      for(int p=0; p<mx.GetRowN()-1; ++p){
	int index_max = p;
	double max = 0.;
	//maximo valor relativo na coluna abaixo do pivot (inclusive)
	for(int r=p; r<mx.GetRowN(); ++r){
	  vr[r] = mx[r][p]/s[r];
	  
	  if(fabs(vr[r]) > max){
	    max = fabs(vr[r]);
	    index_max = r;
	  }
	}
	//valor relativo maximo pequeno => sai do programa
	if(max < tol)
	  throw std::invalid_argument(Form("[%s] Relative value too small...", __PRETTY_FUNCTION__));     
	
	//trocas de linhas da matriz   do vetor s
	if(p != index_max){
	  ++count;
	  mx.swapRows(p, index_max);
	  swap(s[p], s[index_max]);
	  swap(consts[p], consts[index_max]);
	}
	
	//eliminação
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  double fcorr = mx[i][p]/mx[p][p];
	  mx[i] -= mx[p]*fcorr;
	  coef.push_back(fcorr);
	}
      }
      
      //preencher parte triangular inferior e parte aumentada da matriz
      int j = 0;
      for(int p=0; p<mx.GetRowN(); ++p){
	mx[p][mx.GetColN() - 1] = consts[p];
	for(int i=p+1; i<mx.GetRowN(); ++i){
	  mx[i][p] = coef[j];
	  ++j;
	}
      }
    }
  }

  return count;
}


int FCmatrixAlgorithms::GaussElimination(FCmatrixFull& matrix, int flag){
  
  double fcor;
  int count = 0;//contador troca de linhas

  // eleminacao de gauss sem pivotagem
  //contudo sao tidos em atencao pivots==0
  if(flag==0){
    
    for(int i=0; i<matrix.GetRowN()-1; i++){
      
      for(int j=i+1; j<matrix.GetRowN(); j++){
	
	int k=0;

	//pivot!=0
	if(matrix[i][i]){
	  fcor=matrix[j][i]/matrix[i][i];
	}
	else{//pivot==0

	  //determinar qual a linha seguinte
	  //com o elemento da coluna i !=0
	  while(matrix[i+k][i]==0.){
	    if((k+i)==matrix.GetRowN()) break;
	    ++k;
	  }
	  if((k+i)<=matrix.GetRowN()-1){//troca de linhas
	    
	    Vec aux(matrix[i]);
	    matrix[i]=matrix[i+k];
	    matrix[i+k]=aux;
	    ++count;
	    fcor=matrix[j][i]/matrix[i][i];

	  }
	  else{
	    fcor=0;
	  }
	}
	//calculo de gauss
	matrix[j]=matrix[j]-matrix[i]*fcor;
      }
    }

    //diagonalizacao da matrix 
    for(int i=0;i<matrix.GetRowN();++i){
      if(matrix[i][i]==0){
      
	int k=0;
	while(matrix[i+k][i]==0){
	  if((k+i)==matrix.GetRowN()-1) break;
	  ++k;	  
	}
	if((k+i)==matrix.GetRowN()-1){
	  Vec aux=matrix[i];
	  matrix[i]=matrix[i+k];
	  matrix[i+k]=aux;
	}  
      }
  
    }
  }
  else{// gauss com pivotgem
    
    double tol = 1e-16; //escolhemos -16 pq um double tem precisao ate -15
    //nrs<tol nr~0
    
    vector<double> s;
    double vr[matrix.GetRowN()];

    for(int p=0; p<matrix.GetRowN(); ++p){
      
      int  smax = matrix.GetRowMax(p);

      //verificar se o maximo em modulo de cada linha e maior q a tolerancia
      if(fabs(matrix[p][smax]) < tol)
	throw std::invalid_argument(Form("[%s] Zero element in s vector...", __PRETTY_FUNCTION__));
      else //guardar os maximos num vetor
	s.push_back(matrix[p][smax]);
    }
    
    for(int p=0; p<matrix.GetRowN()-1; ++p){

      double max = 0.;
      int index_max = p;
    
      for(int r=p; r<matrix.GetRowN(); ++r){

	vr[r] = matrix[r][p]/s[r];

	if(fabs(vr[r]) > max){
	  max = fabs(vr[r]);
	  index_max = r;
	}
      }
      
      if(max < tol)
	throw std::invalid_argument(Form("[%s] Relative value too small...", __PRETTY_FUNCTION__)); 
      
      
      if(p != index_max){// troca de linhas
	++count;
	matrix.swapRows(p, index_max);
	swap(s[p], s[index_max]);
      }
      
      for(int i=p+1; i<matrix.GetRowN(); ++i){ //calculo de gauss
	double fcorr = matrix[i][p]/matrix[p][p];
	matrix[i] -= matrix[p]*fcorr;
      }
      
    }
  }

  return count;
  
}
