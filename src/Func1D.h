#ifndef __Func1D__
#define __Func1D__

#include "TF1.h"

class Func1D{
 protected:
  TF1* F;

 public:
  //constructor and destructor
  Func1D(const TF1* fF = nullptr);
  Func1D(const TF1&);
  virtual ~Func1D();

  //Function methods
  void SetFunction(const TF1*);
  const TF1& GetFunction() const {return *F;}
  double Eval(double) const;
  
  //output
  void Draw() const;  
  
};

#endif
