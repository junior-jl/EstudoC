```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>


// Traduzir código de cores de resistores para valor de resistência

// Preto = 0
// Marrom = 1
// Vermelho = 2
// Laranja = 3
// Amarelo = 4
// Verde = 5
// Azul = 6
// Violeta = 7
// Cinza = 8
// Branco = 9

// Primeiro e segundo valores são dígitos
// Terceiro valor é multiplicador
// Quarto valor é tolerância



int intpow(int base, int exp){
   int i,res, aux = base;
   if(exp == 0){
      res = 1;
   }else if(exp == 1){
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


char first[255], second[255], multip[255];
int D1, D2, mult, mult1;
long int valor;

int main(){

    setlocale(LC_ALL, "");
    // Recebe primeira cor
    digito1:
    printf("Insira a primeira cor:\n");
    setbuf(stdin, 0);
    fgets(first, 255, stdin);
    first[strlen(first)-1] = '\0';
    // Laço if para identificar o primeiro dígito a partir da cor digitada
      if (strcmp(first,"Preto") == 0){
         printf("Primeira cor: Preto\n");
         D1 = 0;
      }
      else if (strcmp(first,"Marrom")  == 0){
         printf("Primeira cor: Marrom\n");
         D1 = 1;
      }
      else if (strcmp(first,"Vermelho")  == 0){
         printf("Primeira cor: Vermelho\n");
         D1 = 2;
      }
      else if (strcmp(first,"Laranja") == 0){
         printf("Primeira cor: Laranja\n");
         D1 = 3;
      }
      else if (strcmp(first,"Amarelo") == 0){
         printf("Primeira cor: Amarelo\n");
         D1 = 4;
      }
      else if (strcmp(first,"Verde") == 0){
         printf("Primeira cor: Verde\n");
         D1 = 5;
      }
      else if (strcmp(first,"Azul") == 0){
         printf("Primeira cor: Azul\n");
         D1 = 6;
      }
      else if (strcmp(first,"Violeta") == 0){
         printf("Primeira cor: Violeta\n");
         D1 = 7;
      }
      else if (strcmp(first,"Cinza") == 0){
         printf("Primeira cor: Cinza\n");
         D1 = 8;
      }
      else if (strcmp(first,"Branco") == 0){
         printf("Primeira cor: Branco\n");
         D1 = 9;
      }
      else{
         printf("Cor inválida\n");
         goto digito1;
      }
      printf("Primeiro dígito: %d\n", D1);

      // Recebe segunda cor
    digito2:
    printf("Insira a segunda cor:\n");
    setbuf(stdin, 0);
    fgets(second, 255, stdin);
    second[strlen(second)-1] = '\0';
    // Laço if para identificar o primeiro dígito a partir da cor digitada
      if (strcmp(second,"Preto") == 0){
         printf("Segunda cor: Preto\n");
         D2 = 0;
      }
      else if (strcmp(second,"Marrom")  == 0){
         printf("Segunda cor: Marrom\n");
         D2 = 1;
      }
      else if (strcmp(second,"Vermelho")  == 0){
         printf("Segunda cor: Vermelho\n");
         D2 = 2;
      }
      else if (strcmp(second,"Laranja") == 0){
         printf("Segunda cor: Laranja\n");
         D2 = 3;
      }
      else if (strcmp(second,"Amarelo") == 0){
         printf("Segunda cor: Amarelo\n");
         D2 = 4;
      }
      else if (strcmp(second,"Verde") == 0){
         printf("Segunda cor: Verde\n");
         D2 = 5;
      }
      else if (strcmp(second,"Azul") == 0){
         printf("Segunda cor: Azul\n");
         D2 = 6;
      }
      else if (strcmp(second,"Violeta") == 0){
         printf("Segunda cor: Violeta\n");
         D2 = 7;
      }
      else if (strcmp(second,"Cinza") == 0){
         printf("Segunda cor: Cinza\n");
         D2 = 8;
      }
      else if (strcmp(second,"Branco") == 0){
         printf("Segunda cor: Branco\n");
         D2 = 9;
      }
      else{
         printf("Cor inválida\n");
         goto digito2;
      }
      printf("Segundo dígito: %d\n", D2);

      // Terceiro dígito

      digito3:
      printf("Insira a terceira cor:\n");
      setbuf(stdin, 0);
      fgets(multip, 255, stdin);
      multip[strlen(multip)-1] = '\0';

       if (strcmp(multip,"Preto") == 0){
         printf("Terceira cor: Preto\n");
         mult = 0;
      }
      else if (strcmp(multip,"Marrom")  == 0){
         printf("Terceira cor: Marrom\n");
         mult = 1;
      }
      else if (strcmp(multip,"Vermelho")  == 0){
         printf("Terceira cor: Vermelho\n");
         mult = 2;
      }
      else if (strcmp(multip,"Laranja") == 0){
         printf("Terceira cor: Laranja\n");
         mult = 3;
      }
      else if (strcmp(multip,"Amarelo") == 0){
         printf("Terceira cor: Amarelo\n");
         mult = 4;
      }
      else if (strcmp(multip,"Verde") == 0){
         printf("Terceira cor: Verde\n");
         mult = 5;
      }
      else if (strcmp(multip,"Azul") == 0){
         printf("Terceira cor: Azul\n");
         mult = 6;
      }
      else if (strcmp(multip,"Violeta") == 0){
         printf("Terceira cor: Violeta\n");
         mult = 7;
      }
      else if (strcmp(multip,"Cinza") == 0){
         printf("Terceira cor: Cinza\n");
         mult = 8;
      }
      else if (strcmp(multip,"Branco") == 0){
         printf("Terceira cor: Branco\n");
         mult = 9;
      }
      else{
         printf("Cor inválida\n");
         goto digito2;
      }
      printf("Terceiro dígito: %d\n", mult);

      mult1 = intpow(10,mult);

      printf("Multiplicador: %d\n", mult1);

      if(mult < 3){
         valor = (D1*10 + D2)*mult1;
         printf("Resistência = %d\n", valor);
      }else if(mult >= 3 && mult < 6){
         valor = (D1*10 + D2)*(mult1/1000);
         printf("Resistência = %d k\n", valor);
      }
       else if(mult >= 6 && mult < 9){
         valor = (D1*10 + D2)*(mult1/1000000);
         printf("Resistência = %d M\n", valor);
      }
       else if(mult >= 9){
         valor = (D1*10 + D2)*(mult1/1000000000);
         printf("Resistência = %d G\n", valor);
      }


      goto digito1;




      }





```
