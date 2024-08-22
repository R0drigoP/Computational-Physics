#include "FCmatrixBanded.h"
#include <stdexcept>
#include "TROOT.h"
#include "FCmatrixAlgorithms.h"
#include <cstdio>
#include <array>

FCmatrixBanded::FCmatrixBanded(){;}

FCmatrixBanded::FCmatrixBanded(Vec a,Vec b,Vec c){

  if(b.size()>a.size() && b.size()>c.size() && c.size()==a.size()){

    mid=b;
    down=a;
    top=c;

  }
  else if(a.size()>b.size() && a.size()>c.size() && c.size()==b.size()){
    
    mid=a;
    down=b;
    top=c;
    
  }
  else if(c.size()>b.size() && c.size()>a.size() && a.size()==b.size()){
    
    mid=c;
    down=a;
    top=b;
    
  }
  else
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));

 
  Vec aux0(down.size(), down[0]/mid[0]);
  Vec aux1(mid.size(),mid[0]);

  int flag=0;
  for(int i=1; i<mid.size()-1; ++i){
    
    if(mid[i]!=0)
      aux0[i]=down[i]/(mid[i]-top[i-1]*aux0[i-1]);
    else{
      printf("Um dos valores no mid é zero\n");
      flag=1;
      break;
    }
  }
  
  if(flag==0){
    
    Ldown=aux0;
    Ldown.Print();
    
    for(int i=1; i<mid.size() ; ++i){
      aux1[i]=mid[i]-Ldown[i-1]*top[i-1];
    }
    Umid=aux1;
    Utop=top;
  }
}

FCmatrixBanded::FCmatrixBanded(double* a, int na,
			       double* b, int nb,
			       double* c, int nc){
  if(!a)
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));
  if(!b)
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));
  if(!c)
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));

  if(nb>na && nb>nc && nc==na){

    mid.SetEntries(nb,b);
    down.SetEntries(na,a);
    top.SetEntries(nc,c);

  }
  else if(na>nb && na>nc && nc==nb){
    
    mid.SetEntries(na,a);
    down.SetEntries(nb,b);
    top.SetEntries(nc,c);
    
  }
  else if(nc>nb && nc>na && na==nb){
    
    mid.SetEntries(nc,c);
    down.SetEntries(na,a);
    top.SetEntries(nb,b);
    
  }
  else
    throw std::invalid_argument(Form("[%s] Given non-existing pointer...!\n", __PRETTY_FUNCTION__));

  Vec aux0(down.size(), down[0]/mid[0]);
  Vec aux1(mid.size(),mid[0]);

  int flag=0;
  for(int i=1; i<mid.size()-1; ++i){
    
    if(mid[i]!=0)
      aux0[i]=down[i]/(mid[i]-top[i-1]*aux0[i-1]);
    else{
      printf("Um dos valores no mid é zero\n");
      flag=1;
      break;
    }
  }
  if(flag==0){
    Ldown=aux0;
    
    for(int i=1; i<mid.size() ; ++i){
      aux1[i]=mid[i]-Ldown[i-1]*top[i-1];
    }
    Umid=aux1;
    Utop=top;
  }
}

FCmatrixBanded::FCmatrixBanded(const FCmatrixBanded& mx):
  FCmatrixBanded(mx.down, mx.mid, mx.top){;}


/*ec& FCmatrixBanded::operator[](int i){
  
  if (i>=mid.size() || i<0)
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, mid.size()));

  double aux[mid.size()];
  
  Vec Row(mid.size(),0.);
  
  for(int j=0; j<mid.size() ; ++j){
    if(i==j){
      aux[j]=mid[i];
    }
    else if(j==i+1){
      aux[j]=top[i];
    }
    else if(j==i-1){
      aux[j]=down[i-1];
    }
    else{
      aux[j]=0;
    }
  }
  
  Row.SetEntries(mid.size(), aux);
  
  
  return Row;
  }*/


void FCmatrixBanded::operator=(const FCmatrixBanded& mx){
  
  if(this != &mx){
    down=mx.down;
    mid=mx.mid;
    top=mx.top;
    Ldown=mx.Ldown;
    Umid=mx.Umid;
    Utop=mx.Utop;
  }
  
}


