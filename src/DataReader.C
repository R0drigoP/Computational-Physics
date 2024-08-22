#include "DataReader.h"
#include <fstream>
#include <cstdio>
#include <iostream>
#include "TMultiGraph.h"

using namespace std;

/*DataReader::DataReader(string name){
  filename = name;
  //file.open(name);
  }*/

/*DataReader::~DataReader(){
  file.close();
  }*/

/*vector<string> split(const string s, const char c){
  string buff = "";
  vector<string> vec;

  for(auto n:s){
    if(n != c)
      buff += n;
    else if(n==c && buff != ""){
      vec.push_back(buff);
      buff = "";
    }
  }
    if(buff != "")
      vec.push_back(buff);

    return vec;
    }*/

/*vector<vector<string>> DataReader::GetData(){
  ifstream file(filename);
  string line;
  while(getline(file, line)){
    vector<string> aux;
    aux = split(line, ",");
    this->data.push_back(aux);
  }

  file.close();

  return this->data;
  }*/

/*vector<vector<string>> DataReader::GetData(){
  ifstream file(filename);
  string value, line;
  vector<string> aux;
  while(file.good()){
    while(getline(file, line)){
      getline(file, value, ',');
      aux.push_back(value);
      //cout << value << endl;
    }
    data.push_back(aux);
  }

  return data;
  }*/


/*TMultiGraph* DataReader::DisplayData(string KIND, vector<string> COUNTRIES, string OPTION){
  ifstream file(filename);
  TMultiGraph *mg = new TMultiGraph();

  return mg;
}*/
  

void DataReader::Print() const{
}



