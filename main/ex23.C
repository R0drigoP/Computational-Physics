//exercicio 23

#include<map>
#include<vector>
#include<string>
#include<cstdio>
#include<utility>

using namespace std;

vector< vector<int> > Getmatrix(int lin, int col, int **mx){

  vector< vector<int> > vec;
  //vector< vector<int> > vec(lin);

  for(int i=0; i<lin; i++){
    vector<int> aux;
    for(int j=0; j<col; j++){
      //vec[i].push_back(mx[i][j]);
      aux.push_back(mx[i][j]);
    }
    vec.push_back(aux);
  }
  return vec;
}

vector< vector<int> > Mmapfind(string c,map <string,vector< vector<int>>> Mmap){
  vector< vector<int> > v;
  v = Mmap.find(c)->second;

  return v;
}

int main(){

  map < string, vector < vector<int> >  > Mmap;
  
  vector< vector<int> > vec_A;
  vector< vector<int> > vec_B;
  vector< vector<int> > vec_C;

  int a[2][3]={
	       {2, 10, 5},
	       {3, 2, 7}
  };

  int b[3][3]={
	       {5, 1, 3},
	       {10, 1, 5},
	       {15, 1, 4}
  };

  int c[3][2]={
	       {5, 1},
	       {10, 2},
	       {15, 1}
  };

  // Matriz A
  int **A=new int *[2];
  for(int i=0;i<2;i++)
    A[i]=new int [3];

  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
      A[i][j]=a[i][j];
    }
  }

  // Matriz B
  int **B=new int *[3];                                                        
  for(int i=0;i<3;i++)                                                         
    B[i]=new int [3];                                                          
                                                                               
  for(int i=0; i<3; i++){                                                      
    for(int j=0; j<3; j++){                                                    
      B[i][j]=b[i][j];                                                         
    }                                                                          
  }

  // Matriz C
  int **C=new int *[3];                                                        
  for(int i=0;i<3;i++)                                                         
    C[i]=new int [2];                                                          
                                                                               
  for(int i=0; i<3; i++){
    for(int j=0; j<2; j++){                                                   
      c[i][j]=c[i][j];                                                         
    }                                                                          
  }                   

  vec_A = Getmatrix(2, 3, A);
  vec_B = Getmatrix(3, 3, B);
  vec_C = Getmatrix(2, 3, C);

  //******************************************
  //nao funciona pq estamos a fazer push back de um vetor de vetores num
  //vetor de vetores sem dizer para onde vai???ou talvez nao tenha tamanho
  //ou uma mistura das dua justificacoes
  /********************************************
  vector<int> aux(5,15);
  Mmap["mx_A"].push_back(aux);
  Mmap["mx_B"].push_back(vec_B);
  Mmap["mx_C"];
  */
  //funciona pq igualamos um vetor de vetores a um vetor de vetores
  Mmap["mx_A"] = vec_A;
  Mmap["mx_B"] = vec_B;
  Mmap["mx_C"] = vec_C;

  //Matrix A
  printf("**Matriz A**\n");
  for(int i=0; i<2; i++){
    for(int j=0; j<3; j++){
      printf("%d ", vec_A[i][j]);
    }
    printf("\n");
  }
    

  //wtf
  printf("**WTF_A**\n");
  vector<vector<int> > wtf = Mmapfind("mx_A", Mmap);
  
  for(int i=0; i<2; i++){                                                     
    for(int j=0; j<3; j++)                                                     
      printf("%d ", wtf[i][j]);                                                                                                                        
    printf("\n");
  }          


  return 0;
}
