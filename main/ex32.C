#include "segment.h"
#include <vector>
#include <utility>
#include <iostream>
#include <cstdio>

using namespace std;

int main(){
  vector<pair<float, float>> v{{2.3, 5.2}, {2.8, 4.5}};
  segment s1(v);
  s1.Dump();

  segment s2(s1);
  s2.Dump();

  segment s3;
  s3.Dump();
  s3 = s1;
  s3.Dump();

  segment sx;
  sx.Add(1., 1.);
  sx.Add(2.8, 3.2);
  sx.Dump();
  sx.Replace(1, 4.2, 1.3);
  sx.Dump();

  /*vector<segment*> vs;
  vs.push_back(&s1);
  vs[0]->Dump();
  
  segment y1;
  y1 = move(*vs[0]);
  y1.Dump();
  */

  vector<segment> vs;
  vs.push_back(segment(v));
  vs[0].Dump();
  
  segment y1;
  y1 = move(vs[0]);
  y1.Dump();
  return 0;
}
