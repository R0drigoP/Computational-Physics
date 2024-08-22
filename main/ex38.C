#include"PixelDet.h"
#include <cstdio>
int main(){

  vector<int> vet_a;
  vector<int> vet_b;
  PixelDet tab(100,100);
  vet_a=tab.EventNoise(0.005);

  for(int i=0;i<vet_a.size();i++){
    //printf("hello_1\n");
    printf("%d ",vet_a[i]);
  }
  printf("\n--------Exercicio (a) done!!!\n");

  float coo[2] = {30, 30};
  vet_b=tab.EventSignal(coo, 10);
  for(int i=0; i<vet_b.size(); ++i)
    printf("%d ", vet_b[i]);
  printf("\n--------Exercicio (b) done!!!\n");

  TCanvas* c = tab.DrawEvent(vet_b);
  
  return 0;
}
