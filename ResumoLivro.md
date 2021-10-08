# The C Programming Language - Ritchie and Kernighan (2nd edition)

Todo programa em C precisa de uma função **main**. A execução do programa começa nesta função. **main** geralmente chama funções previamente escritas pelo usuário ou de bibliotecas. 
Em vários programas escritos em C, a primeira linha será **#include <stdio.h>**, que diz ao compilador para incluir as informações da biblioteca "standard input/output". O programa inicial no
estudo das linguagens de programação geralmente é escrever "Hello, world", em C, tem-se:

```c
#include <stdio.h>

main(){
  printf("Hello, world\n");
}
```

A fim de comunicar dados entre funções, pode-se fornecer uma lista de **argumentos (parâmetros)**. Essa lista é escrita dentro dos parênteses após o nome da função. 
Ainda, entre as chaves, estão os _statements_ (declarações).

Dessa forma, funções são chamadas nomeando-as e em seguida listando seus parâmetros entre parênteses. Pode-se observar no exemplo anterior a função **printf** foi nomeada e
após isso, o argumento "Hello, world\n". 

**printf** é uma função de biblioteca que imprime saída, neste caso, a sequência entre aspas duplas, chamada _character string_ ou _string constant_. 
O \n é uma **sequência de escape**, isto é, uma sequência de caracteres (dentro de uma _string_) que representa outro caractere ou sequência de caracteres. Abaixo, tem-se uma lista de algumas sequências
de escape utilizadas em C (todas iniciam com o \).

Sequência | Representação
------------ | -------------
\n | newline
\b | backspace
\t | horizontal tab
\v | vertical tab
\" | double quotation mark (")
