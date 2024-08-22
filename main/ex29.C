#include "pessoa.h"
#include "alunoIST.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main(){
  alunoIST v[2];
  
  v[0].SetNumber(96563);                                                   
  v[0].SetBranch("MEFT");                                                     
  v[0].SetName("Rodrigo Pereira");                                            
  v[0].SetBornD(130801);
  v[0].Print();
  
  return 0;
}
