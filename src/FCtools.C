#include <fstream> 
#include <vector>
#include <sstream>
#include <iostream>
#include "FCtools.h"
#include "Vec.h"

using namespace std;


vector <string> FCtools::ReadFile2String (string filename){
    string line;
    vector <string> vec;
    fstream file;
    
    file.open (filename, ios::in);
    if (!file){
        cout << "ERROR OPENING FILE! " << endl;
        exit (EXIT_FAILURE);
    }
    cout << "FILE OPEN" << endl;
    while (getline (file, line)){
        //cout << "reading " << endl;
        vec.push_back(line);
       
    }
    file.close();
    
    //for (int i=0; i<5; i++)
    //    cout << vec[i] << endl;
    return vec;

}
vector <Vec> FCtools::ReadFile2Vec(string filename){
    fstream file;
    vector <Vec> vec;
    Vec temp;
    vector <double> t;
    string line;
    stringstream ss;
    double * array;
    file.open(filename, ios::in);
    if (!file){
        cout << "ERROR OPENING FILE! " << endl;
        exit (EXIT_FAILURE);
    }
    cout << "FILE OPEN" << endl;
    int c;
    double n;
    while (getline(file,line)){
        //cout << "reading  "  << endl;
        c = 1;
        stringstream stream (line);
        int i = 0;
        while (stream >> n){
            t.push_back (n);
            ++i;
        }
        if (c == 1){
            array = new double [i];
            for (int j = 0; j<i; j++){
                array[j] = t[j]; 
                //cout << array[j] << "  " ;
            }
            temp.SetEntries(i, array);
            delete []array;
        }
        vec.push_back(temp);
        t.clear();
    }
    file.close();
    return vec;
}

Vec* FCtools::ReadFile2Vecp(string filename, int& n){
    Vec * v;
    fstream file;
    vector <Vec> vec;
    vector <double> t;
    string line;
    stringstream ss;
    double * array;
    double d = 0;
    int c = 0;
    
    file.open(filename, ios::in);
    if (!file){
        cout << "ERROR OPENING FILE! " << endl;
        exit (EXIT_FAILURE);
    }
    cout << "FILE OPEN" << endl;
    Vec temp;
    while (getline(file, line)){
        //cout << "reading  " << endl;
        ss << line;
        int i = 0;
	while (ss >> d) {
	  t.push_back (d);
	  ++i;
	}

	ss.clear();
        array = new double [i];
        //cout << "print do array na fctools" << endl;
        for (int j = 0; j<i; j++){
	  array[j] = t[j];
	  //cout << array[j] << "  " ;
        }
        
        t.clear();
	temp.SetEntries(i, array);
        delete []array;
        vec.push_back (temp);
        //cout << "vec dentro do while:" << endl;
        //vec[c].Print();
        c++;
	
    }
    v = new Vec [c];
    //cout << "v fora do while:" << endl;
    for (int j = 0; j<c; j++){
      v[j] = vec.at(j);
      //v[j].Print();
    }
    file.close();
    
    return v;
}


