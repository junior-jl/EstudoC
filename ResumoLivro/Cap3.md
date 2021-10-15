# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 3 - Control Flow

<div align="justify">

Os _statements control-flow_ de uma linguagem especificam a ordem na qual computações são feitas. A maioria das construções deste tipo já foram vistas em exemplos anteriores; aqui o conjunto será completado e as discutidas anteriormente serão aprofundadas.

### Statements and Blocks

Uma **expressão** como **x = 0** se torna um _statement_ quando é seguida por um ponto e vírgula. Em C, o ponto e vírgula é um _statement terminator_, não apenas um separador, como em linguagens como Pascal.

As chaves { e } são usadas para agrupar declarações e _statements_ em um _compound statement_ ou _block_, logo, são equivalentes a um único _statement_. Não há ponto e vírgula após a chave direital

### If-Else

O _statement **if-else**_ é usado para expressar decisões. Formalmente, a sintaxe é

```c
  if (expressão)
    statement1
  else
    statement2
```

na qual, o **else** é opcional. A **expressão** é avaliada; caso seja verdadeira (se a expressão tiver um valor diferente de zero), **statement1** é executado. Caso seja falsa (**expressão** tem valor nulo) e existir um **else**, o **statement2** é executado.

Tendo em vista que **if** testa simplesmente o valor numérico de uma expressão, alguns atalhos de código são possíveis. O mais óbvio é escrever

```c
  if (expression)
```

ao invés de

```c
  if (expression != 0)
```

É recomendado utilizar chaves quando existirem **ifs** aninhados para evitar confusões, por exemplo, no código

```c
  if (n > 0)
    if (a > b)
      z = a;
    else 
      z = b;
```

o **else** pertence ao **if** interior, como a indentação mostra bem. Caso não seja o desejado, as chaves resolvem o problema, associando o **else** ao **if** exterior, i.e.,

```c
  if (n > 0){
    if (a > b)
      z = a;
  }
  else
    z = b;
      
```

### Else-If

A construção

```c
  if (expressão)
    statement
  else if (expressão)
    statement
  else if (expressão)
    statement
  else if (expressão)
    statement 
  else
    statement
```

é tão comum que vale a pena discuti-la separadamente. Esta sequência de _if statements_ é a forma mais geral de escrever uma decisão múltipla. As **expressões** são avaliadas em ordem; se qualquer delas é verdadeira, o _statement_ associado é executado e toda a cadeia é encerrada. O último **else** é a alternativa "nenhuma das anteriores", pode ser utilizada para mostrar erro em um caso impossível ou indesejado no programa, como também pode ser omitido.

### Switch

O _statement_ **switch** é uma decisão de múltipla escolha que testa se uma expressão é um dos valores inteiros _constant_.

```c
  switch (expressão) {
    case const-expr: statements
    case const-expr: statements
    default: statements
  }
```

Cada caso é denominado por uma ou mais constantes inteiras ou expressões constantes. Se um caso é igual ao valor da expressão, a execução inicia naquele **case**. Todas as expressões de **case** devem ser diferentes. O **case** rotulado **default** é executado se nenhum dos outros casos for satisfeito. Similarmente ao **else**, **default** é opcional; neste caso, se nenhum dos **cases** for satisfeito, nenhuma ação é tomada. A seguir, um exemplo de programa com **switch**.

```c
  #include <stdio.h>
  
  main() // conta dígitos, espaços brancos, outros
  {
    int c, i, nbranco, noutro, ndigito[10];
    
    nbranco = noutro = 0;
    for (i = 0; i < 10; i++)
      ndigito[i] = 0;
    while ((c = getchar()) != EOF) {
      switch (c) {
      case '0': case '1': case '2': case '3': case '4':
      case '5': case '6': case '7': case '8': case '9':
        ndigito[c - '0']++;
        break;
      case ' ':
      case '\n':
      case '\t':
        nbranco++;
        break;
      default:
        noutro++;
        break;
      }
    }
    printf("Dígitos =");
    for (i = 0; i < 10; i++)
      printf(" %d", ndigito[i]);
    printf(", espaço branco = %d, outro = %d\n", 
      nbranco, noutro);
    return 0;
 
  
  }
```

O _statement_ **break** causa uma saída imediatada do **switch**. Já que **cases** servem apenas como _labels_, após o código em um case ser feito, a execução "_falls through_" (cai através) do próximo a não ser que uma ação explícita seja feita para sair. **break** e **return** são as formas mais comuns de sair de um **switch**. Além disso, o **break** pode ser utilizado para forçar saída imediata de um **while**, **for** e _loops_ **do** (os quais serão discutidos neste capítulo).

A questão de "cair através" tem vantagens e desvantagens. No lado positivo, permite que vários **cases** sejam vinculados a uma única ação, como no exemplo anterior. No entanto, implica a necessidade de um **break** para prevenir a "queda" para o próximo.

Como questão de boa prática de escrita, deve-se colocar um **break** após o último caso (**default** no exemplo), mesmo que seja logicamente desnecessário.

### Loops - While and For

No código

```c
  while (expressão)
    statement
```

a expressão é avaliada. Se for não-nula, _statement_ é executado e **expressão** é reavaliada. O ciclo continua até que **expressão** seja nula, e a execução continua após _statement_.

