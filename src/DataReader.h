#ifndef __DataReader__
#define __DataReader__

#include <vector>
#include <string>
#include <fstream>
#include "TMultiGraph.h"
#include <vector>

using namespace std;

class DataReader{
 private:
  string filename;
  //string delimeter; //virgula no caso de .csv file
  //ifstream file;
  vector<vector<string>> data;
  

 public:
 DataReader(string name = "", string delim = ",") : filename(name) {;}
  ~DataReader(){;}
  //const vector<string> split(const string s, const char c);
  //vector<vector<string>> GetData();
  //KIND: "cases", deaths" || Countries: "ALL" or {"PT, "FR", ... } || OPTION: "daily, "cumulative"
  //TMultiGraph* DisplayData(string, vector<string>, string OPTION = "daily");
  void Print() const;
};

#endif
