#include "FCmatrixFull.h"
#include "EqSolver.h"

#include <stdexcept>
#include "TROOT.h"
#include "FCmatrixAlgorithms.h"
#include <cstdio>

//constructors
FCmatrixFull::FCmatrixFull() {;}

FCmatrixFull::FCmatrixFull(double** a, int m, int n){
  if(!a)
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));

  else if(m<0 || n<0)
    throw std::invalid_argument(Form("[%s] Received negative number of arguments...!\n", __PRETTY_FUNCTION__));
  
  for(int i=0; i<m; ++i)
    M.emplace_back(n, a[i]);
}

FCmatrixFull::FCmatrixFull(double* a, int m, int n){
  if(!a)
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));
  else if(m<0 || n<0)
    throw std::invalid_argument(Form("[%s] Received negative number of arguments...!\n", __PRETTY_FUNCTION__));

  for(int i=0; i<m; ++i)
    M.emplace_back(n, &a[i*n]);
}

FCmatrixFull::FCmatrixFull(const vector<Vec>& v){
  for(int i=0; i<v.size(); ++i)
    M.emplace_back(v[i]);
}

//copy constructor
FCmatrixFull::FCmatrixFull(const FCmatrixFull& mx){
  for(int i=0; i<mx.GetRowN(); ++i)
    M.emplace_back(mx.M[i]);
}

//destructor
FCmatrixFull::~FCmatrixFull(){;}

//operators
Vec& FCmatrixFull::operator[](int i){
  if (i>=this->GetRowN() || i<0)
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, this->GetRowN()));
  
  return M[i];
}

void FCmatrixFull::operator=(const FCmatrix& mx){
  //Não faz sentido comparar tamanhos, porque vamos apagar a matriz de qualquer das formas, e refazê-la
  //if(this->GetRowN() != mx.GetRowN() || this->GetColN() != mx.GetColN())
  //throw std::invalid_argument(Form("[%s] objects with different size...(M=%d x %d || v.M=%d x %d)!\n", __PRETTY_FUNCTION__, this->GetRowN(), this->GetColN(), mx.GetRowN(), mx.GetColN()));
  
  if(this != &mx){
    M.clear();
    for(int i=0; i<mx.GetRowN(); ++i)
      M.push_back(mx.GetRow(i));
  }
}

FCmatrixFull FCmatrixFull::operator+(const FCmatrix& mx){
  if(this->GetRowN() != mx.GetRowN() || this->GetColN() != mx.GetColN())
    throw std::invalid_argument(Form("[%s] objects with different size...(M=%d x %d || v.M=%d x %d)!\n", __PRETTY_FUNCTION__, this->GetRowN(), this->GetColN(), mx.GetRowN(), mx.GetColN()));
  
  vector<Vec> v;
  for(int i=0; i<mx.GetRowN(); ++i)
    v.push_back(M[i] + mx.GetRow(i));
  
  return FCmatrixFull(v);
}

FCmatrixFull FCmatrixFull::operator-(const FCmatrix& mx){
  if(this->GetRowN() != mx.GetRowN() || this->GetColN() != mx.GetColN())
    throw std::invalid_argument(Form("[%s] objects with different size...(M=%d x %d || v.M=%d x %d)!\n", __PRETTY_FUNCTION__, this->GetRowN(), this->GetColN(), mx.GetRowN(), mx.GetColN()));

  vector<Vec> v;
  for(int i=0; i<mx.GetRowN(); ++i)
    v.push_back(M[i] - mx.GetRow(i));

  return FCmatrixFull(v);
}

FCmatrixFull FCmatrixFull::operator*(const FCmatrix& mx){
  if(this->GetColN() != mx.GetRowN())
    throw std::invalid_argument(Form("[%s] objects with non suitable dimensions...!\n", __PRETTY_FUNCTION__));

  vector<Vec> v;
  Vec v1(mx.GetColN());
  Vec v2, v3;
  for(int i=0; i<this->GetRowN(); ++i){
    for(int j=0; j<mx.GetColN(); ++j)
      v1[j] = (this->GetRow(i)).dot(mx.GetCol(j));
    v.push_back(v1);
  }
				      
  return FCmatrixFull(v);
}

FCmatrixFull FCmatrixFull::operator*(double lambda){
  vector<Vec> v;
  for(int i=0; i<this->GetRowN(); ++i)
    v.push_back(M[i]*lambda);

  return FCmatrixFull(v);
}

