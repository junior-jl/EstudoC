# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 2 - Types, Operators, and Expressions

<div align="justify">
  
Variáveis e constantes são os objetos de dados básicos manipulados em um programa.

Declarações listam as variáveis que serão usadas, seus tipos e, talvez seus valores iniciais.

Operadores especificam o que é feito com as variáveis.

Expressões combinam variáveis e constantes para produzir novos valores.

O tipo de um objeto determina o conjunto de valores que este pode assumir e quais operações podem ser executadas
nele.

O padrão ANSI fez pequenas mudanças nos tipos básicos e expressões. Existem agora tipos **signed** e **unsigned**
de todos os tipos inteiros. Operações em ponto flutuante podem ser feitas com precisão singular. Também
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
 
Existe ainda outro tipo de constante, a _**enumeration constant**_. Uma _enumeration_ é uma lista de valores de constantes inteiras, como por exemplo
 
 ```c
  enum boolean { NO, YES };
 ```
 
O primeiro nome em uma lista **enum** possui valor 0, o segundo 1, e assim sucessivamente, a não ser que os valores sejam especificados. Se nem todos os valores são especificados, os que não forem continuam a progressão do último valor especificado, como no segundo dos próximos exemplos.

```c
enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r'};
```

```c
enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; // FEB é 2, MAR é 3 ...
```

### Declarations

Todas as variáveis devem ser declaradas antes de seu uso, embora certas declarações possam ser feitas implicitamente pelo contexto. Uma declaração especifica um **tipo** e contém uma lista de uma ou mais variáveis daquele tipo, como em

```c
 int inferior, superior, passo;
 char c, linha[1000];
```

As declarações acima poderiam ter sido escritas separadamente, tomando mais espaço no código, porém pode ser conveniente para comentários sobre tal variável e modificações posteriores.

Uma variável pode também ser iniciada na sua declaração. Se o nome é seguido de um sinal de igualdade e uma expressão, a expressão serve como um inicializador, como por exemplo,

```c
 char esc = '\\';
 int i = 0;
 int limit = MAXLINE + 1;
 float eps = 1.0e-5;
```

Se a variável em questão não for automática (local), a inicialização é feita somente uma vez. Já uma variável automática é inicializada toda vez que a função ou bloco é adentrada. Variáveis externas e **static** são inicializadas em zero por padrão. Variáveis automáticas não inicializadas tem valor indefinido (lixo).

O qualificador **const** pode ser aplicado a uma declaração de variável cujo valor não será mudado. No caso de um _array_, indica que seus elementos não serão alterados.

```c
 const double e = 2.71828182845905;
 const char msg[] = "warning: ";
```

