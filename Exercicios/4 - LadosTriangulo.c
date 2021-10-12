

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void main()
{

    setlocale(LC_ALL, "");

    // Leia três valores (lados de um triângulo) e diga se o triângulo formado é
    // equilátero, isósceles ou escaleno.

    //Declaração de variáveis
    float L1, L2, L3;

    //Ler valores
    printf("Insira o valor do lado 1 \n");
    scanf("%f", &L1);
    printf("Insira o valor do lado 2 \n");
    scanf("%f", &L2);
    printf("Insira o valor do lado 3 \n");
    scanf("%f", &L3);

    //Condições
      //Equilátero
      if (L1 == L2 && L1 == L3){

         printf("O triângulo formado pelos lados %.2f, %.2f e %.2f é equilátero.", L1, L2, L3);
      //Isósceles
      }else if((L1 == L2 && L1 != L3) || (L1 != L2 && L1 == L3) || (L1 != L2 && L2 == L3) ){
         printf("O triângulo formado pelos lados %.2f, %.2f e %.2f é isósceles.", L1, L2, L3);
      //Escaleno
      }else{
         printf("O triângulo formado pelos lados %.2f, %.2f e %.2f é escaleno.", L1, L2, L3);
      }


}

