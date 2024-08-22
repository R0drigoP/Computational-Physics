#include <cstdio> //printf
#include <cstdlib> //rand
#include <ctime> //time(NULL)
#include <cmath> //sqrt

int main(){
  double x[1000], y, soma=0.0, x_medio, desvio=0.0;
  int i;
  const int N = 1000;
  srand(time(NULL));

  for(i=0; i<N; ++i){
    x[i] = ((double)rand()/(double)RAND_MAX)*50 + 5;
    y = x[i]/(x[i]-10);
    soma += x[i];
    printf("x: %lf -> y: %lf\n", x[i], y);
  }
  
  x_medio = soma/(double)N;

  for(i=0; i<N; ++i)
    desvio += (x[i] - x_medio)*(x[i] - x_medio);
  desvio = sqrt(1/(double)N*desvio);

  printf("x médio: %lf\ndesvio padrao: %lf\n", x_medio, desvio);
  return 0;
}
    
