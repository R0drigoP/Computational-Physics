#ifndef __FCmatrix__
#define __FCmatrix__

#include "Vec.h"
#include <vector>
#include <iostream>
using namespace std;

class FCmatrix{
 protected:
  vector<Vec> M;

 public:
  //Constructors
  FCmatrix();
  FCmatrix(double**, int, int); //rows x columns
  FCmatrix(double*, int, int); //rows x columns
  FCmatrix(const vector<Vec>&);
  FCmatrix(const FCmatrix&);

  //operators
  virtual Vec& operator[](int);
  
  //other methods
  virtual int GetRowN() const=0; //number of rows
  virtual int GetColN() const=0; //number of columns
  virtual double Determinant() const=0; //determinant
  virtual Vec GetRow(int) const=0; //return row
  virtual Vec GetCol(int) const=0; //return col
  virtual int GetRowMax(int) const=0; //return index of col of max in row (in abs)
  virtual int GetColMax(int) const=0; //return index if row of man in col (in abs)
  virtual void swapRows(int, int)=0; //swap rows
  virtual void Print() const; //print matrix
  
  //friend methods
  friend ostream& operator<<(ostream&, const FCmatrix&);
};

#endif
