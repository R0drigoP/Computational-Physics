//fdoublev

double ***fdoublev(int n_0,int n_1=1,int n_2=1) {

  double ***v=new double **[n_0];
  
  for(int i=0;i<n_0;i++){

    v[i]= new double *[n_1];
    
    for(int j=0;j<n_1;j++){
      
      v[i][j]=new double [n_2];
     
    }
    
  }

  return v;
  
}
