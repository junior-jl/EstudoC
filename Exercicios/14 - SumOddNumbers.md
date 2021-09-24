Given the triangle of consecutive odd numbers:

                  1
             
               3     5
          
            7     9    11
       
        13    15    17    19
   
    21    23    25    27    29

...

Calculate the sum of the numbers in the nth row of this triangle (starting at index 1) e.g.: (Input --> Output)

1 -->  1

2 --> 3 + 5 = 8

```c
#include <inttypes.h>

uint64_t rowSumOddNumbers(uint32_t n)
{
    uint32_t first, i;
    uint64_t sum = 0;
    first = n*(n-1) -1;
    for (i=0;i<n;i++){
      first += 2;
      sum += first;
    }
    return sum;
}
```
