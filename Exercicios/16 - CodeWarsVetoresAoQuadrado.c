
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

bool testaDiferente(unsigned int j, unsigned int* jafoi){
  unsigned int i, aux=0, n;
  n = sizeof(jafoi)/sizeof(int);
  for(i=0;i<n;i++){
    if(j!=jafoi[i]) aux++;
  }
  
  if(aux == n){
    return true;
  }else{
    return false;
  }
}


bool comp(const int *a, const int *b, size_t n)
{
    unsigned int i,j,cont=0,jafoi[n];
    for(i=0;i<n;i++){
      jafoi[i] = n+1;
    }
    
    if(n==0){
      return false;
    }else{
    for(i=0;i<n;i++){ 
      for(j=0;j<n;j++){
        if(testaDiferente(j,jafoi)){
        if((b[i]==(a[j]*a[j]))){
          
          
          cont++;
          break;
          }
          
        }else{continue;}
      }
      jafoi[i] = j;
      
    }
    if(cont==n){
      return true;
    }else{
      return false;
    }
    }
}

