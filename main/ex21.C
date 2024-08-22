#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<double> rand2vec(int n){
  time_t T;
  srand(time(&T));
  vector<double> v;
  for(int i=0; i<n; ++i){
    double x = 360*(double)rand()/(double)RAND_MAX;
    v.push_back(x);
  }

  return v;
}

vector<double>* rand2vecp(int n){
  vector<double> *v = new vector<double>[1];
  time_t T;
  srand(time(&T));

  for(int i=0; i<n; ++i){                                                      
    double x = 360*(double)rand()/(double)RAND_MAX;                            
    v[0].push_back(x);
  }

  return v;
}


int main(){
  int n = 10;
  vector<double> vec = rand2vec(n);
  cout << "----------------retornar vetor" << endl;
  for(int i=0; i<n; ++i)
    cout << vec[i] << " " << flush;
  cout << endl;

  cout << "----------------retornar por ponteiro" << endl;
  vector<double> *vec2;
  vec2 = rand2vecp(n); 
  for(int i=0; i<n; ++i)
    cout << vec2[0][i] << " " << flush;
  cout << endl;

  vec.clear();
  vec2[0].clear();
  return 0;
  

}
