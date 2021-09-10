```c
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void main(){

    setlocale(LC_ALL, "");

    //Crie um algoritmo que dê a diferença entre duas notas (valor absoluto)
    float n1,n2,dif;

    printf("Insira a primeira nota.\n");
    scanf("%f",&n1);
    printf("Insira a segunda nota.\n");
    scanf("%f",&n2);
    dif = fabs(n1 - n2);
    printf("A diferença entre as duas notas é %.2f", dif);

}
```
