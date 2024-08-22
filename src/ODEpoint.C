#include "ODEpoint.h"

////////////////////////////constructors and destructor
ODEpoint::ODEpoint(unsigned int fndim, const double* fx) :
  ndim(fndim), x(new double[ndim+1])
{
  for(int i=0; i<ndim+1; ++i)
    x[i] = fx[i];
}

ODEpoint::ODEpoint(const ODEpoint& Op): ODEpoint(Op.ndim, Op.x) {;}

ODEpoint::~ODEpoint(){
  if (x) delete x;
}

///////////////////////////operators
ODEpoint ODEpoint::operator*(double k) const{
  if(!x)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));
  
  double fx[ndim+1];
  for(int i=0; i<ndim+1; ++i)
    fx[i] = x[i]* k;

  return ODEpoint(ndim, fx);
}

ODEpoint ODEpoint::operator+(const ODEpoint& Op) const{
  if(ndim != Op.ndim)
    throw invalid_argument(Form("[%s] Non-existing pointer...!\n", __PRETTY_FUNCTION__));

  double fx[ndim+1];
  for(int i=0; i<ndim+1; ++i)
    fx[i] = x[i] + Op.x[i];
  
  return ODEpoint(ndim, fx);
}

ODEpoint ODEpoint::operator-(const ODEpoint& Op) const{
  if(ndim != Op.ndim)
    throw invalid_argument(Form("[%s] Points with different dimensions...! (N1 = %u, N2 = %u)\n", __PRETTY_FUNCTION__, ndim, Op.ndim));

  double fx[ndim+1];
  for(int i=0; i<ndim+1; ++i)
    fx[i] = x[i] - Op.x[i];

  return ODEpoint(ndim, fx);
}

void ODEpoint::operator=(const ODEpoint& Op){
  if(x) delete x;
  ndim = Op.ndim;
  x = new double[ndim];
  for(int i=0; i<ndim+1; ++i)
    x[i] = Op.x[i];
}

const double& ODEpoint::operator[](int i) const{
  if(i < 0 || i >= ndim+1)
    throw invalid_argument(Form("[%s] Invalid Index...! (Min index = 0 || Max index = %u || Index wanted = %d)\n", __PRETTY_FUNCTION__, ndim, i));
  return x[i];
}

double& ODEpoint::operator[](int i){
  if(i < 0 || i >= ndim+1)
    throw invalid_argument(Form("[%s] Invalid Index...! (Min index = 0 || Max index = %u || Index wanted = %d)\n", __PRETTY_FUNCTION__, ndim, i));
  return x[i];
}

////////////////////////////output
void ODEpoint::Print() const{
  if(!x)
    printf("[ , ]");
  else{
    cout << "[" << flush;
    for(int i=0; i<ndim+1; ++i)
      cout << fixed << x[i] << ", " << flush;
    cout << "\b\b]" << endl;
  }
}

ostream& operator<<(ostream& s, const ODEpoint& Op){
  s << "[";
  for(int i=0; i<Op.ndim+1; ++i)
    s << fixed << Op.x[i] << ", " << flush;
  s << "\b\b]" << flush;

  return s;
}
