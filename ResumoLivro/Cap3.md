# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 3 - Control Flow

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
