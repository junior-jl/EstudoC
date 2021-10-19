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

As operações de _pushing_ e _popping_ um _stack_ são triviais, porém, ao incluir o tempo de detecção e recuperação, são longas o suficiente para que uma função separada para cada seja mais eficiente. Além disso, é interessante uma função para pegar a próxima entrada (operando ou operador).

A principal decisão do projeto é onde fica o _stack_, isto é, quais rotinas podem acessá-lo diretamente. Uma possibilidade é mantê-lo na **main** e passar o _stack_ e sua posição atual para as rotinas que vão _push and pop it_. Mas **main** não precisa saber das variáveis que controlam o _stack_; ela só faz as operações _push_ e _pop_. Então, decidiu-se armazenar o monte e suas informações em variáveis externas acessíveis para as funções **push** e **pop**, mas não para **main**. Traduzindo para código, seria algo similar a

```c
#includes
#defines

declaração de funções para main

main() { ... }

variáveis externas para push e pop

void push (double f) { ... }
double pop (void) { ... }

int getop (char s[]) { ... }

rotinas chamadas por getop

```

A função **main** é um loop contendo um grande **switch** do tipo de operador ou operando:

```c
#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);

//Calculadora com notação polonesa reversa

main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF)
    {
        switch(type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

```

Os operadores **+** e **\*** são comutativos, portanto, a ordem que os operandos são combinados é irrelevante, mas para **-** e **/** os operadores da esquerda e da direita devem ser distinguidos. Em

```c
  push(pop() - pop()); // ERRADO!
```

a ordem na qual as duas chamadas de **pop** são avaliadas não é definida. Para garantir a ordem correta, é necessário _pop_ o primeiro valor numa variável temporária, como foi feito em **main**.

```c
#define MAXVAL 100 // máxima profundidade do stack de valores

int sp = 0; // próxima posição livre do stack
double val[MAXVAL]; // stack de valores

//push: push f onto value stack

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

//pop: pop and return top value from stack

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

```

Note que o _stack_ e o _stack index_ são declarados fora das funções **pop** e **push** para que possam ser compartilhados por ambas. No entanto, **main** não se refere a nenhuma dessas variáveis.

Vamos agora à implementação de **getop**, a função que recebe o próximo operador ou operando. A tarefa é simples. Pule _blanks_ e _tabs_. Se o próximo caractere não for um dígito ou ponto decimal, retorne-o. Senão, colete uma _string_ de dígitos (que podem incluir um ponto decimal), e retorne **NUMBER**, o sinal de que um número foi coletado.

```c
#include <ctype.h>

int getch(void);
void ungetch(int);

//getop: pega o próximo operador ou operando numérico

int getop(char s[])
{
    int i, c;
    
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; // não é um número
    i = 0;
    if (isdigit(c)) // coleta a parte inteira
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') // coleta a parte fracionária
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}
```

O que são **getch** e **ungetch**? É comum um programa não conseguir determinar se já leu entradas suficientes até que tenha lido demais. Um exemplo é coletar os caracteres que compõem um número: até que o primeiro dígito "não-número" seja visto, o número não está completo. Mas então o programa tem que ler um caractere a mais, um caractere para o qual não estava preparado.

O problema seria resolvido se pudéssemos "desler" (_un-read_) o caractere indesejado. Então, toda vez que o programa ler um caractere a mais, jogaria-o de volta à entrada, e o resto do código poderia se comportar como se nunca tivesse o lido. **getch** entrega o próximo caractere da entrada a ser considerado; **ungetch** lembra os caracteres "devolvidos" à entrada, para que chamadas subsequentes de **getch** retornem a esses valores antes de ler uma nova entrada.

Como elas funcionam é simples. **ungetch** coloca o caractere jogado de volta em um **_buffer_** compartilhado - um vetor de caracteres. **getch** lê do buffer se existe algo lá, e chama **getchar** se o _buffer_ estvier vazio. Deve haver também uma variável de índice que registre a posição do caractere atual no _buffer_.

Já que o _buffer_ e o índice são compartilhados por **getch** e **ungetch** e devem guardar seus valores entre chamadas, devem ser externos a ambas as rotinas. Assim, podemos escrever **getch, ungetch** e suas variáveis compartilhadas como:

```c
#define BUFSIZE 100

char buf[BUFSIZE]; // buffer para ungetch
int bufp = 0; // próxima posição livre no buf

int getch(void) // pega um (possivelmente jogado de volta) caractere
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
```

A biblioteca padrão include uma função **ungetc** que fornece um caractere de _pushback_ (será discutida no capítulo 7).

### Scope Rules

As funções e variáveis externas que compõem um programa em C não precisam ser compiladas ao mesmo tempo; o texto fonte do programa pode ser mantido em diferentes arquivos, e rotinas previamente compiladas podem ser carregadas de bibliotecas. Dentre as questões de interesse estão:

- Como declarações são escritas de modo que as variáveis sejam propriamente declaradas durante a compilação?
- Como declarações são organizadas de modo que todas as partes sejam propriamente conectadas quando o programa for carregado?
- Como declarações são organizadas de forma que haja apenas uma cópia?
- Como variáveis externas são inicializadas?

Vamos discutir estes tópicos reorganizando o programa de calculadora em vários arquivos. Praticamente, o programa da calculadora seria muito pequeno para necessitar de divisão, porém é uma ilustração eficiente.

O escopo _(scope)_ de um nome é uma parte do programa dentro da qual o nome pode ser usado. Para uma variável automática declarada no início de uma função, o escopo é a função na qual seu nome foi declarado. Variáveis locais de mesmo nome em funções diferentes não possuem relação. O mesmo é válido para parâmetros de funções, que são, em efeito, variáveis locais.

O escopo de uma variável externa ou função dura do ponto no qual é declarada até o fim do arquivo sendo compilado. Por exemplo, se **main, sp, val, push** e **pop** são definidas em um arquivo, na ordem mostrada abaixo,

```c
  main() { ... }
  
  int sp = 0;
  double val[MAXVAL];
  
  void push(double f) { ... }
  
  double pop(void) { ... }
```

então as variáveis **sp** e **val** podem ser utilizadas em **push** e **pop** simplesmente nomeando-as; não é necessária outra declaração. No entanto, tais nomes não são "visíveis" a **main**, assim como as próprias funções **push** e **pop**.

Por outro lado, se uma variável externa é referida antes de ser definida, ou definida em um arquivo diferente do que está sendo utilizada, uma declaração **extern** é obrigatória.

É importante distinguir entre a **declaração** de uma variável externa e sua **definição**. Uma **declaração** anuncia as propriedades de uma variável (inicialmente, seu tipo); uma **definição** também causa reserva de memória. Se as linhas

```c
  int sp;
  double val[MAXVAL];
```

aparecem fora de qualquer função, elas **definem** as variáveis externas **sp** e **val**, reservam memória para elas, e ainda servem como **declaração** para o resto do arquivo. Por outro lado, as linhas

```c
  extern int sp;
  extern double val[];
```

**declaram** para o resto do arquivo que **sp** é um **int** e **val** é um vetor **double** (cujo tamanho é determinado em outro lugar), no entanto, não criam as variáveis nem reservam memória para elas.

Deve haver apenas uma **definição** de uma variável externa dentre todos os arquivos que compõem o programa fonte; outros arquivos (ou o próprio arquivo na qual é definida) podem conter declarações **extern** para acessá-las. Tamanhos de vetores devem ser especificados na definição, mas são opcionais na declaração **extern**.

A inicialização de uma variável externa acontece apenas na sua definição.

### Header Files

Vamos agora considerar dividir o programa da calculadora em diversos arquivos fonte, como seria feito se cada componente fosse substancialmente maior. A função **main** iria num arquivo, chamado **main.c**; **push, pop** e suas variáveis iriam num segundo arquivo, **stack.c**; **getop** num terceiro, **getop.c**. Finalmente, **getch** e **ungetch** iriam num quarto arquivo **getch.c**; estas últimas foram separadas pois, num programa realista, viriam de uma biblioteca compilada separadamente.

Só há mais uma questão a se preocupar - as definições e declarações compartilhadas pelos arquivos. Deve-se centralizar, tanto quanto possível, para que haja apenas uma cópia. Portanto, colocamos esse material comum em uma _header file_ (arquivo cabeçalho), **calc.h**, que será incluído onde for necessário. O programa resultante tem a seguinte forma:

![image](https://user-images.githubusercontent.com/69206952/137824586-e3beba7d-d295-483d-a6a3-6b48e4446852.png)

Há um _tradeoff_ (uma troca com vantagens e desvantagens) entre o desejo de que cada arquivo tenha acesso à informação necessária para seu trabalho e a realidade prática da dificuldade de manter mais arquivos _header_. 

### Static Variables

As variáveis **sp** e **val** em **stack.c**, e **buf** e **bufp** em **getch.c** são para uso exclusivo das funções em seus respectivos arquivos, e não devem ser acessadas por nada mais. A declaração **static**, aplicada a uma função ou variável externa, limita o escopo daquele objeto para o resto do arquivo fonte sendo compilado. Assim, **static** fornece uma maneira de esconder nomes como **buf** e **bufp** na combinação **getch-ungetch**, as quais devem ser externas para que possam ser compartilhadas, no entanto, não deveria ser vista pelos usuários de **getch** e **ungetch**.

O armazenamento estático é especificado colocando o prefixo **static** antes da declaração normal da variável. Se as duas rotinas e as duas variáveis são compiladas em um arquivo, como em

```c
  static char buf[BUFSIZE];
  static int bufp = 0;
  
  int getch(void) { ... }
  
  void ungetch(int c) { ... }
```

então nenhuma outra rotina será capaz de acessar **buf** e **bufp**, e tais nomes não conflitarão com os mesmos nomes em outros arquivos do mesmo programa. Da mesma forma, as variáveis que **push** e **pop** utilizam para manipular o monte (_stack_) podem ser escondidas, declarando **sp** e **val** como **static**.

A declaração externa **static** geralmente é utilizada para variáveis, porém pode ser aplicada em funções. Normalmente, nomes de funções são globais, visíveis a qualquer parte do programa. Se uma função é declarada como **static**, no entanto, seu nome é invisível fora do arquivo no qual é declarada.

A declaração **static** também pode ser aplicada a variáveis internas. Nesse caso, tornam-se locais a uma função particular como variáveis automáticas, mas, ao contrário destas, permanecem existindo sem a necessidade da chamada da função a qual pertencem. Isso significa que **static** utilizado em variáveis internas fornece armazenamento permanente e exclusivo dentro de uma função única. 
