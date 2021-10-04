Write a function that takes an integer as input, and returns the number of bits that are equal to one in the binary representation of that number. You can guarantee that input is non-negative.

Example: The binary representation of 1234 is 10011010010, so the function should return 5 in this case.

```c
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

```
