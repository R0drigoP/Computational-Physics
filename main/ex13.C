#include <cstdio> //printf, scanf
#include <cmath> //cbrt

double altitude(double T){
  const double G = 6.67e-11;
  const double M = 5.97e24;
  const double R = 6371e3;

  double h = cbrt(G*M*T*T/(4*M_PI*M_PI)) - R;

  return h;
  }
  

int main(){
  double h, T;
  scanf("%lf", &T);

  h = altitude(T);

  printf("%lg\n", h);
  return 0;
}

/*
Ao calcular com T=45min, dá uma altitude negativa, ou seja,
é impossivel ter um satélite com este período.
Nos outros dois casos, o resultado é razoável
*/
