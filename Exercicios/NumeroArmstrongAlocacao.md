```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



int intpow(int base, int exp){
   int i,res, aux = base;
   if(exp == 0){
      res = 1;
   }else if(exp ==1){
      res = base;
   }
   else{
   for(i=2;i<=exp;i++){
   base = base*aux;
   res = base;
   }
}
   return res;
}

int* alocaVetor(int tamanho){

      int *aux;

      aux = (int*) malloc(tamanho*sizeof(int));
      return aux;
}


//int tam = 3;
//int digitos[TAM];

int main(){

   int numero,num, cont = 0, i;
   int res=0;
   int *digitos;

    setlocale(LC_ALL, "");
    printf("Insira o número\n");
    scanf("%d", &num);
    numero = num;


    //printf("%d", TAM);
    while(numero>0){

        numero= numero/10; // número dividido por 10
        cont++;

    }
    printf("Número de dígitos = %d\n", cont);
    digitos = alocaVetor(cont);

    numero = num;
    i = cont;
    while(numero>0){
      digitos[i-1] = numero%10;
      numero = numero/10;
      i--;
    }
    printf("Dígitos: ");
    for(i=0;i<cont;i++){
      printf("%d ", digitos[i]);
      res = res + intpow(digitos[i],cont);
    }

    printf("\nSoma = %d", res);
    printf("\nNúmero = %d", num);
    if(res == num){
      printf("\n%d é um número Armstrong, pois %d = %d", num, num, res);
    }else{
      printf("\n%d não é um número Armstrong, pois %d != %d", num, num, res);
    }

    return 0;
}

```
