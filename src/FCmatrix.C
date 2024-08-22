#include "FCmatrix.h"
#include <utility>
#include <iostream>
#include <vector>
#include <stdexcept>
#include "TROOT.h"
using namespace std;

/////////////////// Constructors
FCmatrix::FCmatrix() {;}

FCmatrix::FCmatrix(double** a, int m, int n){;}

FCmatrix::FCmatrix(double* a, int m, int n){;}

FCmatrix::FCmatrix(const FCmatrix& mx){;}

////////////////// operators
Vec& FCmatrix::operator[](int i){
  if (i>=this->GetRowN() || i<0)
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, this->GetRowN()));
  
  return M[i];
}

void FCmatrix::Print() const{

  cout << "matrix: [\n" << endl;
  for(int i=0; i<this->GetRowN(); ++i)
    cout << "           " << this->M[i] << endl;
  cout << "       ]" << endl;  
}

/////////////////// friend methods
ostream& operator<<(ostream& s, const FCmatrix& mx){
  s << "matrix: [\n";
  for(int i=0; i<mx.GetRowN(); ++i)
    s << "           " << mx.M[i] << endl;
  s << "       ]";

  return s;
}