FCmatrixBanded FCmatrixBanded::operator+(const FCmatrixBanded& mx){
  
  if(this->mid.size() != mx.mid.size())
      throw std::invalid_argument(Form("[%s] objects with different size...(M=%d x %d || v.M=%d x %d)!\n", __PRETTY_FUNCTION__, mid.size(),mid.size(), mx.mid.size(),mx.mid.size()));
  
  Vec a(mid.size()-1,0.);
  Vec b(mid.size(), 0.);
  Vec c(mid.size()-1, 0.);
    
  for(int i=0; i<mid.size(); ++i){

    if(i!=0)
      a[i-1]=down[i-1]+mx.down[i-1];
    
    b[i]=mid[i]+mx.mid[i];

    if(i!=mid.size()-1)
      c[i]=top[i]+mx.top[i];
    
  }
  
  return FCmatrixBanded(a,b,c);
  
}

FCmatrixBanded FCmatrixBanded::operator-(const FCmatrixBanded& mx){
  
  if(mid.size() != mx.mid.size())
    throw std::invalid_argument(Form("[%s] objects with different size...(M=%d x %d || v.M=%d x %d)!\n", __PRETTY_FUNCTION__, mid.size(),mid.size(), mx.mid.size(),mx.mid.size()));
    
  Vec a(mid.size()-1,0.);
  Vec b(mid.size(), 0.);
  Vec c(mid.size()-1, 0.);
    
  for(int i=0; i<mid.size(); ++i){

    if(i!=0)
      a[i-1]=down[i-1]-mx.down[i-1];
    
    b[i]=mid[i]-mx.mid[i];

    if(i!=mid.size()-1)
      c[i]=top[i]-mx.top[i];
    
  }
  
  return FCmatrixBanded(a,b,c);
  
}


// FALTA FAZER A MULTIPLICACAO DE MATRIZES

FCmatrixBanded FCmatrixBanded::operator*(double lambda){

  Vec a,b,c;
  a=down*lambda;
  b=mid*lambda;
  c=top*lambda;

  return FCmatrixBanded(a,b,c);
}

double FCmatrixBanded::Determinant() const{

  double dtr[mid.size()];
  dtr[0]=mid[0];

  for(int i=1; i<mid.size(); ++i){
    dtr[i]=mid[i]*dtr[i-1]-down[i-1]*top[i-1]*dtr[i-2];
  }
  
  return dtr[mid.size()-1];
}


Vec FCmatrixBanded::GetRow(int i) const{
  if (i>=mid.size() || i<0)
    throw std::invalid_argument(Form("[%s] index out of bounds...(i=%d N=%d)!\n", __PRETTY_FUNCTION__, i, mid.size()));

  double aux[mid.size()];
  Vec Row(mid.size(),0.);
  
  for(int j=0; j<mid.size() ; ++j){
    if(i==j){
      aux[j]=mid[i];
    }
    else if(j==i+1){
      aux[j]=top[i];
    }
    else if(j==i-1){
      aux[j]=down[i-1];
    }
    else{
      aux[j]=0;
    }
  }
  
  Row.SetEntries(mid.size(), aux);
  
  return Row;
}

Vec FCmatrixBanded::GetCol(int j) const{

  if(j<0 || j>=mid.size())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));
  
  double a[mid.size()];
  for(int i=0; i<mid.size() ; ++i){
    if(i==j){
      a[i] = mid[j];
    }
    else if(i==j-1){
      a[i] = top[j-1];
    }
    else if(i==j+1){
      a[i] = down[j];
    }
    else
      a[i] = 0;
  }
    
  return Vec(mid.size(), a);
}

int FCmatrixBanded::GetRowMax(int i) const{
  if(i<0 || i>=this->GetRowN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));

  int flag=0;
  Vec row(this->GetRow(i));
  double max=fabs(row[0]);
  
  for(int j=0; j<this->GetColN(); ++j){

    double x=fabs(row[j]);
    if(x > max){
      
      max = x;
      flag = j;
    }
    
  }

  return flag;
}

int FCmatrixBanded::GetColMax(int i) const{

  if(i<0 || i>=this->GetRowN())
    throw std::invalid_argument(Form("[%s] Index out of range...!\n", __PRETTY_FUNCTION__));


  int flag=0;
  Vec col(this->GetCol(i));
  double max=fabs(col[0]);
  
  for(int j=0; j<this->GetRowN(); ++j){

    double x=fabs(col[j]);
    
    if(x > max){
      
      max = x;
      
      flag = j;
    }
    
  }

  return flag;
}


void FCmatrixBanded::Print() const{

  cout << "matrix: [\n" << endl;
  for(int i=0; i<this->mid.size(); ++i)
    cout << "           " << this->GetRow(i) << endl;
  cout << "       ]" << endl;

  /*printf("Ldown\n");
  Ldown.Print();
  printf("Umid\n");
  Umid.Print();
  printf("Utop\n");
  Utop.Print();
  */
}

