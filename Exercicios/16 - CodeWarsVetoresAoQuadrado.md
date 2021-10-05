Given two arrays a and b write a function comp(a, b) (orcompSame(a, b)) that checks whether the two arrays have the "same" elements, with the same multiplicities. "Same" means, here, that the elements in b are the elements in a squared, regardless of the order.

Examples
Valid arrays
a = [121, 144, 19, 161, 19, 144, 19, 11]  
b = [121, 14641, 20736, 361, 25921, 361, 20736, 361]
comp(a, b) returns true because in b 121 is the square of 11, 14641 is the square of 121, 20736 the square of 144, 361 the square of 19, 25921 the square of 161, and so on. It gets obvious if we write b's elements in terms of squares:

a = [121, 144, 19, 161, 19, 144, 19, 11] 
b = [11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19]
Invalid arrays
If, for example, we change the first number to something else, comp may not return true anymore:

a = [121, 144, 19, 161, 19, 144, 19, 11]  
b = [132, 14641, 20736, 361, 25921, 361, 20736, 361]
comp(a,b) returns false because in b 132 is not the square of any number of a.

a = [121, 144, 19, 161, 19, 144, 19, 11]  
b = [121, 14641, 20736, 36100, 25921, 361, 20736, 361]
comp(a,b) returns false because in b 36100 is not the square of any number of a.

Remarks
a or b might be [] or {} (all languages except R, Shell).
a or b might be nil or null or None or nothing (except in C++, Elixir, Haskell, PureScript, Pascal, Perl, R, Rust, Shell).
If a or b are nil (or null or None, depending on the language), the problem doesn't make sense so return false.

Note for C
The two arrays have the same size (> 0) given as parameter in function comp.

```c
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
```
