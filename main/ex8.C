#include <cstdio> //printf, scanf

int fact(int n){

  if(n==0 || n==1)
    return 1;
  else
    return n*fact(n-1);
}

int main(){
  int n, result;
  scanf("%d", &n);
  result = fact(n);
  printf("%d! = %d\n", n,  result);
  return 0;
}
