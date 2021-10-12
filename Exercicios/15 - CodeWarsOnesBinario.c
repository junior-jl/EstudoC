
#include <stddef.h>

size_t countBits(unsigned value){
  
  unsigned int ones=0, lsb;
  
  while(value>0){ 
  lsb = value%2; 
  if(lsb == 1){
    ones++;
  }
  value /= 2;
  }
  return ones;
};


