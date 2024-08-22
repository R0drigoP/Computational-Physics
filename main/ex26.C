#include <cstdio> 
#include <ctime> //time
#include <cstdlib> //rand
#include <cmath> //sqrt
#include <iostream> //cout
#include <vector> //vectors
#include <algorithm> //sort
#include <numeric> //adjacent_difference

using namespace std;

int main(){
  int n = 100; //numeros a gerar
  double sum = 0.;
  double mean = 0.;
  double desvio = 0.;
  vector <double> v;
  time_t T;
  srand(time(&T)); //colocar em seed aleatória

  for(int i=0; i<n; ++i){
    double x = (double)rand()/(double)RAND_MAX;
    v.push_back(x);
    sum += x;
    mean += x/n;
  }

  for(int i=0; i<n; ++i)
    desvio += (v[i] - mean)*(v[i] - mean)/n;
  desvio = sqrt(desvio);

  cout << "soma = " << sum << endl;
  cout << "media = " << mean << endl;
  cout << "desvio padrao = " << desvio << endl;

  double sum2 = 0.;
  double mean2 = 0.;
  for(int i=0; i<n; ++i){
    v[i] -= mean;
    sum2 += v[i];
    mean2 += v[i]/n;
  }

  cout << "--------subtraindo a cada valor a media" << endl;
  cout << "nova soma = " << sum2 << endl;
  cout << "nova media = " << mean2 << endl;

  /*for(int i=0; i<10; ++i)
    cout << v[i] << " " << endl;
    cout << endl;*/
  
  sort(v.begin(), v.end());
  cout << "---------------imprimindo primeiros 10 valores do vetor ordenado" << endl;
  for(int i=0; i<10; ++i)
    cout << v[i] << " " << endl;

  cout << "---------------imprimindo primeiras 10 diferencas consecutivas" << endl;
  
  vector <double> vec(n);
  adjacent_difference(v.begin(), v.end(), vec.begin());

  
  for(int i=0; i<10; ++i)
    cout << vec[i+1] << endl;
  
  return 0;
}
