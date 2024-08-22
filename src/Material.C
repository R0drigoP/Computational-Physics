#include "Material.h"
#include <string>
#include <iostream>
using namespace std;

//Constructor
Material::Material(string fname, double fdens){
  cout << __PRETTY_FUNCTION__ << endl;
  name = fname;
  density = fdens;
}

//Destructor
Material::~Material(){
  cout << __PRETTY_FUNCTION__ << endl;
}

//Print
void Material::Print(){
  cout << "Name: " << name << "| Density: " << density << endl;
}

