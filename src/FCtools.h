#ifndef __FCtools__
#define __FCtools__
#include <vector>
#include <string>
#include "Vec.h"
using namespace std;

class FCtools{
 public:	
  static vector<string> ReadFile2String(string); //file name, returns lines
  static vector<Vec> ReadFile2Vec(string); //file name, returns vectors of Vec’s
  static Vec* ReadFile2Vecp(string, int&); //file name, returns pointer to array of Vec’s 
};
#endif 
