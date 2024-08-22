#include <cstdio>
#include <iostream>
#include <cmath>
using namespace std;

int main(){

  //(a) Energy of lvl n of hydrogen atom  with lambda function (pode-se tirar o "->double")
  auto fE = [] (int n) -> double{
    double m = 9.1093835611e-31;
    double e = 1.60217656535e-19;
    double h = 6.62607015e-34;
    double eps_0 = 8.854187817e-12;
    int z = 1;
    double En = -z*z*m*e*e*e*e/(8*h*h*eps_0*eps_0*n*n);
    return En;
  };

  cout << fE(1) << endl;

  
  //(b) Same but with any z value (any atom)
  auto fEZ = [] (int n, int z){                                              
    double m = 9.1093835611e-31;                                               
    double e = 1.60217656535e-19;                                              
    double h = 6.62607015e-34;                                                
    double eps_0 = 8.854187817e-12;                                            
    double En = -z*z*m*e*e*e*e/(8*h*h*eps_0*eps_0*n*n);                         
    return En;                                                                 
  };

  cout << fEZ(1, 4) << endl;


  //(c) Now declaring constants in main and lambda function to get wl
  double m = 9.1093835611e-31;                                                                                                                                                                            
  double e = 1.60217656535e-19;                                                                                                                                                                          
  double h = 6.62607015e-34;                                                                                                                                                                            
  double eps_0 = 8.854187817e-12;
  double c = 2.99792458e8;
  auto fEL = [m, e, h, eps_0, c] (int z, int n1, int n2){                                                                                                               
    double En1 = -z*z*m*e*e*e*e/(8*h*h*eps_0*eps_0*n1*n1);
    double En2 = -z*z*m*e*e*e*e/(8*h*h*eps_0*eps_0*n2*n2);
    double dE = En2 - En1;
    double wl = h*c/abs(dE);
    return wl;                                                                  
  };

  cout << fEL(1, 1, 2) << endl;

  //(d) matriz E[z][n]
  double E[10][20];
  for(int z=0; z<10; ++z){
    for(int n=0; n<20; ++n){
      E[z][n] = fEZ(n+1, z+1);
      printf("%.2lg ", E[z][n]);
    }
    cout << endl;
  }
  
  return 0;
  
}
