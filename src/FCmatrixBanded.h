#ifndef __FCmatrixBanded__
#define __FCmatrixBanded__

#include "Vec.h"
#include <vector>

class FCmatrixBanded{

 private:
  Vec down, mid, top;
  Vec Ldown;
  Vec Umid, Utop;
  
 public:
  //constructor
  FCmatrixBanded();
  FCmatrixBanded(Vec a,Vec b,Vec c);
  FCmatrixBanded(double* a,int na, double* b,int nb,
		 double* c, int nc);
  FCmatrixBanded(const FCmatrixBanded&);

  //destructor
  ~FCmatrixBanded(){;}
  
  //operators
  //Vec& operator[](int);
  void operator=(const FCmatrixBanded&);
  FCmatrixBanded operator+(const FCmatrixBanded&);
  FCmatrixBanded operator-(const FCmatrixBanded&);
  //FCmatrixBanded operator*(const FCmatrixBanded&);
  FCmatrixBanded operator*(double);
  
  int GetRowN() const{return mid.size();} 
  int GetColN() const{return mid.size();} 
  double Determinant() const;
  Vec GetRow(int) const;
  Vec GetCol(int) const;
  Vec GetMid() const {return mid;}
  Vec GetTop() const {return top;}
  Vec GetDown() const{return down;}
  Vec GetUmid() const {return Umid;}
  Vec GetUtop() const {return Utop;}
  Vec GetLdown() const{return Ldown;}
  
    
  int GetRowMax(int) const; //return index of col of max in row (in abs)
  int GetColMax(int) const; //return index if row of man in col (in abs)
 

  
  void Print() const;
  
};

#endif
