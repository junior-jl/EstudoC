
#include<stdio.h>
#include<stdlib.h>
#include<locale.h>

void main(){

    setlocale(LC_ALL, "");

    //Crie um algoritmo que leia duas notas e mostre a média entre elas;
    float n1,n2,media;

    printf("Insira a primeira nota.\n");
    scanf("%f",&n1);
    printf("Insira a segunda nota.\n");
    scanf("%f",&n2);
    media = (n1 + n2)/2;
    printf("A média entre as notas é: %.2f", media);

}

