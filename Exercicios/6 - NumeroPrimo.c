

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void main()
{

    setlocale(LC_ALL, "");

    int a,i,cont=0;
    //Descobrir se o número é primo


    printf("Insira um número. \n");
    scanf("%d", &a);

    // 1 2 3 5 7 11...

    for(i = 1; i <= a; i++){

      printf("O resto da divisão entre %d e %d é %d \n", a,i, a%i);
      if(a%i == 0){
         cont++;
      }
    }
    if (a == 1){
      printf("Número primo. Número de divisores = %d", cont);
    }
    else if(cont==2){
      printf("Número primo. Número de divisores = %d", cont);
    }else{
      printf("Número não é primo. Número de divisores = %d", cont);
    }

}



