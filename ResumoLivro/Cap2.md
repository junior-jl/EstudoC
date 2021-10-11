# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 2 - Types, Operators, and Expressions

Variáveis e constantes são os objetos de dados básicos manipulados em um programa.

Declarações listam as variáveis que seram usadas, seus tipos e talvez seus valores iniciais.

Operadores especificam o que é feito com as variáveis.

Expressões combinam variáveis e constantes para produzir novos valores.

O tipo de um objeto determina o conjunto de valores que este pode assumir e quais operações podem ser executadas
nele.

O padrão ANSI fez pequenas mudanças nos tipos básicos e expressões. Existem agora tipos **signed** e **unsigned**
de todos os tipos inteiros. Operações em ponto flutuante podem ser feita com precisão singular. Também
existe o tipo **long double** para precisão estendida. _String constants_ podem ser concatenadas. 
Objetos podem ser declarados como **const**, prevenindo qualquer mudança.

### Variable Names

Apesar de não ser mencionado no capítulo 1, existem algumas restrições nos nomes de variáveis e constantes
simbólicas.

- Nomes devem ser compostos por letras e dígitos, com o primeiro caractere sendo uma letra;
- O símbolo _underscore_ ( _ ) conta como uma letra, no entanto, não se deve iniciar o nome de variáveis
com este símbolo, pois rotinas de bibliotecas usam tais nomes;
- Letras maiúsculas e minúsculas são diferenciadas, portanto, **S** e **s** são dois nomes diferentes;
- Como já mencionado, é prática comum utilizar letras minúsculas em nomes de variáveis e maiúsculas para constantes;
- Palavras-chave como **if**, **else**, **int**, **float**, etc., são reservadas e não podem ser utilizadas como nomes de variáveis;

### Data Types and Sizes

Em C, existem apenas alguns tipos básicos de dados:
  
Tipo | Descrição
-----|-----
**char** | um byte único, capaz de armazenar um caractere
**int** | um inteiro, tipicamente refletindo o tamanho natural de inteiros na máquina **host**
**float** | ponto flutuante de precisão singular
**double** | ponto flutuante de precisão dupla
  
Além disso, há qualificadores que podem ser aplicados aos tipos básicos, por exemplo, **short** e **long**
se aplicam a inteiros, isto é,

```c
  short int x;
  long int y;
```

A palavra **int** pode ser omitida nessas declarações.

**short** geralmente é uma variável de 16 bits, **long** de 32 bits, com **int** variando de 16 a 32 bits
dependendo da máquina utilizada. Cada compilador pode escolher livremente tamanhos apropriados para cada
hardware. A única restrição é que **shorts** e **ints** tenham pelo menos 16 bits e **longs** 32 bits.

Os qualificadores **signed** e **unsigned** podem ser aplicados a **char** e **int**.

Números **unsigned** são sempre zero ou positivos e obedecem a lei de 2<sup>n</sup>, onde **n** é o número
de bits do tipo. Isso significa que, se **chars** possuem 8 bits, uma variável **unsigned char** aceita valores
entre 0 e 255, enquanto que **signed chars** tem valores entre -128 e 127 (numa máquina com complemento de dois).

Os _headers_ padrão **<limits.h>** e **<float.h>** contém constantes simbólicas para todos os tamanhos,
além de propriedades da máquina e compilador.

### Constants

Uma constante 
