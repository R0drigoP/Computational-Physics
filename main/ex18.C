#include <cstdio>

//Traço de matriz
int Trace(int** mx, int n){
  int sum = 0;
  for(int i=0; i<n; ++i)
    sum += mx[i][i];
  return sum;
}

//Linha de matriz
int* Mrow(int i, int **mx, int n, int m){
  int* line = new int[m];

  for(int j=0; j<m; ++j)
    line[j] = mx[i-1][j];
  
  return line; 
  }

//Resultado de Mx*v
int* mv_mult(int *v, int **mx, int n, int m){
  int *result = new int[n];
  int i, j;

  for(i=0;i<n;++i){
    result[i] = 0;
    for(j=0;j<m;++j)
      result[i] += v[j]*mx[i][j];
  }

  return result;
}

//Mx1(nxm)*Mx2(mxp)
int** mat_mult(int** mx1, int** mx2, int n, int m, int p){
  int i, j, k;

  int **r_mx = new int* [n];

  for(i=0;i<n;++i)
    r_mx[i] = new int[p];
  
  for(i=0;i<n;++i){
    for(j=0;j<p;++j){
      r_mx[i][j] = 0;
      for(k=0;k<m;++k)
	r_mx[i][j] += mx1[i][k]*mx2[k][j];
    }
  }
  
  return r_mx;
}

int main(){
  int i, j;
  int mx1[2][2] = {
    {2, 10},
    {5, 7}
  };

  int mx2[2][3] = {
    {2, 10, 5},
    {3, 2, 7}
  };

  int v[3] = {2, 5, 7}; //Vetor v
  int** ptrmx1 = new int* [2]; //Matriz mx1(2x2)
  int** ptrmx2 = new int* [2]; //Matriz mx2(2x3)
  int** ptrmx3 = new int* [2]; //Matriz mx3(2x3) => mx3 = mx1.mx2
  for(i=0;i<2;++i){
    ptrmx1[i] = new int[2];
    ptrmx2[i] = new int[3];
    ptrmx3[i] = new int[3];
    }
  
  //Atribuião de valores da matriz mx1
  printf("Matriz 1 (2x2):\n");
  for (i=0; i<2; ++i){        
    for (j=0; j<2; ++j){                 
      ptrmx1[i][j] = mx1[i][j];
      printf("%d  ", ptrmx1[i][j]); //Imprime mx1
      }
    printf("\n");
  }

  //Atribuição de valores da matrix mx2
  printf("\nMatriz 2 (2x3):\n");
  for(i=0; i<2; ++i){
    for(j=0; j<3; ++j){
      ptrmx2[i][j] = mx2[i][j];
      printf("%d  ", ptrmx2[i][j]); //Imprime mx2
    }
    printf("\n");
  }
  
  //Traço da Matriz mx1
  int tra = Trace(ptrmx1, 2);
  printf("\nTraco da matriz 1 = %d\n", tra);

  //Linha 1 da Matriz mx1
  int *line = new int[2];
  line =  Mrow(1, ptrmx1, 2, 2);
  printf("\nLinha 1 da matriz 1: ");
  for(i=0;i<2;++i)
    printf("%d  ", line[i]);

  //Resultado de mx2*v
  int* col_vec = new int[2];
  col_vec  = mv_mult(v, ptrmx2, 2, 3);
  printf("\n\nMatriz 2 x Vetor v: "); 
  for(i=0; i<2; ++i)
    printf("%d  ", col_vec[i]);

  
  printf("\n\nMatriz 3 = M1*M2:\n");
  ptrmx3 = mat_mult(ptrmx1, ptrmx2, 2, 2, 3); 
  for(i=0; i<2; ++i){
    for(j=0;j<3; ++j)
      printf("%d  ", ptrmx3[i][j]);
    printf("\n");
  }

  for(i=0; i<2; ++i){
    delete ptrmx1[i];
    delete ptrmx2[i];
    delete ptrmx3[i];
  }
    
  delete [] ptrmx1;
  delete [] ptrmx2;
  delete [] ptrmx3;
  delete [] line;
  delete [] col_vec;
  
  return 0;
}
