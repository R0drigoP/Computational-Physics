#include <cstdio>

void sum(double* const v, int n){
  int i;
  double sum = 0.;
  for(i=0;i<n;++i)
    sum += v[i];
  v[0]=sum;
}

int main(){
  double v[5] = {1, 2, 3, 4, 5};
  sum(v, 5);
  printf("%lf\n", v[0]);
  return 0;

  
}
