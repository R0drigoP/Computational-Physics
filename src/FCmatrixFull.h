#ifndef __FCmatrixFull__
#define __FCmatrixFull__

#include "FCmatrix.h"
#include "Vec.h"
#include <vector>

class FCmatrixFull: public FCmatrix{
  
 public:
  //constructors
  FCmatrixFull();
  FCmatrixFull(double**, int, int);
  FCmatrixFull(double*, int, int);
  FCmatrixFull(const vector<Vec>&);
  FCmatrixFull(const FCmatrixFull&);

  //destructor
  ~FCmatrixFull();
  
  //operators
  Vec& operator[](int);
  void operator=(const FCmatrix&);
  FCmatrixFull operator+(const FCmatrix&);
  FCmatrixFull operator-(const FCmatrix&);
  FCmatrixFull operator*(const FCmatrix&);
  FCmatrixFull operator*(double);
  Vec operator*(const Vec&);
  
  //virtual inherited
  virtual int GetRowN() const; //number of rows
  virtual int GetColN() const; //number of columns
  virtual double Determinant() const;//
  virtual Vec GetRow(int) const; //return row
  virtual Vec GetCol(int) const; //return col
  virtual int GetRowMax(int) const; //return index of col of max in row (in abs)
  virtual int GetColMax(int) const; //return index if row of man in col (in abs)
  virtual void swapRows(int, int); //swap rows
  virtual void Print() const; //print matrix

   //friends
  friend std::ostream& operator<<(std::ostream&, const FCmatrixFull&);

  //other usefull methods
  void Transposta(); //calculate transpose matrix
  void GetInverseMatrix(); //calculate inverse matrix //testar função!!
  
};

#endif