### Arithmetic Operators

 Os operadores binários aritméticos são **+, -, \*, /** e o operador módulo **%**. Já que a divisão de inteiros trunca qualquer parte fracionária, a expressão **x % y** produz o resto da divisão de x por y, sendo zero quando a divisão for exata.
 
 O operador **%** não pode ser aplicado a **float** ou **double**. Os operadores + e - tem a mesma precedência, que é inferior à precedência de \*, / e %, que por sua vez é inferior aos + e - unários (bit a bit). Operadores aritméticos são associados da esquerda para a direita.

### Relational and Logical Operators

Os operadores relacionais são:

```c
 >    >=    <    <=
```

Todos possuem precedência igual. Abaixo deles em termos de precedência estão os operadores de igualdade:

```c
 ==    !=
```

Operadores relacionais possuem precedência menor do que operadores aritméticos, logo, uma expressão como **i < lim - 1** é equivalente a **i < (lim - 1)**.

Ainda há os operadores lógicos && e ||. Expressões conectadas por estes são avaliadas da esquerda para a direita, e a avaliação acaba assim que a veracidade ou falsidade da expressão é conhecida, como já mencionado no capítulo 1. A precedência de && é maior do que a de ||, e ambos possuem precedência menor do que operadores relacionais e de igualdade, assim, a expressão

```c
 i < lim - 1 && (c = getchar()) != '\n' && c != EOF
```

não necessita de parênteses adicionais. No entanto, como **!=** possui precedência maior do que o operador _assignment_ **=**, os parênteses são necessários em tal termo.

Por definição, o valor numérico de uma expressão relacional ou lógica é 1 caso seja verdadeira e 0 caso seja falsa. O operador de negação unária **!** converte um operando não-nulo em 0 e um operando zero em 1. Um uso comum desse operador é em construções como:

```c
 if (!valid)
```

ao invés de

```c
 if (valid == 0)
```

### Type Conversions

Quando um operador possui dois tipos diferentes de operando, eles são convertidos para um tipo comum de acordo com um pequeno número de regras. Em geral, as únicas conversões automáticas são as que convertem um operando "menor" em um "maior" sem perder informações, como converter um **int** em **float** numa expressão como **f + i**;

- Expressões que não fazem sentido, como utilizar um **float** como subscrito de um vetor não são permitidas;
- Expressões que podem perder informações, como atribuir um **long int** a um **short int**, podem levantar um alerta do compilador, mas não são ilegais;
- Um **char** é apenas um inteiro pequeno, logo, podem ser utilizados livremente em expressões aritméticas. Esse tipo de conversão é útil em funções como a seguinte, que transforma caracteres maiúsculos em minúsculos.

```c
 int lower(int c)
 {
  if (c >= 'A' && c <= 'Z')
   return c + 'a' - 'A';
  else 
   return c;
 }
```

Vale ressaltar que o código funciona apenas para máquinas/compiladores que utilizem ASCII, caso utilizasse o conjunto EBCDIC, não funcionaria, porém poderia ser facilmente modificado.

O _header_ padrão **<ctype.h>** define uma família de funções que fornece testes e conversões que são independentes do conjunto de caracteres. Por exemplo, a função **tolower(c)** retorna o valor em letras minúsculas de **c** se **c** for maiúsculo. Da mesma forma, o teste

```c
 c >= '0' && c <= '9'
```

poderia ser substituído por

```c
 isdigit(c)
```

Ainda sobre a conversão de **char** para **int**, há um certo ponto a ser discutido. C não especifica se variáveis do tipo **char** são **signed** ou **unsigned**, logo, quando um **char** é convertido em **int**, pode produzir um inteiro negativo? A resposta varia de máquina a máquina. Em algumas máquinas, um **char** cujo bit mais à esquerda seja 1 será convertido em um inteiro negativo. Em outras, um **char** é convertido em **int** adicionando zeros à sua esquerda, portanto, sempre será positivo.

Por definição, o C garante que numa expressão, caracteres serão sempre positivos, no entanto, padrões binários arbitrários podem aparecer negativos em algumas máquinas e positivos em outras. Por conta disso, deve-se especificar **unsigned** ou **signed** se algum dado não-char vá ser armazenado em variáveis **char**.

Conversões aritméticas implícitas funcionam como esperado. Em geral, se um operador como + ou \* (binário) tem operandos de tipos diferentes, o tipo "menor" é _promovido_ ao "maior" antes da operação ocorrer. O resultado é do tipo "maior". O apêndice A trata das regras de conversão de forma mais aprofundada. No entanto, se não existirem operandos **unsigned**, o seguinte conjunto de regras é suficiente:

- Se qualquer um dos operandos é **long double**, converte o outro para **long double**;
- Caso não, se qualquer um dos operandos é **double**, converte o outro para **double**;
- Caso não, se qualquer um dos operandos é **float**, converte o outro para **float**;
- Caso não, converte **char** e **short** para **int**;
- Então, se qualquer operando é **long**, converte o outro para **long**.

Geralmente, funções matemáticas como as que estão em **<math.h>** usarão precisão **long**. A principal razão para utilizar **float** é para poupar armazenamento em vetores grandes, ou, menos frequente, poupar tempo em máquinas nas quais aritmética com precisão dupla é particularmente caro.

As regras de conversão são mais complicadas quando envolvem operandos **unsigned**, pois são dependentes da máquina, pois os tamanhos das variáveis mudam. Por exemplo, suponha que **int** possui 16 bits e **long** 32 bits. Nesse caso,

- -1L < 1U, pois 1U, que é um **int**, é promovido a **signed long**;
- -1L > 1UL, pois -1L é promovido a **unsigned long** e então aparece como um número positivo maior.

Ainda, 

- A conversão de **float** para **int** causa truncamento da parte fracionária;
- Na conversão de **double** para **float**, se o valor será arredondado ou truncado depende da implementação.


Um argumento de uma função é uma expressão, logo, conversões ocorrem quando os argumentos são passados às funções. Na ausência de um protótipo de função (a declaração no início), **char** e **short** tornam-se **int** e **float** é convertido em **double**. Por isso, até agora foram declarados argumentos de funções como **int** e **double** mesmo quando a função é chamada com **char** e **float**.

#### Conversão explícita (cast)

Conversões podem ser forçadas em qualquer expressão, com o operador unário chamado _**cast**_. Na construção

```c
 (**tipo**) expressão
```

a **expressão** é convertida para o tipo nomeado pelas regras mencionadas. O significado preciso do **cast** é como se a expressão fosse atribuída a uma variável do tipo especificado. Por exemplo, a rotina **sqrt** (da biblioteca **<math.h>** espera um argumento **double** e produz um resultado sem sentido caso não seja fornecido um valor de tal tipo. Logo, se **n** é um inteiro, pode-se fazer

```c
 sqrt((double) n)
```

para converter o valor de **n** para **double** ao passá-lo para **sqrt**. Note que o **_cast_** produz o valor de **n** no tipo apropriado, no entanto, a variável **n** não é alterada. O operador **_cast_** tem a mesma precedência alta de outros operadores unários, como será mostrado na tabela no final do capítulo.

Argumentos geralmente são declarados no protótipo da função; tal declaração causa conversão automática de qualquer argumento quando a função for chamada. Por exemplo, dado o protótipo de **sqrt**:

```c
double sqrt(double);
```

a chamada

```c
raiz2 = sqrt(2);
```

automaticamente transforma o inteiro 2 no valor **double** 2.0 sem a necessidade de um **_cast_**.

### Increment and Decrement Operators

  C fornece dois operadores para incrementar e decrementar variáveis. O operador incremento **++** adiciona um a seu operando, enquanto que o operador **--** subtrai 1. A parte inusitada é que tais operadores podem ser utilizados antes ou depois da variável.
  
  - A expressão **++n** incrementa **n** antes de seu valor ser utilizado;
  - A expressão **n++** incrementa **n** após seu valor ser utilizado.

Esses operadores só podem ser aplicados a variáveis, logo, uma expressão do tipo **(i + j)++** é ilegal. Com isso, pode-se modificar códigos como o seguinte:

```c
  if (c == '\n') {
    s[i] = c;
    ++i;
  }
```

para uma forma mais compacta

```c
  if (c == '\n')
    s[i++] = c;
```

### Bitwise Operators

A linguagem C fornece seis operadores para manipulação de bits; estes só podem ser aplicados a operandos inteiros, isto é, **char, short, int, long**, seja **signed** ou **unsigned**

Operador | Descrição
--- | ---
& | bitwise AND
\| | bitwise inclusive OR
^ | bitwise exclusive OR
<< | left shift
\>> | right shift
~ | complemento de um (unário)

Um uso comum do **&** é mascarar um conjunto de bits, por exemplo

```c
  n = n & 0177;
```

seta a zero todos os bits, exceto os últimos 7 bits de **n**. (177<sub>8</sub> = 11111111<sub>2</sub>).

O OR _bitwise_ é utilizado para "ligar" bits:

```c
  x = x | SET_ON;
```

Essa linha de código seta para 1 todos os bits que são 1 em **SET_ON**, por exemplo, se **SET_ON = 1111**, os últimos quatro bits são "ligados", independente de seu valor atual.

O operador de bit OR (^) seta para um cada posição de bit na qual seus operandos possuem bits diferentes, e zero onde são iguais.

Deve-se distinguir os operadores **_bitwise_** & e | dos operadores lógicos **&&** e **||**, que implicam avaliação (da esquerda para a direita) de uma verdade ou falsidade. Por exemplo,

```c
  x = 1; //(01)
  y = 2; //(10)
  a = x & y // a = 0... 0 AND 1 = 0, 1 AND 0 = 0
  b = x && y // b = TRUE, pois 1(TRUE) AND 2(TRUE) = TRUE
```

Os operadores _shift_ << e >> performam _shifts_ (deslocamentos) para a esquerda e para a direita do operando à esquerda pelo número de posições (bits) dadas no operando à direita, que deve ser positivo. Portanto, **x << 2** desloca o valor de **x** para a esquerda em duas posições, preenchendo o que ficaria vazia com zeros. Um deslocamento à direita de um **unsigned** sempre preenche os bits vagos com zeros. No entanto, deslocamento à direita em **signeds** preenche com bits de sinal (_arithmetic shift_) em algumas máquinas e com zeros (_logical shift_) em outras.

O operador unário ~ produz o complemento de um de um inteiro, i.e., converte cada bit 1 para 0 e vice-versa. Por exemplo,

```c
x = x & ~077 // 077 = 00111111
```

seta os últimos 6 bits de x para zero. Tal expressão é independente do tamanho da palavra, então, é preferível a **x & 0177700** (017700<sub>8</sub> = 1111111111000000<sub>2</sub>), assumindo que **x** é uma quantidade de 16 bits. Tal portabilidade não possui custo extra, já que ~077 é uma expressão constante que pode ser avaliada durante a compilação.

### Assignment Operators and Expressions

Expressões do tipo

```c
  i = i + 2;
```

podem ser escritas na forma comprimida

```c
  i += 2;
```

O operador **+=** é um **_assignment operator_**. A maioria dos operadores binários possuem um operador _assignment_ correspondente **op=**, onde **op** é um de

```
 +   -   *   /   %   <<   >>   &   ^   |
```

Se **expr1** e **expr2** são expressões, então

```
  expr1 op= expr2
```

é equivalente a

```
  expr1 = (expr1) op (expr2)
```

exceto que **expr1** só é computado uma vez. Note os parênteses ao em **expr2**:

```c
  x *= y + 1
```

significa 

```c
  x = x * (y + 1)
```

e não

```c
  x = x * y + 1
```

Por fim, em quaisquer expressões _assignment_, o tipo de tal _assignment_ é o tipo do operando à esquerda.

### Conditional Expressions

Os _statements_

```c
  if (a > b)
    z = a;
  else
    z = b;
```

computam em **z** o máximo entre **a** e **b**. A _conditional expression_, escrita com o operador ternário **"?:"**, fornece um método alternativo para escrever isso e construções similares. Na expressão

```c
  expr1 ? expr2 : expr3
```

A expressão **expr1** é avaliada primeiro. Se é verdadeira, então **expr2** é avaliada, e este é o valor da _conditional expression_. Se não, **expr3** é avaliada e esse é o valor. Somente uma de **expr2** e **expr3** é avaliada. Dessa forma, passar a **z** o valor máximo entre **a** e **b** pode ser feito da seguinte forma:

```c
  z = (a > b) ? a : b; // z = max(a,b)
```

Se **expr2** e **expr3** são de tipos diferentes, o tipo do resultado é determinado pelas regras de conversão descritas anteriormente neste capítulo. Por exemplo, se **f** é um **float** e **n** um **int**, a expressão

```c
  (n > 0) ? f : n
```

é do tipo **float**, não importando se **n** é positivo. Parênteses não são necessários ao redor da primeira parte da expressão, tendo em vista que a precedência de ?: é muito baixa, somente acima do _assignment_. No entanto, são recomendados por questões de leitura de código.

### Precedence and Order of Evaluation

A tabela abaixo resume as regras de precedência e associatividade de todos os operadores, incluindo os que não foram discutidos ainda.

Operadores | Associatividade
---------- | ---------------
( )       [ ]      ->       . | esquerda para direita 
!      ~      ++      --      +      -      *     &     (**tipo**)    **sizeof** | direita para esquerda
\*     /     % | esquerda para direita 
\+       -    | esquerda para direita 
<<      \>>   | esquerda para direita 
<     <=      >     >= | esquerda para direita 
==        != | esquerda para direita
& | esquerda para direita
^ | esquerda para direita
\| |  esquerda para direita
&& | esquerda para direita
\|\| | esquerda para direita
?: | direita para esquerda
= += -= *= /= %= &= \^= \|= <<= >>= | direita para esquerda
, | esquerda para direita

Os operadores na mesma linha tem a mesma ordem de precedência; linha sestão em ordem decrescente de precedência. O **"operador"** () se refere a chamada de função. Os operadores -> e . são usados para acessar membros de estruturas e serão tratados no capítulo 6, assim como **sizeof**. O capítulo 5 discute * (direção por um ponteiro) e & (endereço de um objeto), e o capítulo 3 discute o operador vírgula.

A linguagem C não especifica a ordem na qual os operandos de um operador são avaliados (com exceção de &&, ||, ?: e ,). Assim, num _statement_ como

```c
  x = f() + g();
```

**f** pode ser avaliado antes de **g** ou vice-versa; dessa forma, se **f** ou **g** alteram uma variável da qual a outra depende, **x** pode depender da ordem de avaliação. Pode-se utilizar variáveis temporárias para garantir uma sequência particular. De maneira similar, a ordem na qual argumentos são avaliados não é especificada, portanto, o _statement_

```c
  printf("%d %d\n", ++n, power(2,n)); // ERRADO!
```

pode produzir resultados diferentes em compiladores diferentes, dependendo se **n** é incrementado antes de **power** ser chamada. A solução, neste caso, é escrever

```c
  ++n;
  printf("%d %d\n", n, power(2,n));
```

Logo, conclui-se que escrever código que depende da ordem de avaliação é uma prática ruim de programação em qualquer linguagem. 

</div>
