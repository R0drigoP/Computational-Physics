#ifndef __Vec__
#define __Vec__

#include <iostream> // ostream
using namespace std;

class Vec {

 public:

  // constructors
  Vec(int i=0, double x=0); // Vec v;
  Vec(int, const double*);
  Vec(const Vec&);

  // destructor
  ~Vec();

  // operators
  double  operator[](int i) const;
  double& operator[](int i);

  void operator=(const Vec&); // A=B

  Vec operator+(); //unary opeator //É suposto fazer o quê?? Manter a matriz igual ou meter tudo positivo??
  Vec operator+(const Vec&) const;
  const Vec& operator+=(const Vec&);
  
  Vec operator-(); //unary operator
  Vec operator-(const Vec&) const;
  const Vec& operator-=(const Vec&);
  //(...)
  /*
  the overloading of then * operator allows multiply a vector by a
  scalar:
  Vec * scalar
  */
  Vec operator*(double) const; //Vec.operator*(double) <=> A*5.
  Vec operator*(const Vec&) const;
  
  // other methods
  int size() const;
  double dot(const Vec&);
  void SetEntries(int, double*);
  double sumAbs();
  double At(int); //
  void swap(int, int);
  void Print() const;
  double GetMaxAbs() const; //returns max absolute
  
  // friend methods
  friend std::ostream& operator<<(std::ostream&, const Vec&);
  /*
  in order to multiply a scalar to a vector (scalar*Vec) we need
  to implement a friend method:
  friend Vec operator*(double, const Vec&);
  */
  
 private:
  int N; // number of elements
  double *entries; // array
  
};
#endif
