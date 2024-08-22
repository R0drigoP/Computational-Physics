#include <cstdio> //printf
#include <cmath> //sin(x)

double f(double x){
  return sin(x)*sin(x);
}

double z(double x){
  return x + f(x);
}

int main(){
  double result1 = z(0.4);
  double result2 = z(2.1);
  double result3 = z(1.5);

  printf("- z(0.4) = %lf\n- z(2.1) = %lf\n- z(1.5) = %lf\n", result1, result2, result3);

  return 0;
}
