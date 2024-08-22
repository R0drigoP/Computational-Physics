#include "alunoIST.h"
#include "Turma.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

int main(){
  Turma T1("MEFT T1", 2);
  alunoIST *A1 = new alunoIST[1];
  A1->SetName("Rodrigo");
  A1->SetNumber(96563);
  A1->SetBranch("MEFT");
  T1.AddAluno(A1);
  
  alunoIST *A2 = new alunoIST[1];                                              
  A2->SetName("Joao");                                                       
  A2->SetNumber(96542);
  A2->SetBranch("MEFT");  
  T1.AddAluno(A2);

  T1.Print();
  
  return 0;
}
