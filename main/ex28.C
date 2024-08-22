#include "pessoa.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

  string name = "Rodrigo";
  unsigned int BornD = 130801;
  pessoa P[10];
  P[0].SetName(name);
  P[0].SetBornD(BornD);
  P[0].Print();
  

  return 0;
}
