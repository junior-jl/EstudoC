If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.

Finish the solution so that it returns the sum of all the multiples of 3 or 5 below the number passed in. Additionally, if the number is negative, return 0 (for languages that do have them).

Note: If the number is a multiple of both 3 and 5, only count it once.



```c
int solution(int number) {
		// code here
    int soma = 0, i;
    if(number>0){
      for(i=number-1;i>0;i--){
        if((i%3 == 0)||(i%5 == 0)){
          soma = soma + i;
        }
      } 
    }else{
      soma = 0;
    }
    return soma;
}
```