Vec FCmatrixFull::operator*(const Vec& v){
  if(v.size() != this->GetColN())
    throw std::invalid_argument(Form("[%s] objects with non suitable dimensions...!\n", __PRETTY_FUNCTION__));
  double result[this->GetRowN()];
  for(int i=0; i<this->GetRowN(); ++i){
    result[i] = 0;
    for(int j=0; j<this->GetColN(); ++j)
      result[i] += v[j]*M[i][j];
  }  
  return Vec(this->GetRowN(), result);
}


///////////////// virtual inherithed methods
int FCmatrixFull::GetRowN() const{
  return M.size();
}

int FCmatrixFull::GetColN() const{
  return M[0].size();
}

double FCmatrixFull::Determinant() const{
  
  int n=0;
  double dtr=1;
  FCmatrixFull matrix= *this;
  //matrix.Print();
  n=FCmatrixAlgorithms::GaussElimination(matrix,1);
  
  for(int i=0; i<this->GetRowN(); ++i){
    dtr=dtr*matrix[i][i];
  }
  
  if(n%2==0){
    return dtr;
  }
  else{
    return -dtr;
  }
}

Vec FCmatrixFull::GetRow(int i) const{
  if(i<0 || i>=this->GetRowN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));  
  return M[i];
}

Vec FCmatrixFull::GetCol(int j) const{
  if(j<0 || j>=this->GetColN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));
  
  double a[this->GetRowN()];
  for(int i=0; i<this->GetRowN() ; ++i)
    a[i] = M[i][j];
  
  return Vec(this->GetRowN(), a);
}

int FCmatrixFull::GetRowMax(int i) const{
  if(i<0 || i>=this->GetRowN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));

  int flag=0;
  double max = fabs(M[i][0]);
  for(int j=1; j<this->GetColN(); ++j){
    if(double x=fabs(M[i][j] > max)){
      max = x;
      flag = j;
    }
  }

  return flag;
}

int FCmatrixFull::GetColMax(int j) const{
  if(j>0 || j>=this->GetColN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));

  int flag=0;
  double max = fabs(M[0][j]);
 
  for(int i=1; i<this->GetRowN(); ++i){
    if(double x=fabs(M[i][j]) > max){
	  max = x;
	  flag = i;
    }
  }

  return flag;
}

void FCmatrixFull::swapRows(int i, int j){  
  if(max(i,j)>=this->GetRowN()||min(i,j)<0){                                 
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));                                           
  }                                   
  if(i!=j){                                  
    Vec aux(this->GetColN());                                 
    aux=M[j];                           
    M[j]=M[i];                                 
    M[i]=aux;                                           
  }                                  
}           

void FCmatrixFull::Print() const{

  cout << "matrix: [\n" << endl;
  for(int i=0; i<this->GetRowN(); ++i)
    cout << "           " << this->M[i] << endl;
  cout << "       ]" << endl;  
}

//friends
std::ostream& operator<<(std::ostream& s, const FCmatrixFull& matrix){
  
  s << "matrix: [\n" << endl;
  for(int i=0; i<matrix.GetRowN(); ++i)
    s << "           " <<matrix.M[i] << endl;
  s << "       ]" << endl;

  return s;
}

//other usefull methods
void FCmatrixFull::Transposta(){

  FCmatrixFull aux(*this);

  for(int i=0;i<aux.GetRowN();++i){
  aux.M[i]=this->GetCol(i);
  }

  M=aux.M;
  
}

void FCmatrixFull::GetInverseMatrix(){
  int rowN = this->GetRowN();
  int colN = this->GetColN();

  if(rowN != colN)
     throw std::invalid_argument(Form("[%s]Matrix given is not square\n", __PRETTY_FUNCTION__));
  
  vector<Vec> trans;
  Vec col(colN, 0.);
  
  for(int i=0; i<colN ;i++){

    //colunas identidade
    Vec linhas(rowN, 0.);
    linhas[i]=1;

    //calcular colunas inversa
    EqSolver Eq(M,linhas);
    col=Eq.GaussEliminationSolver(1,1);

    //preencher o vector que corresponde a matrix transposta do resultado
    trans.push_back(col);
  }

  FCmatrixFull result(trans);
  result.Transposta();
  
  *this = result;
}
