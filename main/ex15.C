#include <cstdio> //printf
#include <cmath> //M_PI, sqrt, sin

double f1(double x){
  x = M_PI*x/180;
  return sqrt(sin(2*x));
}

void f2(double x, double& f){
  x = M_PI*x/180;
  f = sqrt(sin(2*x));
}

void f3(double x, double* f){
  x =  M_PI*x/180;
  *f = sqrt(sin(2*x));
}

void f4(const double x, double* const f){
  double y = M_PI*x/180;
  *f = sqrt(sin(2*y));
}
  

int main(){
  
  double x = f1(45);
  printf("%lf\n", x);
  
  double y; //variável onde se guarda o valor
  f2(45, y); 
  printf("%lf\n", y);

  double z;
  f3(45, &z);
  printf("%lf\n", z);

  double w;
  f4(45, &w);
  printf("%lf\n", w);
  
  return 0;
}

