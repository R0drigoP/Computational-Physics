#include <cstdio> //printf
#include <cmath> //cos, sqrt

double Sum(int* vi, int* vj){
  
  int i, j;
  double sum =0.0;

  for(i=0;i<=*vi;++i){
    for(j=5;j<=*vj;++j)
      sum += cos(i*i + sqrt(j));
  }

  return sum;
}


int main(){
  int v[2];
  v[0] = 100;
  v[1] = 300;
  double sum = Sum(&v[0], &v[1]);

  printf("%lf\n", sum);
  return 0;
}
