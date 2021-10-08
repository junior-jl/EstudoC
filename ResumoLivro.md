# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 1 - A Tutorial Introduction

- **Função main**

Todo programa em C precisa de uma função **main**. A execução do programa começa nesta função. **main** geralmente chama funções previamente escritas pelo usuário ou de bibliotecas. 
Em vários programas escritos em C, a primeira linha será **#include <stdio.h>**, que diz ao compilador para incluir as informações da biblioteca "standard input/output". O programa inicial no
estudo das linguagens de programação geralmente é escrever "Hello, world", em C, tem-se:

```c
#include <stdio.h>

main(){
  printf("Hello, world\n");
}
```

- **Funções, parâmetros e declarações**

A fim de comunicar dados entre funções, pode-se fornecer uma lista de **argumentos (parâmetros)**. Essa lista é escrita dentro dos parênteses após o nome da função. 
Ainda, entre as chaves, estão os _statements_ (declarações).

Dessa forma, funções são chamadas nomeando-as e em seguida listando seus parâmetros entre parênteses. Pode-se observar no exemplo anterior a função **printf** foi nomeada e
após isso, o argumento "Hello, world\n". 

**printf** é uma função de biblioteca que imprime saída, neste caso, a sequência entre aspas duplas, chamada _character string_ ou _string constant_. 

- **Sequências de escape**

O \n é uma **sequência de escape**, isto é, uma sequência de caracteres (dentro de uma _string_) que representa outro caractere ou sequência de caracteres. Abaixo, tem-se uma lista de algumas sequências de escape utilizadas em C (todas iniciam com o \).

Sequência | Representação
------------ | -------------
\n | newline
\b | backspace
\t | horizontal tab
\v | vertical tab
\" | double quotation mark (")

- **Comentários**

Tudo que estiver entre \* e *\ é ignorado pelo compilador (ou após \\ numa linha única).

- **Variáveis**

Em C, todas as variáveis devem ser declaradas antes de serem usadas. Uma declaração consiste no tipo e nome da variável, por exemplo,

```c
int variavel1, variavel2;
```

O tipo **int** significa que as variáveis listadas são inteiros, em contraste com **float**, por exemplo, que significa ponto flutuante (números que podem ter parte fracionária).

A faixa de valores que **int** e **float** podem assumir depende da máquina utilizada. É bastante comum **ints** de 16-bits (valores entre -32768 e +32767) ou 32-bits.
Um número **float** geralmente é uma quantidade de 32-bits com pelo menos seis dígitos significativos, com magnitude variando entre 10<sup>-38</sup> e 10<sup>38</sup>.

Em C, ainda existem outros tipos básicos de dados além de **int** e **float**, incluindo:
Tipo | Significado
------------ | -------------
char | character (a single bit)
short | short integer
long | long integer
double | double-precision floating point

Da mesma forma, o tamanho desses tipos depende da máquina na qual o programa está sendo executado. Ainda há _arrays_ (vetores), _structures_ e _unions_ destes tipos básicos, ponteiros para eles, e funções que os retornam.

O código abaixo imprime uma tabela de valores de temperatura Fahrenheit (de 0 a 300, variando de 20 em 20) e seu equivalente em Celsius.

```c
#include <stdio.h>
main(){
    int fahr, celsius;
    int inferior,superior,passo;
    inferior = 0;
    passo = 20;
    superior = 300;
    fahr = inferior;
    while (fahr <= superior){
        celsius = 5*(fahr - 32)/9;
        printf("%d\t%d\n", fahr, celsius);
        fahr = fahr + passo;
    }
}
```

Esse código resulta em: 

![image](https://user-images.githubusercontent.com/69206952/136628685-e96cc717-6cdb-4f14-af9a-6e2fb1381145.png)

O primeiro passo após a declaração de variáveis é passar a estas um valor (fazer o seu _assignment_), que é o que está sendo feito em:

```c
inferior = 0;
passo = 20;
superior = 300;
fahr = inferior;
```

_Statements_ individuais são terminados por ";" (_semicolon_ - ponto e vírgula).

- **Laço de repetição _while_**

Como cada linha da tabela é computada de maneira similar, foi utilizado um _loop_ (laço de repetição). O _loop **while**_ funciona da seguinte forma:

- A condição entre parênteses é testada. Se for verdadeira (**fahr** é menor ou igual a **superior**), o corpo do _loop_, os _statements_ entre as chaves são executados;
- A condição é testada novamente, caso seja verdadeira, os _statements_ são executados novamente;
- Quando o teste for falso, isto é, a variável **fahr**(que é incrementada em 20 a cada _loop_) for maior do que a variável **superior**, o laço é encerrado e a execução do programa continua no _statement_ que o sucede.

No caso do programa-exemplo, não há _statement_ posterior ao **_while_**, então, o programa encerra. 

O corpo de um laço _**while**_ pode consistir de uma ou mais declarações fechadas por chaves ou uma única declaração sem a necessidade das chaves, isto é,

```c
  while(i>j)
    i = j + 2;
```
