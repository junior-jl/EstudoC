
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define TAM 255

int intpow(int base, int exp){
   int i,res, aux = base;
   if(exp == 0){
      res = 1;
   }else{

   for(i=2;i<=exp;i++){
   base = base*aux;
   res = base;
   }
}
   return res;
}


int numero,num, cont = 0, i;
int res=0;
//int tam = 3;
int digitos[TAM];


int main(){

    setlocale(LC_ALL, "");
    printf("Insira o número a ser analisado: \n");
    scanf("%d", &num);
    numero = num;


    //printf("%d", TAM);
    while(numero>0){
        digitos[cont] = numero%10; // Guardando digitos no vetor (de trás pra frente)
        numero= numero/10; // número dividido por 10
        cont++;
        //printf("%d\n", numero);
    }

    int digitosAux[cont];
    for(i=0; i<cont; i++){
      digitosAux[i] = digitos[i];
    }
    size_t n = sizeof(digitosAux)/sizeof(digitosAux[0]);
    printf("%d\n", n);
    printf("Dígitos da direita para a esquerda:  ");
   //354/10 = 35*10 + 4 ; 35/10 = 3*10 + 5
   for(i=0; i< n ; i++){
      printf("%d  ", digitosAux[i]);
   }

   for(i=0; i< n ; i++){
      printf("\n%d ^ %d = %d \n", digitos[i], n, intpow( digitos[i], n));
      res =  res +  intpow( digitos[i], n);
      //printf("Res: %d\n", res);


   }

    printf("Soma = %d\n", res);
    printf("Número = %d\n", num);
    if(res == num){
      printf("%d é um número Armstrong, pois %d = %d", num, num, res);
    }else{
      printf("%d não é um número Armstrong, pois %d != %d", num, num, res);
    }
    return 0;
}

