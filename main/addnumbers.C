#include <cstdio> //scanf, printf

int main(){
  int n1, n2, sum = 0, i;
  scanf("%d", &n1);
  scanf("%d", &n2);

  if(n1 < n2){
    for(i = n1; i<=n2; ++i)
      sum +=i;
  }
  else{
    for(i = n1; i>=n2; --i)
      sum+=i;
  }

  printf("%d\n", sum);
  return 0;
}
