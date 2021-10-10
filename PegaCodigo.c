/*
This program should read the .md files that I write in EstudoC/Exercicios and take away the text part and create a new file containing
only the code that is enclosed by ```c ```
*/

#include<stdio.h>

#define IN 1
#define OUT 0

int main(){

    int c,state = OUT; // cursor que percorre cada letra
    FILE *file; // arquivo a ser lido
    FILE *file2; // arquivo a ser escrito
    file = fopen("Codigo.txt", "r"); // abre o arquivo no diretório escolhido para leitura
    file2 = fopen("CodigoNovo.txt", "w"); // abre o arquivo no diretório escolhido para escrita
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
    fclsoe(file2);
    }
    return 0;
}
