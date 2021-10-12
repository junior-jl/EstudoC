/*
This program should read the .md files that I write in EstudoC/Exercicios and take away the text part and create a new file containing
only the code that is enclosed by ```c ```
*/

int* alocaVetor(int tamanho){

      int *aux;

      aux = (int*) malloc(tamanho*sizeof(int));
      return aux;
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define IN 1
#define OUT 0

int main(){

    int i;
    char nomeArquivo[255];
    char *nomeArquivo1, *nomeArquivo2;
    int c, contagem = 17;

    printf("Oi. Insira o nome do arquivo .md sem a extensao. Sera criado um arquivo com o mesmo nome e extensao .c\n");
    printf("excluindo quaisquer textos antes do codigo, alem das crases que envolvem o codigo\n");
    setbuf(stdin,0);
    fgets(nomeArquivo,255,stdin);

    nomeArquivo1 = alocaVetor((strlen(nomeArquivo) + 4));
    nomeArquivo2 = alocaVetor((strlen(nomeArquivo) + 3));
    //printf("Strlen nA: %d\n", strlen(nomeArquivo));
    //printf("Strlen nA1: %d\n", strlen(nomeArquivo1));
    //printf("Strlen nA2: %d\n", strlen(nomeArquivo2));
    for(i = 0; i < strlen(nomeArquivo) - 1; ++i){
        //printf("nomeArquivo2[%d] (%c) = nomeArquivo[%d] (%c)\n", i, nomeArquivo2[i], i, nomeArquivo[i]);
        nomeArquivo2[i] = nomeArquivo[i];
    }

        nomeArquivo2[i] = '.';
        //printf("nomeArquivo2[%d] = %c\n", i, nomeArquivo2[i]);
        ++i;
        nomeArquivo2[i] = 'c';
        //printf("nomeArquivo2[%d] = %c\n", i, nomeArquivo2[i]);
        ++i;
        nomeArquivo2[i] = '\0';
        //printf("nomeArquivo2[%d] = %c\n", i, nomeArquivo2[i]);

    //nomeArquivo2 = nomeArquivo;
    for(i = 0; i < strlen(nomeArquivo) - 1 ; ++i){
        //printf("nomeArquivo1[%d] (%c) = nomeArquivo[%d] (%c)\n", i, nomeArquivo1[i], i, nomeArquivo[i]);
        nomeArquivo1[i] = nomeArquivo[i];
    }

        nomeArquivo1[i] = '.';
        //printf("nomeArquivo1[%d] = %c\n", i, nomeArquivo1[i]);
        ++i;
        nomeArquivo1[i] = 'm';
        //printf("nomeArquivo1[%d] = %c\n", i, nomeArquivo1[i]);
        ++i;
        nomeArquivo1[i] = 'd';
        //printf("nomeArquivo1[%d] = %c\n", i, nomeArquivo1[i]);
        ++i;
        nomeArquivo1[i] = '\0';
        //printf("nomeArquivo1[%d] = %c\n", i, nomeArquivo1[i]);

    /*
    i = 0;
    while ((c = nomeArquivo2[i]) != '\0'){
        putchar(c);
        ++i;
    }
    i = 0;
    printf("\n");
    while ((c = nomeArquivo1[i]) != '\0'){
        putchar(c);
        ++i;
    }
    */
    int state = OUT; // cursor que percorre cada letra
    FILE *file; // arquivo a ser lido
    FILE *file2; // arquivo a ser escrito
    file = fopen(nomeArquivo1, "r"); // abre o arquivo no diretório escolhido para leitura
    file2 = fopen(nomeArquivo2, "w"); // abre o arquivo no diretório escolhido para escrita
    if (file){
        while((c=getc(file)) != EOF){ // enquanto o char cursor for diferente do fim do arquivo (EOF)
            if(c == '`'){ // se o char lido for a crase
                if(state == OUT){ // se o estado ainda for OUT, i.e., se ainda estiver fora do código
                    while((c = getc(file)) == '`' || c == 'c') // enquanto o caractere lido seja uma crase ou um 'c'
                        c = '\b'; // apaga o caractere
                    state = IN; // quando acabar, o estado é IN, ou seja, estamos lendo dentro do codigo agora
                }
                else{
                    state = OUT; // caso o caractere lido seja um '`', mas o estado é IN, estado recebe OUT
                }
            }
            if(state == OUT)
                c = '\b'; // sempre que state for OUT, apaga
            else
                //printf("%c",c);
                //putchar(c);
                putc(c,file2);
    }
    fclose(file); // fecha o arquivo
    fclose(file2);
    }


    return 0;
}
