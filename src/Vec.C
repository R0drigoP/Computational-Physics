#include "Vec.h"
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <iomanip>
#include <cmath>

#include "TROOT.h"

//#define DEBUG

///////////////////// constructors

Vec::Vec(int i, double x) : N(i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (N<0)
    throw std::invalid_argument(Form("[%s] received negative number of elements...!\n", __PRETTY_FUNCTION__));
  else if(N==0)
    entries = nullptr;
  else{
    entries = new double[N];
    std::fill_n(entries, N, x);
  }
}

Vec::Vec(int i, const double* x) : Vec(i) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (x)
    std::copy(x, x+i, entries);
  else  
    throw std::invalid_argument(Form("[%s] null pointer to array...!\n", __PRETTY_FUNCTION__));
}

Vec::Vec(const Vec& v) : Vec(v.N, v.entries) { //c++11 on...
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
}

////////////////////// destructor
Vec::~Vec() {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if(entries)
    delete [] entries;
}

///////////////////// operators
double Vec::operator[](int i) const {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N || i<0) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));
  
  return entries[i];
}


double& Vec::operator[](int i) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (i>=N || i<0) 
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, N));  
  return entries[i];
}

void Vec::operator=(const Vec& v) {
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__);
#endif
  if (this != &v) {
    if (v.N != N) {
      N = v.N;
      delete [] entries;
      entries = new double[N];
    }
    std::copy(v.entries, v.entries+N, entries);    
  }
}

Vec Vec::operator+(const Vec& v) const{
  if (v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));
  
  for (int i=0; i<N; ++i)                                           
    entries[i] += v.entries[i];    

  return *this;                 
}

const Vec& Vec::operator+= (const Vec& v) { 
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif
  if (v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));        
  for (int i=0; i<N; ++i)
    entries[i] += v.entries[i];
  return *this;
}


Vec Vec::operator-(const Vec& v) const{
  if(v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));

  for(int i=0; i<N; ++i)
    entries[i] -= v.entries[i];

  return *this;
}

const Vec& Vec::operator-=(const Vec& v){
  if(v.N != N)
    throw std::invalid_argument(Form("[%s] objects with different size...(N=%d v.N=%d)!\n", __PRETTY_FUNCTION__, N, v.N));

  for(int i=0; i<N; ++i)
    entries[i] -= v.entries[i];

  return *this;
}

Vec Vec::operator*(double x) const{
#ifdef DEBUG
  printf("[%s]\n", __PRETTY_FUNCTION__ );
#endif
  if (abs(x-1.)<1E-9)
    return *this;
  double a[N];
  for (int i=0; i<N; ++i) {
    a[i] = entries[i] * x;
  }
  return Vec(N, a);
}


Vec Vec::operator*(const Vec& v) const{                               
  if(N != v.N)                                             
    throw std::invalid_argument(Form("[%s] the two vectors must have the same size!\n", __PRETTY_FUNCTION__));
  
  double a[N];                                           
  for(int i=0;i<N; ++i)            
    a[i] = entries[i]*v.entries[i];  

  return Vec(N, a);
}


///////////////////// other methods

int Vec::size() const{
  return N;
}

double Vec::dot(const Vec& v){
  if (N != v.N)
    throw std::invalid_argument(Form("[%s] the two vectors must have the same size!\n", __PRETTY_FUNCTION__));
  
  return inner_product(entries, entries+N, v.entries, 0.);
}

void Vec::SetEntries(int n, double* v){
  //ha forma de saber o tamanho de v, para ver se o tamanho de v é n??
  N=n;
  if(!entries)
    entries = new double[N];
  
  for(int i=0; i<N; ++i)
    entries[i] = v[i];
}

double Vec::sumAbs(){
  return accumulate(entries, entries+N, 0, [](double accum, double x){return accum + fabs(x);});
}

double Vec::At(int pos){
  if(pos<0 || pos>=N)
    throw std::invalid_argument(Form("[%s] invalid numbers for indexes\n", __PRETTY_FUNCTION__));

  return entries[pos];
}

void Vec::swap(int i, int j){
  if(min(i, j)<0 || max(i, j)>=N)
    throw std::invalid_argument(Form("[%s] invalid numbers for indexes\n", __PRETTY_FUNCTION__));
  if(i != j)
    swap(entries[i], entries[j]);
}

void Vec::Print() const{
  for(int i=0; i<N; ++i)
    cout << setprecision(6) << entries[i] << " " << flush;
  cout << endl;
}

double Vec::GetMaxAbs() const{

  double max=0;
  double mod[N];
  
  for(int i=0; i<N; ++i){

    if(entries[i]>=0){
      mod[i]=entries[i];
    }
    else{
      mod[i]=-entries[i];
    }
    
  }

  return max=*max_element(mod,mod+N);
}


///////////////////// friend methods

std::ostream& operator<<(std::ostream& s, const Vec& v) {
  s << "[";
  for (int i=0; i<v.N; ++i) {
    s << std::fixed << std::setprecision(6) << v.entries[i];
    if (i<v.N-1) s << ", ";
  }
  s << "]";

  return s;
}

Vec operator*(double x, const Vec& v){}
