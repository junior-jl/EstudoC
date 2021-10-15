# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 4 - Functions and Program Structure

Funções quebram grandes tarefas de computação em tarefas menores, e permitem a outras pessoas construírem a partir de programas anteriores, ao invés de começar do zero. Funções apropriadas "escondem" detalhes de operação de partes do programa que "não precisam saber" sobre isso, clarificando o todo e facilitando mudanças.

C foi projetado para tratar funções de maneira eficiente e simples; programas em C geralmente consistem de muitas pequenas funções em vez de poucas grandes. A declaração e definição de funções, como já discutido, foi a área com mudanças mais visíveis no C pelo padrão ANSI. É possível declarar os tipos dos argumentos quando a função é declarada. Além disso, quando argumentos são declarados apropriadamente, as transformações de tipo são realizadas automaticamente.

O padrão deixa claro regras na questão de nomes; em particular, é necessário que haja apenas uma definição de cada objeto externo. 

### Basic of Functions

Iniciando, vamos projetar e escrever um programa para imprimir cada linha de sua entrada que contenha um "padrão" particular ou _string_ de caracteres. Por exemplo, procurando pelo padrão de letras "ould" no conjunto de linhas

```
  Ah Love! could you and I with Fate conspire
  To grasp this sorry Scheme of Things entire,
  Would not we shatter it to bits -- and then
  Re-mould it nearer to the Heart's Desire!
```

produz a saída

```
  Ah Love! could you and I with Fate conspire
  Would not we shatter it to bits -- and then
  Re-mould it nearer to the Heart's Desire!
```

Assim, este trabalho, nitidamente, divide-se em três partes:

```c
  while (existir outra linha)
    if (a linha contém o padrão)
      imprima-a
```

Apesar de ser possível colocar todo o código para isso em **main**, lidar com três partes pequenas é mais simples do que lidar com uma única maior, pois detalhes irrelevantes podem ser colocados nas funções, diminuindo a chance de interações indesejadas. Além de que tais partes podem ser úteis em programas diferentes.

"Enquanto existir outra linha" é **getline**, uma função escrita no capítulo 1, e "print it" é **printf**, que já foi fornecida por alguém. Assim, só é necessário escrever a rotina para decidir se a linha contém ou não o padrão.

Pode-se resolver esse problema escrevendo uma função **strindex (s,t)** que retorna a posição (ou índice) na **string s** na qual a **string t** começa, ou -1 caso **s** não contenha **t**. Tendo em vista que vetores em C iniciam na posição zero, os índices serão zero ou positivo, logo, um valor negativo é conveniente para sinalizar falha. O programa pode ser escrito como mostrado abaixo:

```c
#include <stdio.h>
#define MAXLINE 1000 // máximo comprimento da linha de entrada

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould"; // padrão a ser procurado

//Procurar todas as linhas com o padrão

main()
{
    char line[MAXLINE];
    int found = 0;

    while (getline(line, MAXLINE) > 0)
        if (strindex(line, pattern) >= 0)
        {
            printf("%s", line);
            found++;
        }
    return found;
}

//getline: recebe a linha em s, retorna seu comprimento
int getline(char s[], int lim) 
{
    int c, i;

    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        s[i++] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0'; 
    return i; 
}

//strindex: retorna o índice de t em s, -1 se não achar
int strindex (char s[], char t[]) 
{
    int i, j, k;

    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            return i;
    }
    return -1;
}

```

Cada definição de função tem a forma

```
tipo-de-retorno nome-função (declaração-de-argumentos)
{
  declarações e statements
}
```

Várias partes podem ser omitidas; uma função mínima é

```
  dummy() {}
```

que não faz nem retorna nada. Uma função que não faz nada pode ser útil como um marcador de posição durante um programa de desenvolvimento. Se o tipo de retorno é omitido, é assumido que seja **int**. 

Um programa é apenas um conjunto de definições de variáveis e funções. A comunicação entre funções é pelos argumentos e valores retornados, além de variáveis externas. As funções podem aparecer em qualquer ordem no arquivo fonte, e o programa fonte pode ser dividido em vários arquivos, contanto que nenhuma função seja dividida.

O _statement_ **return** é o mecanismo para retornar um valor da função chamada àquela que a chamou. Qualquer expressão pode seguir um **return**:

```c
  return expressão;
```

A expressão será convertida no tipo de retorno da função se for necessário. Geralmente, são utilizados parênteses ao redor de expressão, porém podem ser omitidos.

A função "chamadora" é livre para ignorar o valor retornado. Além disso, não é necessário que exista uma expressão depois de **return**; neste caso, nenhum valor é retornado. Além disso, o controle também retorna para a função de chamada sem valor quando a execução "cai para o final" da função chegando a uma chave }. Não é ilegal, mas é provavelmente um sinal de problema se uma função retorna um valor para um lugar e nenhum valor para outro. Em todo caso, se uma função falha em retornar valor, seu "valor" será lixo.

Os mecanismos para compilar e carregar um programa em C compostos por múltiplos arquivos fonte dependem do sistema. No sistema UNIX, o comando **cc** é utilizado. Supondo que as três funções são armazenadas em diferentes arquivos chamados **main.c, getline.c** e **strindex.c**. O comando

```
cc main.c getline.c strindex.c
```

compila os três arquivos, colocando o código objeto resultante nos arquivos **main.o, getline.o** e **strindex.o**, assim carregando todas num arquivo executável **a.out**.  O comando **cc** utiliza ".c" e ".o" para diferenciar arquivos fonte de arquivos objeto.
