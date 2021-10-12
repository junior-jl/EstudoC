
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

