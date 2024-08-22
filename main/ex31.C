//exercício 31
//#include "Motion1D.h"
#include "Uniform1D.h"
#include <cstdio>

int main(){
  const float g = 9.81;

  //Uniform1D(int fN, float ti, float xi, float dt, float vel); 
  Uniform1D *p1D = new Uniform1D(100, 0., 0., 1000., 10.); // 1000 sec
  p1D->Print();

  //inicializar pm
  Motion1D* pm[2] = {
    new Uniform1D(100, 0., 0., 500., 20.),
    new Motion1D(400)
  };
  //inicializar m
  Motion1D m[2] = {
    Motion1D(400),
    Motion1D(400)
  };

  //-------------------pm
  float *t_ql = new float[400];
  float *x_ql = new float[400];

  float x0 = 20.; //altura inicial
  float t0 = 0.; //tempo inicial
  float tf = 2; //tempo final
  for(int i=0; i<400; ++i){
    t_ql[i] = t0;
    x_ql[i] = x0 - 0.5*g*t0*t0;
    t0 += tf/400; //dt = tf/400;
  }
  pm[1]->SetMotion(t_ql, x_ql, 400);

  printf("----------Mov. uniforme\n");
  pm[0]->Print();

  printf("----------Queda livre\n");
  pm[1]->Print();

  //----------------m
  float *t1 = new float[400];
  float *x1 = new float[400];
  float v0=1.;
  float dt=0.2/400;
  float t=0.;
  
  for(int i=0; i<400; ++i){ 
    x1[i]=v0*t-0.5*g*t*t;
    t1[i]=t;
    t=t+dt;
  }
 
  m[0].SetMotion(t1,x1,400);
  m[0].Print();

  m[1].SetMotion(t_ql,x_ql,400);
  m[1].Print();

  //deletes
  delete pm[0];
  delete pm[1];
  delete p1D;
  delete []t_ql;
  delete []x_ql;
  delete []t1;
  delete []x1;
  
  
  return 0;

}
