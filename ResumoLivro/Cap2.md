# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 2 - Types, Operators, and Expressions

<div align="justify">
 


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

Uma constante inteira como 1234 é um **int**. Uma constante **long** é escrita com um **l** (éle) ou **L** no final, como 123456789L; um inteiro grande demais para ser acomodado num **int** é tomado como **long**. Constantes **unsigned** são escritas com um **u** ou **U** no final, e o sufixo **ul** ou **UL** indica **unsigned long**.

Constantes de ponto flutante contém um ponto decimal (12.34), um expoente (1e-2), ou ambos; seu tipo é **double**, a não ser que seja sufixado. Os sufixos **f** ou **F** indicam uma constante **float**; **l** ou **L** indicam um **long double**.

O valor de um inteiro pode ser especificado em octal ou hexadecimal, ao invés de decimal:

- Um **0** (zero) no início de uma constante inteira significa octal.

Por exemplo, 31 = 037;

- Um **0X** no início indica hexadecimal.

Por exemplo, 31 = 0X1F ou 0X1f.

Constantes escritas em código octal ou hexadecimal também podem ser seguidas de **L** ou **U** para serem lidos como **long** ou **unsigned**, respectivamente. **0XFUL** é uma constante **unsigned long** com valor 15<sub>10</sub>.

- **_Character constant_**: é um inteiro escrito como um caractere entre aspas simples. Seu valor é o valor numérico de tal caractere no conjunto de caracteres da máquina (geralmente o código ASCII). Por exemplo, a **_character constant_** '0' tem valor 48.

Alguns caracteres podem ser representados por _string constants_ como as sequências de escape já mencionadas. Além disso, um padrão binário arbitrário de tamanho de um byte pode ser especificado como **'\ooo'** onde **ooo** representa um a três dígitos octais (0...7) ou por **'\xhh'** onde **hh** representa um ou mais dígitos hexadecimais (0...F). Dessa forma, pode-se escrever

```c
#define VTAB '\013' // Vertical Tab ASCII 
#define BELL '\077 // Caractere de sino ASCII 
```

```c
#define VTAB '\xb' // Vertical Tab ASCII (hexadecimal)
#define BELL '\x7' // Caractere de sino ASCII (hexadecimal)
```

A _character constant_ '\0' representa o caractere de valor zero (_null character_). É geralmente escrito como '\0' para enfatizar a natureza de caractere de alguma expressão, porém seu valor numérico é simplesmente 0.

Uma **_constant expression_** é uma expressão que envolve somente constantes. Tais expressões podem ser avaliadas durante a compilação ao invés de durante a execução, podendo ser utilizadas em qualquer lugar como uma constante, por exemplo

```c
#define MAXLINE 1000
char line[MAXLINE + 1];
```

Uma **_string constant_** ou **_string literal_** é uma sequência de zero ou mais caracteres fechados por aspas duplas, como

```c
"Eu sou uma string"
```

ou 

```c
"" // a string vazia.
```

As aspas não fazem parte da _string_, servem apenas para delimitá-la. As mesmas sequências de escape utilizadas em caracteres servem para strings e **\"** representa o caractere da aspa dupla. Além disso, _string constants_ podem ser concatenadas, assim

```c
"Hello," " world"
```

é equivalente a 

```c
"Hello, world"
```

Esse fato é útil quando é necessário separar _strings_ longas em várias linhas fonte.

Tecnicamente, uma _string constant_ é um vetor de caracteres. A representação interna de uma _string_ possui um caractere nulo '\0' no final, assim, o armazenamento físico necessário é o número de caracteres escrito entre aspas mais um. Essa representação significa que não há limite para o comprimento de uma _string_, mas programas podem percorrer uma _string_ completamente para determinar seu tamanho. A função **strlen(s)** da biblioteca padrão **<string.h>**  retorna o comprimento de seu argumento **s** (uma _character string_) excluindo o '\0' terminal.

Assim, um programa que retorna o comprimento de uma string **s** é:
 
 ```c
 int strlen(char s[]){
  int i;
 
 i = 0;
 while (s[i] != '\0')
  ++i;
 return i;
 }
 
 ```
 
É importante distinguir entre uma _string_ e uma _character constant_ que possui um único caractere, isto é, 'x' não é o mesmo que "x". O primeiro é um inteiro, utilizado para produzir o valor numérico da letra **x** no conjunto de caracteres da máquina. O último é um vetor de caracteres que contém um único caractere (x) e um '\0'.
 
Existe ainda outro tipo de constante, a _**enumeration constant**_
 
 
  </div>
