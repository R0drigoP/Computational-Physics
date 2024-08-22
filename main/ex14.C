#include<cstdio>

int ***fintv(int,int=1,int=1);
double ***fdoublev(int,int=1,int=1);

void printdouble(double ***v,int a, int b=1, int c=1){
  
   for(int i=0; i<a; i++){
    for(int j=0; j<b; j++){
      for(int k=0; k<c; k++){
	printf("%lf ",v[i][j][k]);
      }
    }
  }
  
}
void printint(int ***v,int a, int b=1, int c=1){
  
   for(int i=0; i<a; i++){
    for(int j=0; j<b; j++){
      for(int k=0; k<c; k++){
	printf("%d ",v[i][j][k]);
	if(k%(c+1)){
	  printf("\n");
	}
      }
    }
  }
  
}

int main(){

  int ***a = fintv(100,50);
  double ***b = fdoublev(100,50,20);
  double ***c = fdoublev(100,50);
  
  for(int i=0; i<100; i++){
    for(int j=0; j<50; j++){
      for(int k=0; k<1; k++){
	a[i][j][k]=1;
      }
    }
  }
  for(int i=0; i<100; i++){
    for(int j=0; j<50; j++){
      for(int k=0; k<20; k++){
	b[i][j][k]=5;
      }
    }
  }
  for(int i=0; i<100; i++){
    for(int j=0; j<50; j++){
      for(int k=0; k<1; k++){
	c[i][j][k]=5.1;
      }
    }
  }

  printint(a,100,50);
  printdouble(b,100,50,20);
  printdouble(c,100,50);
  
  
  //delete
  delete **a;
  delete *a;
  delete a;
  delete **b;
  delete *b;
  delete b;
  delete **c;
  delete *c;
  delete c;

  return 0;
}
