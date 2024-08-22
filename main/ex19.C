#include <cstdio>

void Mmultiply(double** mx, double* vr, int n, int m, double *pt){
  int i, j;

  for(i=0;i<n;++i){
    pt[i] = 0;
    for(j=0;j<m;++j)
      pt[i] += vr[j]*mx[i][j];
  }
}

int main(){
  int i, j;
  double mx[3][3] = {
    {5, 1, 3},
    {10, 1, 5},
    {15, 1, 4}
  };
  double **ptrmx = new double*[3];
  for(i=0;i<3;++i)
    ptrmx[i] = new double[3];

  printf("Matriz M1:\n");
  for(i=0;i<3;++i){
    for(j=0;j<3;++j){
      ptrmx[i][j] = mx[i][j]; //Atribuir valores da matriz para o ponteiro
      printf("%.1lf  ", ptrmx[i][j]); //Imprimir Matriz
    }
    printf("\n");
  }
  double vc[3] = {1, 3, 5}; //Vetor a multiplicar
  printf("\nVetor v:\n");
  for(i=0;i<3;++i)
    printf("%.1lf  ", vc[i]); //Imprime Vetor inicial
  printf("\n");
  
  double *vec = new double[3]; //Vetor que vai ter o resultado
  Mmultiply(ptrmx, vc, 3, 3, vec);
  printf("\nResultado de M*v:\n");
  for(i=0;i<3;++i)
    printf("%.1lf  ", vec[i]); //Imprimir o resultado
  printf("\n");

  //Libertar espaço
  for(i=0;i<3;++i)
    delete ptrmx[i];
  delete [] *ptrmx;
  delete [] vec;
  
  return 0;
}
