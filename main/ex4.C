#include <cstdio>
#include <cmath>


int main(){
  float fpi = 4*atan(1);
  double dpi = 4*atan(1);

  double y = fabs(M_PI - fpi);
  double x = fabs(M_PI - dpi);

  printf("erro float: %.17lf\n", y);
  printf("erro double: %.17lf\n", x);
  //printf(" %.15lf\n %.15lf\n", M_PI - fpi, );
  return 0;
}