O _statement_ for

```c
  for (expr1 ; expr2 ; expr3)
    statement
```

é equivalente a 

```c
  expr1;
  while (expr2) {
    statement
    expr3;
  }
```

com exceção do comportamento de **continue**, que é descrito ainda neste capítulo.

Gramaticamente, os três componentes de um _loop **for**_ são expressões. Mais comumente, **expr1** e **expr3** são _assignments_ ou chamadas de funções e **expr2** é uma expressão relacional. Qualquer uma das três partes pode ser omitida, no entanto, o ponto e vírgula deve ser mantido. Se **expr1** ou **expr3** são omitidas, é simplesmente retirado da expansão. Se o teste **expr2** não estiver presente, é tomado como permanentemente verdadeiro, portanto,

```c
  for (;;) {
    ...
  }
```

é um _loop_ "infinito", presumivelmente quebrado por outros meios, como um **break** ou **return**.

Utilizar **while** ou **for** é uma questão de preferência pessoal e do programa a ser executado. Por exemplo, em

```c
  while ((c = getchar()) == ' ' || c == '\n' || c == '\t')
  ; // pula caracteres de espaço em branco
```

não há inicialização ou reinicialização, portanto, o **while** é a escolha natural. O **for** é preferível quando há uma inicialização e incremento simples, tendo em vista que estes _statements_ ficam juntos e visíveis no topo do _loop_.

Os componentes de um _loop **for**_ não precisam ser, necessariamente, expressões aritméticas. No entanto, não é recomendado realizar computações não relacionadas nos campos de inicialização e incremento, pois são campos melhor utilizados para controle de operações do _loop_.

#### Operador vírgula

Um último operador em C é a vírgula ",", comumente encontrado no _statement **for**_. Um par de expressões separado por uma vírgula é avaliado da esquerda para a direita, e o tipo e valor do resultado é o tipo e valor do operando da direita. Assim, em um **for**, é possível colocar múltiplas expressões em várias partes, por exemplo, para processar dois índices em paralelo. Este fato é ilustrado na função **reverse (s)**, que reverte a _string _ **s** no lugar.

```c
  /* reverse: reverte uma string s no lugar */
  #include <string.h>
  
  void reverse (char s[])
  {
    int c, i, j;
    
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--){
      c = s[i];
      s[i] = s[j];
      s[j] = c;
    }
  }
```

É importante salientar que as vírgulas que separam argumentos de funções, variáveis em declarações, etc., não são **operadores vírgula**, e não garantem avaliação da esquerda para direita.

O operador vírgula deve ser utilizado com moderação. Os usos mais adequados são para construções fortemente relacionadas, como no _loop **for**_ de **reverse** e em **macros** onde a computação multipasso tem que ser uma expressão única. Uma expressão com vírgula também pode ser apropriada para a troca de elemntos em **reverse**, a qual pode ser pensada como uma única operação, i.e.,

```c
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
```

### Loops - Do-while

Como discutido no Capítulo 1, os _loops **while**_ e _**for**_ testam a condição de terminação no topo. Por outro lado, o terceiro loop em C, o **do-while**, testa a condição no fim, **após** passar pelo corpo do _loop_, dessa forma, o corpo é executado pelo menos uma vez. A sintaxe do **do** é

```c
  do
    statement
  while (expressão);
```

O _statement_ é executado, então **expressão** é avaliada. Se é verdadeira, _statement_ é executado novamente, e assim segue. Quando a expressão tornar-se falsa, o _loop_ é encerrado. A experiência mostra que o **do-while** é bem menos utilizado do que **while** e **for**. Mesmo assim, por vezes, é a opção mais adequada. 

### Break and Continue

Em determinadas situações, é conveniente criar uma "saída" de um loop que não seja o teste (no topo ou no fim). O _statement_ **break** fornece uma saída antecipada do **for, while, do** e **switch**. Um **break** força a saída do _loop_ ou **switch** mais interno.

O _statement_ **continue** é relacionado ao **break**, apesar de menos utilizado; seu uso causa com que a próxima iteração do _loop_ **for**, **while** ou **do** comece. No caso do **while** e **do**, isso significa que a parte de teste é executada imediatamente; no **for**, o controle passa para o incremento. O **continue** não se aplica ao **switch**.

### Goto and Labels

O C fornece o _statement_ "infinitamente abusável" **goto** e _labels_ para ramificar. Formalmente, o **goto** nunca é necessário, e na prática é quase sempre mais fácil escrever o código sem isto. Neste livro, **goto** não é utilizado.

Todavia, há situações nas quais um **goto** é bem vindo. O mais comum é para abandonar processamento em uma estrutura muito aninhada, como sair de dois ou mais _loops_ de uma vez. Por exemplo,

```c
  for ( ... )
    for ( ... ) {
      ...
      if (disastre)
        goto erro;
    }
  ...
  
erro:
  limpe a bagunça
```

Uma _label_ tem a mesma forma de um nome de variável, e é seguida por um ponto e vírgula (_colon_). Pode ser anexada a qualquer _statement_ na mesma função que o **goto**. O alcance de uma _label_ é a função inteira.
  
  </div>
