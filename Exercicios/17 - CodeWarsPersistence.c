
persistence(39) === 3;
//     because 3*9 = 27, 2*7 = 14, 1*4 = 4
//         and 4 has only one digit

persistence(999) === 4;
//     because 9*9*9 = 729, 7*2*9 = 126, 1*2*6 = 12,
// and finally 1*2 = 2
                
persistence(4) === 0;
//     because 4 is already a one-digit number




#include <stdlib.h>
#include <stdio.h>

int* alocaVetor(int tamanho){
      int *aux;
      aux = (int*) malloc(tamanho*sizeof(int));
      return aux;
}
int persistence(int n) {
    int i, aux, aux2, mult, j, cont;
    int* digitos;
    cont=0;
    while(n>9){
    aux2=n;
    aux=n;
    mult=1;
    i=0; 
    while(aux2>0){
      aux2/=10;
      i++; 
    }
    int tamanho = i;
    digitos = alocaVetor(tamanho);
    i=0;
    while(aux>0){
      digitos[i] = aux%10;
      i++;
      aux/=10;
    }
    
    for(j=0;j<tamanho;j++){
    mult = mult*digitos[j];
      }
      n = mult;
      cont++;
    }
        return cont;       
}


Another user code (I thought about something similar, but didn't work that way, but this solution is WAAAY simpler!)


int persistence(int n)
{
    int aux, cont = 0;
    while (n > 9) {
        ++cont;
        aux = n % 10;
        while (n /= 10)
            aux *= n % 10;
        n = aux;
    }
    return cont;
}

