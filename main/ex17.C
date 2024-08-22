#include <iostream>
using namespace std;
#include <cstdio>
#include <ctime>
#include <cstdlib>

int* func1(){
  int *x = new int(rand());
  return x;
}

int& func2(){
  int *x = new int(rand());
  return *x;
}

int main(){
  //counter
  int i;
  //array space
  int n = 1e6;

  //seed random
  time_t T;
  srand(time(&T));
  cout << "seed = " << T << endl;

  //returning by pointer
  cout << "-------------------------------- returning by pointer" << endl;

  //problem: memory leakage
  int** pp = new int* [n];

  for(i=0;i<n;++i){
    int* p = func1();
    if(i<10)
      printf("main/random number = %d (address = %p)\n", *p, p);
    pp[i] = p;
  }

  //return by reference
  cout << endl <<  "-------------------------------- returning by reference" << endl;

  for(i=0;i<n;++i){
    int& x = func2();
    if(i<10)
      printf("main/random number = %d (address = %p)\n", x, &x);
    pp[i] = &x;
  }
  
  //pause...
  getchar();

  //freeing memory
  for(i=0;i<n;++i)
    delete pp[i];
  delete [] pp;

  return 0;
}
  

  
