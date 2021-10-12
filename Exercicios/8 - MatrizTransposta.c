
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
//Definindo o tamanho da matriz
#define TAM 5
void main()
{

    setlocale(LC_ALL, "");

    // ENCONTRAR A MATRIZ TRANSPOSTA DE A
    // Basicamente trocar i e j nos loop for
    // Utilizei k para preencher a matriz (teste)
    int i,j,k=1;
    int A[TAM][TAM], B[TAM][TAM];

    printf("Insira os valores da matriz: \n");
    for(i=0;i<=TAM-1;i++){
      for(j=0;j<=TAM-1;j++){
         //scanf("%d", &A[i][j]); --- para colocar manualmente os valores da matriz, descomentar essa linha e comentar as duas próximas.
         A[i][j] = k; // Essas duas linhas preenchem automaticamente a matriz com 1 2 3 4...
         k++;
      }
    }
    printf("A = [");
    for(i=0;i<=TAM-1;i++){
      for(j=0;j<=TAM-1;j++){
          printf("%d", A[i][j]);

          if(j!=TAM-1){
          printf(" ");
          }else{
          printf("");
          }

      }
          if(i!=TAM-1){
          printf("\n     ");
          }else{
          printf("]");
          }
    }
    printf("\n \n");

    // Preenchendo matriz B
    for(i=0;i<=TAM-1;i++){
      for(j=0;j<=TAM-1;j++){
            B[i][j] = A[j][i];
      }
    }
    printf("A matriz transposta é dada por B. \n");
    printf("B = [");
    for(i=0;i<=TAM-1;i++){
      for(j=0;j<=TAM-1;j++){
          printf("%d", B[i][j]);

          if(j!=TAM-1){
          printf(" ");
          }else{
          printf("");
          }

      }
          if(i!=TAM-1){
          printf("\n     ");
          }else{
          printf("]");
          }
    }
}


