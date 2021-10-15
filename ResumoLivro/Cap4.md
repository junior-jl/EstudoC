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

### Functions Returning Non-integers

Até o momento, todas as funções utilizadas retornaram nenhum valor (**void**) ou um **int**. Muitas funções numéricas como **sqrt, sin, cos** retornam **double**; outras funções especializadas retornam outros tipos. Para ilustrar como lidar com isso, escrevemos e usamos a função **atof(s)**, que converte a _string_ **s** no seu equivalente ponto flutuante de precisão dupla. A função descrita abaixo não é de alta qualidade, porém funciona bem para fins didáticos; a biblioteca padrão **<stdlib.h>** inclue um **atof**.

```c
double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i = 0; isspace(s[i]); i++) // pula espaços brancos
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
```

Vale ressaltar que a rotina de chamada deve saber que **atof** retorna um valor não-**int**. Uma forma de assegurar isso é declara **atof** explicitamente na rotina de chamada. Tal declaração é mostrada no código de uma calculadora primitiva, que lê um número por linha, opcionalmente precedido por um sinal, e os soma, imprimindo a soma atual após cada entrada.

```c
#include <stdio.h>

#define MAXLINE 100

main()
{
    double sum, atof(char []);
    char line[MAXLINE];
    int getline(char line[], int max);

    sum = 0;
    while (getline(line, MAXLINE) > 0)
        printf("\t%f\n", sum += atof(line));
    return 0;
}
```

A declaração

```c
  double sum, atof(char []);
```

diz que **sum** é uma variável **double** e **atof** é uma função que recebe um **char[]** e retorna um **double**. 

A função **atof** deve ser declarada e definida consistentemente. Se **atof** e sua chamada em **main** tiverem tipos inconsistentes no mesmo arquivo, o erro será detectado pelo compilador. No entanto, se (o que é mais provável), **atof** foi compilada separadamente, a incompatibilidade não seria detectada, **atof** retornaria um **double** que **main** trataria como **int** e a resposta acabaria sem sentido.

A razão para que uma incompatibilidade ocorra é que se não há protótipo de função, esta é implicitamente declarada pela sua primeira aparição numa expressão, como

```c
  sum += atof(line)
```

Se um nome que não tiver sido previamente declarado ocorre em uma expressão e é seguido de um parêntese esquerdo, é declarado por contexto como um nome de função, assume-se que a função retorna um **int** e nada é assumido acerca de seus argumentos. Além disso, se uma declaração de função não inclui argumentos, como

```c
  double atof();
```

nada é assumido sobre os argumentos de **atof**; toda a checagem de parâmetros é desligada. Este significado especial da lista de argumentos vazia é para permitir que programas antigos em C compilem em novos compiladores. Porém, é uma má ideia usá-la para novos programas. Se a função possui argumentos, declare-os; se não há, use **void**.

### External Variables

Um programa em C consiste de um conjunto de objetos externos, que podem ser variáveis ou funções. O adjetivo "externo" é utilizado em contraste a "interno", que descreve os argumentos e variáveis definidos dentro de funções. Variáveis externas são definidas fora do escopo de qualquer função, podendo ser acessadas por qualquer função. As funções por si só são externas, pois C não permite a definição de uma função dentro de outra. Por padrão, variáveis e funções externas possuem a propriedade de que todas as referências ao mesmo nome, até mesmo em funções compiladas separadamente, são referências à mesma coisa (o padrão ANSI chama isso de _**external linkage**_.

Se um grande número de variáveis precisa ser compartilhado entre funções, variáveis externas são mais convenientes e eficientes do que longas listas de argumentos. Porém, como comentado no capítulo 1, este raciocínio deve ser aplicado com cautela, pois pode gerar um efeito ruim na estrutura do programa.

Vamos examinar essa propriedade com um exemplo maior. O problema é escrever um programa de calculadora que fornece os operadores **+, -, \*** e **/**. Por ser mais simples de implementar, a calculadora usará a notação polonesa inversa ao invés da notação infixa (notação geralmente utilizada onde o operador é colocado entre os operandos).

Na notação polonesa reversa, cada operador segue seus operandos, assim, uma expressão infixa como:

```
(1 - 2) \* (4 + 5)
```

é inserida como

```
1 2 - 4 5 + *
```

Parênteses não são necessários; a notação não gera ambiguidade, desde que se saiba quantos operandos cada operador espera.

A implementação será feita da seguinte forma:

- Cada operando é colocado em um monte (_stack_);
- Quando chega o operador, o número adequado de operandos (dois para operadores binários) é "estourado" (_popped_) e o operador é aplicado a estes;
- O resultado é colocado (_pushed_) de volta no monte.

No exemplo acima, o passo-a-passo seria:

- 1 e 2 são colocados no monte, daí substituídos por sua diferença (-1);
- Após isso, 4 e 5 são colocados e substituídos por sua soma (9);
- O produto de -1 e 9 (-9) os substitui no monte;
- O valor no topo do monte é retirado e impresso quando o fim da linha de entrada é encontrado.

Assim, a estrutura do programa é um _loop_ que performa operações apropriadas em cada operador e operando quando aparecem (a tradução de alguns termos ficou confusa pra mim, coloquei entre parênteses):

```c
  while (o próximo operador ou operando não for o indicador fim de arquivo (EOF))
    if (número)
      joga o número (push it)
    else if (operador)
      coloca operandos (pop)
      faz a operação
      joga o resultado (push)
    else if (newline)
      coloca e imprime o topo do monte (pop and print top of stack)
    else
      erro
```

