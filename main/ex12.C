#include <cstdio> //printf, scanf
#include <cmath> //sqrt

int main(){
  double t, h;
  const double g = 9.80665;
  scanf("%lf", &h);

  t = sqrt(2*g*h);

  printf("O corpo demororou %lf s a cair\n", t);
  return 0;
}

  

  
