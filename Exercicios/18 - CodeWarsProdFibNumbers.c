
#include <stdlib.h>
#include <stdio.h>

typedef unsigned long long ull;

unsigned long long* productFib(ull prod) {
  
  ull f0=0,f1=1,teste=0,aux;
  static ull res[3];
  
  while(f1*f0<=prod){
    if(f0*f1 == prod){
      teste = 1;
      break;
    }
    aux = f0;
    f0=f1;
    f1+=aux;
    
    
  }
  res[0] = f0;
  res[1] = f1;
  res[2] = teste;
  return res;
  
}

