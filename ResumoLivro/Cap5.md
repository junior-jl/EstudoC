# The C Programming Language - Ritchie and Kernighan (2nd edition)
## Chapter 5 - Pointers and Arrays

Um ponteiro é uma variável que contém o endereço de uma variável. Ponteiros são muito utilizados em C, parcialmente porque
às vezes são a única forma de expressar determinada computação, mas também porque geralmente levam a um código mais compacto e eficiente. Ponteiros e vetores são intimamente relacionados; este capítulo explora seu relacionamento e como explorá-lo.

A principal mudança no ANSI C é a explicitação das regras acerca de manipulação de ponteiros; e ainda, o tipo **void*** (ponteiro para **void**) substitui **char*** como o tipo padrão de um ponteiro genérico.

### Pointers and Addresses

Uma máquina típica tem um vetor de células de memória endereçadas, as quais podem ser manipuladas individualmente ou em grupos contíguos. Uma situação comum é que qualquer byte pode ser um **char**, um par de células de um byte pode ser tratado como um inteiro **short**, e quatro bytes adjacentes formam um **long**. Um ponteiro é um grupo de células (geralmente duas ou quatro) que armazena um endereço. Logo, se **c** é um **char** e **p** é um ponteiro que aponta para **c**, pode-se representar a situação como a figura abaixo.

![image](https://user-images.githubusercontent.com/69206952/140530161-fc93ebf3-1f71-4697-a7a7-e6b2e7999ade.png)

O operador unário **&** fornece o endereço de um objeto, portanto, o _statement_

```c
p = &c;
```

atribui o endereço de **c** à variável **p**, e é dito que **p aponta para c**. O operador **&** só é aplicável a objetos na memória: variáveis e elementos de vetor, não pode ser aplicado a expressões, constantes ou variáveis de registro.

O operador unário **\*** é a indireção (_indirection_) ou operador desreferenciamento (_dereferencing_); quando aplicado a um ponteiro, acessa o objeto para o qual o ponteiro aponta. Suponha que **x** e **y** são inteiros e **ip** é um ponteiro para **int**. A sequência artificial mostra como declarar um ponteiro e como usar **&** e **\***:

```c
  int x = 1, y = 2, z[10];
  int *ip; // ip é um ponteiro para int
  
  ip = &x; // ip agora aponta para x
  y = *ip; // y agora é 1
  *ip = 0; // x agora é 0
  ip = &z[0]; // ip agora aponta para z[0]
```

As declarações de **x**, **y** e **z** são como temos visto até aqui. A declaração do ponteiro **ip**,

```c
  int *ip;
```

é como um mnemônico; ela diz que a expressão **\*ip** é um **int**. A sintaxe da declaração para uma variável imita a sintaxe de expressões na qual a variável pode aparecer. Esse raciocínio se aplica a declaração de funções também. Por exemplo,

```c
  double *dp, atof (char*);
```

diz que uma expressão **\*dp** e **atof(s)** possuem valores do tipo **double** e que o argumento de **atof** é um ponteiro para **char**.

Cada ponteiro aponta para um tipo específico de dado. No entanto, há a exceção de um ponteiro para **void** que é utilizado para armazenar qualquer tipo de ponteiro mas que não pode ser "desreferenciado" a si mesmo (não entendi bem a tradução aqui). Tal ponteiro será tratado na seção 5.11.

Se **ip** aponta para o inteiro **x**, então **\*ip** pode ocrrer em qualquer contexto que **x** poderia, assim,

```c
  *ip = *ip + 10;
```

incrementa **\*ip** em 10.

Os operadores unários **\*** e **&** se "amarram mais fortemente" do que operadores aritméticos, assim, o _assignment_

```c
  y = *ip + 1
```

pega o que **ip** aponta, adiciona 1, e atribui o resultado a **y**, enquanto que

```c
  *ip += 1
```

incrementa o que **ip** aponta, da mesma forma que

```c
  ++*ip
```

e

```c
  (*ip)++
```

Os parênteses são necessários no último exemplo; sem eles, a expressão incrementaria **ip** ao invés do que este aponta, pois operadores unários como **\*** e **++** se associam da direita para a esquerda.

Finalmente, já que ponteiros são variáveis, podem ser usados sem "desreferenciamento". Por exemplo, se **iq** é outro ponteiro para **int**,

```c
  iq = ip
```

copia o conteúdo de **ip** em **iq**, fazendo com que **iq** aponte para o que **ip** aponta.

### Ponteiros e Argumentos de Função

Tendo em vista que C passa argumentos para função por valor, não há uma forma direta para a função chamada alterar uma variável na função que a chama. Por exemplo, uma rotina de ordenação pode trocar dois elementos fora de ordem com uma função chamada **swap**. Não é suficiente escrever

```c
  swap(a,b);
```

onde a função **swap** é definida como

```c
  void swap(int x, int y) // ERRADO!
  {
  int temp;
  
  temp = x;
  x = y;
  y = temp;
  }
```

Por conta da chamada por valor, **swap** não pode afetar os argumentos **a** e **b** na rotina que a chamou. A função acima apenas permuta **_cópias_** de **a** e **b**.

A maneira de obter o efeito desejado é fazendo com que a função "chamadora" passe ponteiros para os valores que devem ser alterados:

```c
  swap(&a,&b);
```

Já que o operador **&** produz o endereço de uma variável, **&a** é um ponteiro para **a**. Na própria função **swap**, os parâmetros devem ser declarados como ponteiros, e os operandos são acessados indiretamente por meio deles.

```c
  void swap(int *px, int *py) // alterna *px e *py
  {
  int temp;
  
  temp = *px;
  *px = *py;
  *py = temp;
  }

```

A figura abaixo resume o funcionamento.

![image](https://user-images.githubusercontent.com/69206952/140564721-8424f0f2-4d1f-48e5-bad7-86f65f58094d.png)

Argumentos ponteiro permitem que uma função acesse e modifique objetos na função que a chamou. Como exemplo, pode-se considerar uma função **getint** que performa conversão de entrada de formato livre quebrando uma stream de caracteres em valores inteiros, um inteiro por chamada. **getint** deve retornar o valor que encontrou e também sinalizar fim de arquivo caso não haja mais entrada. Estes valores devem ser passados de volta por caminhos separados, pois não importa qual valor seja utilizado para EOF, pode também ser usado como o valor de um inteiro de entrada.

Uma solução é fazer com que **getint** retorne o status de fim de arquivo como seu valor de função, enquanto usa um argumento de ponteiro para armazenar o inteiro convertido de volta para a função "chamadora". Este é o esquema utilizado por **scanf** (detalhado na seção 7.4).

O loop a seguir preenche um inteiro com inteiros por chamadas de **getint**:

```c
int n, array[SIZE], getint(int *);

for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
  ;
```

Cada chamada seta **array[n]** ao próximo inteiro encontrado na entrada e incrementa **n**. Note que é essencial passar o endereço de **array[n]** para **getint**. De outra forma, não é possível para **getint** comunicar o inteiro convertido de volta para a função que a chamou.

Nossa versão de **getint** retorna EOF para fim de arquivo, zero se a próxima entrada não for um número, e um valor positivo se a entrada contém um número válido.

```c
#include <ctype.h>

int getch(void);
void ungetch(int);

//getint: pega o próximo inteiro de uma entrada em *pn
int getint(int *pn)
{
  int c, sign;
  
  while (isspace(c = getch())) // pula espaços brancos
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    ungetch(c); // não é um número
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
  
}
```

Ao longo de **getint**, **\*pn** é utilizado como uma variável **int** comum. Também foram utilizados **getch** e **ungetch** descritas na seção 4.3 para que um caractere extra que deve ser lido possa ser jogado de volta na entrada.

### Ponteiros e Vetores

Em C, há um relacionamento forte entre ponteiros e vetores, forte o suficiente para que ponteiros e vetores devam ser discutidos simultaneamente. Qualquer operação que pode ser realizada por meio de subscritos de vetores pode ser obtida por meio de ponteiros. A versão com ponteiros, geralmente, será mais rápida, no entanto, para iniciantes, pode tornar-se mais difícil de entender.

A declaração

```c
  int a[10];
```

define um vetor **a** de tamanho 10, isto é, um bloco de 10 objetos consecutivos chamados **a[0],  a[1], ..., a[9]**.

![image](https://user-images.githubusercontent.com/69206952/140573398-df07064e-5b29-4945-ba55-b34293e269dc.png)

A notação **a[i]** se refere ao i-ésimo elemento do vetor. Se **pa** é um ponteiro para um inteiro, declarado como

```c
  int *pa;
```

então, o _assignment_

```c
pa = &a[0]
```

seta **pa** para apontar para o elemento zero de **a**; isto é, **pa** contém o endereço de **a[0]**.

![image](https://user-images.githubusercontent.com/69206952/140573589-1278d3f8-8ed8-4c24-ae73-b95be1a74bcf.png)

Agora, o _assignment_

```c
  x = *pa;
```

copiará o conteúdo de **a[0]** em **x**.

Se **pa** aponta para um elemento em particular de um vetor, então, por definição **pa + 1** aponta para o próximo elemento, **pa + i** aponta para **i** elementos após **pa**, e **pa - i** aponta para **i** elementos antes. Assim, se **pa** aponta para **a[0]**,

```c
  *(pa + 1)
```

se refere ao conteúdo de **a[1]**, **pa + i** é o endereço de **a[i]**, e **\*(pa + i)** é o conteúdo de **a[i]**.

![image](https://user-images.githubusercontent.com/69206952/140573935-d8e2aa21-d651-4fab-a88e-b988210e03d3.png)

Tais observações são verdadeiras independentemente do tipo ou tamanho das variáveis no vetor **a**. O significado de "adicionar 1 a um ponteiro", e, por extensão, toda a aritmética com ponteiros, é que **pa + 1** aponta para o próximo objeto, e **pa + i** para o i-ésimo objeto após **pa**.

A correspondência entre indexar e aritmética com ponteiros é bem próxima. Por definição, o valor de uma variável ou expressão do tipo vetor é o endereço do elemento zero do vetor. Assim, após o _assignment_

```c
  pa = &a[0];
```

**pa** e **a** possuem valores idênticos. Tendo em vista que o nome de um vetor é um sinônimo para a localização do elemento inicial, então, a atribuição **pa = &a[0]** pode ser reescrita simplesmente como

```c
  pa = a;
```

Ainda mais surpreendente, pelo menos à primeira vista, é o fato de que uma referência a **a[i]** pode ser escrita como **\*(a + i)**. Ao avaliar **a[i]**, C converte para **\*(a + i)** imediatamente; as duas formas são equivalentes. Aplicando o operador **&** a ambas as partes desta equivalência, segue que **&a[i]** e **a + i** são idênticos: **a + i** é o endereço do i-ésimo elemento após **a**. Do outro lado da moeda, se **pa** é um ponteiro, expressões podem usá-lo com um subscrito; **pa[i]** é idêntico a **\*(pa + i)**. Em resumo, uma expressão com vetor e índice é equivalente a uma com ponteiro e _offset_.

Há uma diferença entre um nome de vetor e um ponteiro que deve ser destacada. Um ponteiro é uma variável, logo, **pa = a** e **pa++** são expressões válidas. Mas, um nome de vetor não é uma variável; construções como **a = pa** e **a++** são ilegais.

Quando um nome de vetor é passado a uma função, o que é passado é a localização do elemento inicial. Dentro da função chamada, o argumento é uma variável local, e então um parâmetro _array name_ é um ponteiro, isto é, uma variável contendo um endereço. Pode-se utilizar este fato para escrever outra versão de **strlen**, que computa o comprimento de uma string.

```c
  // strlen : retorna o comprimento de uma string s
  int strlen(char *s)
  {
    int n;
    
    for (n = 0; *s != '\0'; s++)
      n++;
    return n;
  }
```

Já que **s** é um ponteiro, incrementá-lo é perfeitamente legal; **s++** não causa efeito na _string_ de caracteres na função que chamou **strlen**, meramente incrementa a cópia particular do ponteiro. Isso significa que chamadas como

```c
  strlen("hello, world"); // string constant
  strlen(array); // char array[100];
  strlen(ptr); // char *ptr;
```

funcionam.

Como parâmetros formais em uma definição de função,

```c
  char s[];
```

e 

```c
  char *s;
```

são equivalentes; preferimos o último porque diz mais explicitamente que o parâmetro é um ponteiro. Quando um nome de vetor é passado a uma função, a função pode - à sua conveniência - "acreditar" que foi fornecida ou um vetor ou um ponteiro, e manipulá-los de acordo. Pode-se até mesmo usar ambas as notações caso seja mais apropriado e claro.

É possível passar parte de um vetor a uma função, passando um ponteiro para o começo do subvetor. Por exemplo, se **a** é um vetor,

```c
  f(&a[2])
```

e

```c
  f(a + 2)
```

ambas passam à função **f** o endereço do subvetor que começa em **a[2]**. Dentro de **f**, a declaração do parâmetro pode ler

```c
  f(int arr[]) { ... }
```

ou

```c
  f(int *arr) { ... }
```

Logo, no que diz respeito a **f**, não há diferença se o parâmetro se refere à parte de um vetor maior ou não.

Se há certeza que os elementos existem, também é possível indexar um vetor de trás para frente; **p[-1], p [-2]**, e assim sucessivamente, são sintaticamente legais e se referem aos elementos que imediatamente precedem **p[0]**. Claro, é ilegal se referir a objetos que não estão dentro dos limites do vetor.

### Address Arithmetic

Se **p** é um ponteiro a algum elemento de um vetor, então **p++** incrementa **p** para apontar para o próximo elemento, e **p += i** o incrementa para apontar **i** elementos além de onde atualmente aponta. Estas e outras construções similares são as formas mais simples de aritmética com ponteiros ou endereços.

A linguagem C é consistente e regular na sua abordagem de aritmética de endereço. Sua integração de ponteiros, vetores, e _address arithmetic_ é uma das forças da linguagem. Vamos ilustrar escrevendo um alocador de armazenamento rudimentar. Há duas rotinas. A primeira, **alloc(n)**, retorna um ponteiro **p** para **n** posições de caracteres consecutivas, que podem ser utilizadas pela "chamadora" de **alloc** para armazenar caracteres. A segunda, **afree(p)**, libera o armazenamento adquirido para que possa ser reutilizado mais tarde. As rotinas são "rudimentares" porque as chamadas a **afree** podem ser feitas na ordem oposta às chamadas às chamadas feitas em **alloc**. Isto é, o armazenamento gerenciado por **alloc** e **afree** é um "monte" (_stack_) ou uma lista "último a entrar - primeiro a sair". A biblioteca padrão fornece funções análogas chamadas **malloc** e **free** que não possuem tais restrições; na seção 8.7 mostra-se como são implementadas.

A implementação mais fácil é fazer com que **alloc** distribua pedaços de um vetor de caracteres grande que nós chamaremos de **allocbuf**. Este vetor é particular a **alloc** e **afree**. Tendo em vista que lidam com ponteiros, não índices de vetores, nenhuma outra rotina precisa saber o nome do vetor, o qual pode ser declarado **static** no arquivo fonte contendo **alloc** e **afree**, tornando-se invisível para fora deste. Em implementações práticas, o vetor pode nem mesmo possuir um nome; ao invés disso, pode ser obtido chamando **malloc** ou "pedindo" ao sistema operacional (?) por um ponteiro para um bloco de armazenamento não nomeado.

As outras informações necessárias são: quanto de **allocbuf** está sendo utilizado. Nós usamos um ponteiro, chamado **allocp**, que aponta para o próximo elemento livre. Quando é requisitado a **alloc** n caracteres, esta checa se há espaço suficiente restante em **allocbuf**. Caso haja, **alloc** retorna o valor atual de **allocp** (i.e., o início do próximo bloco livre), e então incrementa-o com **n** para o ponto da próxima área livre. Se não há espaço, **alloc** retorna zero. **afree(p)** meramente seta **allocp** para **p** se **p** está dentro de **allocbuf**

![image](https://user-images.githubusercontent.com/69206952/140578495-75173d6d-a8cf-46b2-a705-566da1a6c550.png)

```c
  #define ALLOCSIZE 10000 // tamanho de espaço disponível
  
  static char allocbuf[ALLOCSIZE]; // armazenamento para alloc
  static char *allocp = allocbuf; // próxima posição livre
  
  char *alloc(int n) // retorna ponteiro para n caracteres
  {
    if (allocbuf + ALLOCSIZE - allocp >= n) { // se "cabe"
      allocp += n;
      return allocp - n; // p anterior
    } else // não há espaço suficiente
        return 0;
  }
  void afree(char *p) // libera o armazenamento apontado por p
  {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
      allocp = p;
  }
```

Em geral, um ponteiro pode ser inicializado como qualquer outra variável, embora normalmente os únicos valores significativos são zero ou uma expressão envolvendo endereços de dados previamente definidos do tipo apropriado. A declaração

```c
  static char *allocp = allocbuf;
```

define **allocp** como um ponteiro de caracteres e inicializa-o para apontar para o começo de **allocbuf**, que é a próxima posição livre quando o programa inicia. Isto também poderia ter sido escrito como

```c
  static char *allocp = &allocbuf[0];
```

já que o nome do vetor é o endereço do elemento 0.

O teste

```c
if (allocbuf + ALLOCSIZE - allocp >= n) { // se "cabe"
```

checa se há espaço suficiente para satisfazer um chamado para **n** caracteres. Se há, o novo valor de **allocp** seria, no máximo, um além do final de **allocbuf**. Se o pedido for satisfeito, **alloc** retorna um ponteiro para o início de um bloco de caracteres (note a declaração da própria função). Se não **alloc** deve retornar algum sinal de que não há espaço restante. C garante que zero nunca é um endereço válido para dados, logo, um retorno de valor zero pode ser utilizado para sinalizar uma anormalidade, neste caso, falta de espaço.

Ponteiros e inteiros não são intercambiáveis. Zero é a única exceção: a constante zero pode ser atribuída a um ponteiro, e um ponteiro pode ser comparado com a constante zero. A constante simbólica **NULL** é frequentemente usada no lugar do zero, como um mnemônico para indicar mais claramente de que é um valor especial para um ponteiro. **NULL** é definida em **<stdio.h>**. Utilizaremos **NULL** daqui em diante.

Testes como 

```c
  if (allocbuf + ALLOCSIZE - allocp >= n) { // se "cabe"
```

e

```c
  if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
```

mostram diversas facetas importantes da aritmética de ponteiros. Primeiro, ponteiros podem ser comparados em certas circunstâncias. Se **p** e **q** apontam para membros do mesmo vetor, então, as relações **==, !=, <, >=, etc** funcionam normalmente. Por exemplo,

```c
  p < q
```

é verdadeira se **p** aponta para um membro anterior a **q** do vetor. Qualquer ponteiro pode ser significativamente comparado por igualdade ou desigualdade com zero. Mas o comportamento é indefinido para aritmética ou comparações com ponteiros que não apontam para membros do mesmo vetor. (Há uma exceção: o endereço do primeiro elemento após o fim de um vetor pode ser usado em aritmética de ponteiros).

Em segundo lugar, já foi observado que um ponteiro e um inteiro podem ser somados ou subtraídos. A construção

```c
  p + n
```

significa que o endereço do n-ésimo objeto além do qual **p** aponta atualmente. Isso é verdadeiro independentemente do tipo de objeto que **p** aponta; **n** é dimensionado de acordo com o tamanho dos objetos para os quais **p** aponta, que é determinado na declaração de **p**. Se um **int** possui quatro bytes, por exemplo, o **int** será escalado por quatro. 

Subtração de ponteiros também é válida: se **p** e **q** apontam para elementos do mesmo vetor, e **p < q**, então **q - p + 1** é o número de elementos de **p** a **q** inclusivo. Este fato pode ser usado para escrever outra versão de **strlen**:

```c
  //strlen: retorna o comprimento de uma string s
  
  int strlen(char *s)
  {
    char *p = s;
    
    while (*p != '\0')
      p++;
    return p - s;
  }
```

Nesta declaração, **p** é inicializado com **s**, isto é, para apontar para o primeiro caractere da string. No loop **while**, cada caractere é examinado um a um até que **'\0'** seja visto. Por conta de **p** apontar para caracteres, **p++** avança **p** para o próximo caractere a cada vez, e **p - s** fornece o número de caracteres avançados, isto é, o comprimento da string. (O número de caracteres na string poderia ser grande demais para armazenar num **int**. O _header_ **<stddef.h>** define um tipo **ptrdiff_t** que é grande o suficiente para armazenar a diferença (com sinal) de dois valores de ponteiros. Se estivermos sendo muito cautelosos, no entanto, podemos utilizar **size_t** para o tipo de retorno de **strlen**, para corresponder à versão da biblioteca padrão. **size_t** é o tipo _unsigned integer_ retornado pelo operador **sizeof**).

A aritmética de ponteiros é consistente: se nós estamos lidando com **floats**, que ocupam mais armazenamento do que **chars**, e se **p** é um ponteiro para **float**, **p++** avançaria para o próximo **float**. Portanto, poderíamos escrever outra versão de **alloc** que mantém **floats** ao invés de **chars**, simplesmente mudando **char** para **float** ao longo de **alloc** e **afree**. Todas as manipulações de ponteiros automaticamente levarão em conta o tamanho do objeto para o qual apontam.

As operações com ponteiros válidas são: _assignment_ de ponteiros do mesmo tipo, adicionar ou subtrair um ponteiro e um inteiro, subtrair ou comparar dois ponteiros para membros do mesmo vetor, e atribuir ou comparar a zero. Qualquer outra aritmética com ponteiros é ilegal. Não é legal adicionar dois ponteiros, ou multiplicar, dividir, deslocar, mascarar, adicionar a **float** ou **double**, ou ainda, com a exceção de **void\***, atribuir um ponteiro de um tipo a um ponteiro de outro tipo sem um **cast**.

### Character Pointers and Functions

Uma _string constant_, escrita como

```c
  "Eu sou uma string"
```

é um vetor de caracteres. Na representação interna, o vetor é terminado por um caractere nulo **'\0'** para que o programa possa encontrar o fim. O comprimento no armazenamento é, então, um a mais do que o número de caracteres entre as aspas duplas.

Provavelmente a ocorrência mais comum de _string constants_ é como argumentos em funções, como em

```c
  printf("Hello, world\n");
```

Quando uma string de caracteres como essa aparece em um programa, o acesso a esta é feito por meio de um ponteiro de caractere; **printf** recebe um ponteiro para o começo do vetor de caracteres. Isto é, uma _string constant_ é acessada por um ponteiro para seu primeiro elemento.

_String constants_ não precisam ser argumentos de função. Se **pmessage** é declarado como

```c
  char *pmessage;
```

então, o _statement_

```c
  pmessage = "now is the time";
```

atribui a **pmessage** um ponteiro para o vetor de caracteres. Não há uma cópia da _string_; apenas ponteiros são envolvidos. C não fornece operadores para processar uma _string_ inteira como uma unidade.

Há uma diferença importante entre as seguintes definições:

```c
  char amessage[] = "now is the time"; // um vetor
  char *pmessage = "now is the time"; // um ponteiro
```

**amessage** é um vetor, de tamanho suficiente para guardar a sequência de caracteres e o **'\0'** que a finaliza. Caracteres individuais dentro do vetor podem ser alterados, mas **amessage** sempre se referirá ao mesmo armazenamento. Por outro lado, **pmessage** é um ponteiro, inicializado para apontar para uma _string constant_; o ponteiro pode ser modificado para apontar para outro lugar, mas o resultado é indefinido caso tente-se modificar o conteúdo da _string_.

![image](https://user-images.githubusercontent.com/69206952/140613830-2c596d9c-4bc6-448e-bc7c-0963627135ea.png)

Ilustraremos mais aspectos de ponteiros e vetores estudando versões de duas funções úteis adaptadas da biblioteca padrão. A primeira função é **strcpy(s,t)**, que copia a _string_ **t** para a _string_ **s**. Seria ótimo apenas escrever **s = t**, no entanto, isto copia o ponteiro, não os caracteres. Para copiar os caracteres, é necessário um loop. A versão com vetor é a primeira:

```c
  //strcpy: copia t para s; versão com vetores e subscritos
  void strcpy(char *s, char *t)
  {
    int i;
    
    i = 0;
    while ((s[i] = t[i]) != '\0')
      i++;
  }
```

Para fins de comparação, aqui está uma versão com ponteiros:

```c
  //strcpy: copia t para s; versão com ponteiros 1
  void strcpy(char *s, char *t)
  {
    while ((*s = *t) != '\0'){
      s++;
      t++;
    }
  }
```

Já que argumentos são passados por valor, **strcpy** pode usar os parâmetros **s** e **t** da forma que desejarem. Aqui, são ponteiros convenientemente inicializados, que "marcham" junto com os vetores um caractere por vez, até que o **'\0'** que termina **t** tenha sido copiado para **s**.

Na prática, **strcpy** não seria escrito como mostramos acima. Programadores C experientes prefeririam

```c
  //strcpy: copia t para s; versão com ponteiros 2
  void strcpy(char *s, char *t)
  {
    while ((*s++ = *t++) != '\0')
      ;
  }
```

Assim, o incremento de **s** e **t** é movido para a parte de teste do loop. O valor de **\*t++** é o caractere que **t** apontava antes de ser incrementado; o sufixo **++** não modifica **t** até que tal caractere tenha sido buscado. Da mesma forma, o caractere é armazenado na posição anterior de **s** antes de ser incremento. Este caractere é também o valor que é comparado com **'\0'**  para controlar o loop. O efeito de rede é que os caracteres são copiados de **t** para **s**, incluindo o terminador nulo.

Como última abreviação, observe que uma comparação com **'\0'** é redundante, já que a questão é meramente se a expressão é zero. Portanto, a função seria escrita como

```c
  //strcpy: copia t para s; versão com ponteiros 3
  void strcpy(char *s, char *t)
  {
    while (*s++ = *t++)
      ;
  }
```

Apesar de parecer enigmática à primeira vista, a conveniência notacional é considerável, e o _idiom_ deve ser dominado, pois será visto frequentemente em programas C.

A função **strcpy** na biblioteca padrão (**<string.h>**) retorna a string alvo como seu valor de função.

A segunda rotina que iremos examinar é **strcmp(s,t)**, que compara as strings de caracteres **s** e **t**, e retornam negativo, zero ou positivo se **s** é lexicograficamente menor que, igual a, ou maior que **t**. O valor é obtido subtraindo os caracteres na primeira posição na qual **s** e **t** "discordam".

```c
  // strcmp: retorna <0 se s<t, 0 se s==t, >0 se s>t
  int strcmp(char *s, char *t)
  {
    int i;
    
    for (i = 0; s[i] == t[i]; i++)
      if (s[i] == '\0')
        return 0;
    return s[i] - t[i];
  }
```

A versão de **strcmp** com ponteiros é:

```c
  // strcmp: retorna <0 se s<t, 0 se s==t, >0 se s>t
  int strcmp(char *s, char *t)
  {
    for ( ; *s == *t; s++, t++)
      if (*s == '\0')
        return 0;
    return *s - *t;
  }
```

Tendo em vista que **++** e **--** são operadores prefixos ou sufixos, outras combinações de **\*** e **++** e **--** podem ocorrer, apesar de menos frequentes. Por exemplo,

```c
  *--p
```

decrementa **p** antes de pegar o caractere para o qual **p** aponta. De fato, o par de expressões

```c
  *p++ = val; // leva val de volta para o monte
  val = *--p; // "pop" o topo do monte em val
```

são os _idioms_ padrões para _pushing_ e _popping_ um _stack_.

O _header_ **<string.h>** contém declarações para as funções mencionadas nesta seção, mais uma variedade de outras funções que lidam com strings.

### Pointer Arrays; Pointers to Pointers

Ponteiros são variáveis, portanto, podem ser armazenados em vetores da mesma forma que outras variáveis podem. Vamos ilustrar escrevendo um programa que ordena um conjunto de linhas de texto em ordem alfabética, uma versão despojada do programa UNIX **sort**.

No capítulo 3, foi apresentada uma função de ordenação Shell que ordenava um vetor de inteiros, e no capítulo 4, aperfeiçoamos com um **_quicksort_**. Os mesmos algoritmos funcionarão, exceto que agora nós temos que lidar com linhas de texto, que possuem comprimentos diferentes, e, diferentemente de inteiros, não podem ser comparados ou movidos numa única operação. Nós precisamos de uma representação de dados que lide eficientemente e convenientemente com linhas de texto de comprimento variável.

Aqui é onde o vetor de ponteiros entra. Se as linhas a serem ordenadas são armazenadas "end-to-end" em um longo vetor de caracteres, então cada linha pode ser acessada por meio de um ponteiro para o seu primeiro caractere. Os próprios ponteiros podem ser armazenados em um vetor. Duas linhas podem ser comparadas passando seus respectivos ponteiros para **strcmp**. Quando duas linhas fora de ordem precisarem ser trocadas, os ponteiros no vetor de ponteiros são trocados, não as linhas propriamente ditas. 

![image](https://user-images.githubusercontent.com/69206952/140615031-33ebec46-02e3-400c-ab6b-df0af68b518c.png)

Isso elimina os problemas de sobrecarga e gerenciamento de memória que ocorreriam para movimentar as linhas em si.

O processo de ordenação possui três etapas:

```c
  leia todas as linhas da entrada
  ordene-as
  imprima-as em ordem
```

Como de costume, é melhor dividir o programa em funções que correspondam a esta divisão natural, com a rotina principal controlado as outras funções. Vamos adiar a etapa de ordenação por um momento e concentrar-se na estrutura dos dados e a entrada e saída.

A rotina de entrada deve coletar e salvar os caracteres de cada linha, e construir um vetor de ponteiros para as linhas. Ela também deve contar o número de linhas de entrada, já que esta informação é necessária para ordenar e imprimir. Já que a função de entrada só pode lidar com um número finito de linhas, pode retornar algum valor ilegal de contagem como -1 se muita entrada é fornecida.

A rotina de saída deve apenas imprimir as linhas na ordem que aparecem no vetor de ponteiros.

```c
  #include <stdio.h>
  #include <string.h>
  
  #define MAXLINES 5000 // máximo de #linhas para serem ordenadas
  
  char *lineptr[MAXLINES]; // ponteiros para as linhas de texto
  
  int readlines(char *lineptr[], int nlines);
  void writelines(char *lineptr[], int nlines);
  void qsort(char *lineptr[], int left, int right);
  
  //ordena linhas de entrada.
  
  main()
  {
    int nlines; // número de linhas de entrada lidas
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
      qsort(lineptr, 0, nlines-1);
      writelines(lineptr, nlines);
      return 0;
    } else {
        printf("erro: entrada muito grande para ordenar\n");
        return 1;
    }
  }
  
  #define MAXLEN 1000 // máximo comprimento de uma linha de entrada
  int getline(char *, int);
  char *alloc(int);
  
  //readlines: lê linhas de entrada
  int readlines(char *lineptr[], int maxlines)
  {
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    while ((len = getline(line, MAXLEN)) > 0)
      if (nlines >= maxlines || (p = alloc(len)) == NULL)
        return -1;
      else {
        line[len - 1] = '\0'; // deleta newline
        strcpy(p, line);
        lineptr[nlines++] = p;
      }
    return nlines;
  }
  
  //writelines: escreve linhas de saída
  void writelines(char *lineptr[], int nlines)
  {
    int i;
    
    for (i = 0; i < nlines; i++)
      printf("%s\n", lineptr[i]);
  }
```

A função **getline** é mostrada na seção 1.9.

A principal coisa nova é a declaração para **lineptr**:

```c
  char *lineptr[MAXLINES]
```

diz que **lineptr** é um vetor de **MAXLINES** elementos, cada elemento é um ponteiro para **char**. Isto é, **lineptr[i]** é um ponteiro para caractere, e **\*lineptr[i]** é o caractere para o qual este aponta, o primeiro caractere da i-ésima linha de texto salva.

Já que **lineptr** é o nome de um vetor, este pode ser tratado como um ponteiro da mesma forma que nos exemplos anteriores, e **writelines** pode ser escrita como

```c
  //writelines: escreve linhas de saída
  void writelines(char *lineptr[], int nlines)
  {
    while (nlines-- > 0)
      printf("%s\n", *lineptr++);
  }
```

Inicialmente, **\*lineptr** aponta para a primeira linha; cada incremento o avança para o ponteiro da próxima linha enquanto **nlines** é contado regressivamente.

Com a entrada e saída sob controle, podemos prosseguir para a ordenação. O **quicksort** do capítulo 4 precisa de mudanças pequenas: as declarações precisam ser modificadas, e a operação de comparação deve ser feita por **strcmp**. O algoritmo permanece o mesmo, o que nos dá confiança de continuará funcionando.

```c
  //qsort: sort v[left] ... v[right] em ordem decrescente
  void qsort(char *v[], int left, int right)
  {
    int i, last;
    void swap(char *v[], int i, int j);
    
    if (left >= right) // não faz nada se o vetor contém menos de dois elementos
      return;
    swap(v, left, (left+right)/2);
    last = left;
    for (i = left + 1; i <= right; i++)
      if (strcmp(v[i], v[left]) < 0)
        swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
  }
```

Similarmente, a rotina **swap** precisa apenas de mudanças triviais:

```c
  // swap: intercambia v[i] e v[j]
  void swap(char *v[], int i, int j)
  {
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
  }
```

Tendo em vista que qualquer elemento individual de **v** (ou **lineptr**) é um ponteiro de caractere, **temp** também deve ser, para que um possa ser copiado para o outro.

### Multi-dimensional Arrays

C fornece vetores multidimensionais retangulares, apesar de que na prática são muito menos usados em comparação a vetores de ponteiros. Nesta seção, iremos mostrar algumas de suas propriedades.

Considere o problema de conversão de data, de dia do mês para dia do ano e vice-versa. Por exemplo, dia 1 de março é dia 60 de um ano não-bissexto, e o dia 61 de um ano bissexto. Vamos definir duas funções para fazer as conversões: **day_of_year** converte o mês e dia em um dia do ano, e **month_day** converte o dia do ano em um mês e dia. Já que a última função computa dois valores, os argumento mês e dia serão ponteiros:

```c
  month_day(1988, 60, &m, &d)
```

seta **m** para 2 e **d** para 29 (29 de fevereiro).

Ambas as funções precisam da mesma informação, uma tabela do número de dias em cada mês. Já que o número de dias por mês difere para anos bissextos ou não, é mais simples separá-los em duas linhas de um vetor de duas dimensões do que observar o que acontece em fevereiro durante a compilação. O vetor e as funções para performar as transformações são como mostrados a seguir:

```c
  static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
  };
  
  //day_of_year : seta o dia do ano para mês e dia
  int day_of_year(int year, int month, int day)
  {
    int i, leap;
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; i++)
      day += daytab[leap][i];
    return day;
  }
  
  //month_day: seta mês, dia de um dia do ano
  void month_day(int year, int yearday, int *pmonth, int *pday)
  {
    int i, leap;
    
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
      yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
  }
```

Relembre que o valor aritmético de uma expressão lógico, como em **leap**, é ou 0 (falsa) ou 1 (verdadeira), portanto, pode ser utilizada como subscrito no array **daytab**.

O vetor **daytab** deve ser externo a **day_of_year** e **month_day** para que ambas possam utilizá-lo. Utilizamos **char** para ilustrar um uso legítimo de **char** para armazenar pequenos inteiros não-caracteres.

**daytab** é o primeiro vetor bidimensional que lidamos. Em C, um vetor de duas dimensões é, na verdade, um vetor de uma dimensão cujos elementos são um vetor. Dessa forma, os subscritos são escritos como

```c
  daytab[i][j] // [linha][coluna]
```

ao invés de

```c
  daytab[i,j] // ERRADO
```

Além dessa notação, um vetor de duas dimensões pode ser tratado basicamente da mesma forma que em outras linguagens. Elementos são armazenados por linhas, para que o subscrito mais à direita, ou coluna, varie mais rápido ao passo que elementos são acessados na ordem de armazenamento.

Um vetor é inicializado por uma lista de inicializadores entre chaves; cada linha de um vetor de duas dimensões é inicializada por uma sublista correspondente. Nós iniciamos o vetor **daytab** com uma coluna de zeros para que o número do mês possa correr normalmente de 1 a 12 ao invés de 0 a 11.

Se um vetor de duas dimensões é passado a uma função, a declaração do parâmetro na função deve incluir o número de colunas; o número de linhas é irrelevante, já que o que é passado, assim como antes, é um ponteiro para um vetor de linhas, onde cada linha é um vetor de 13 **ints**. Neste caso particular, é um ponteiro para objetos que são vetores de 13 **ints**. Assim, se o vetor **daytab** é passado a uma função **f**, a declaração de **f** seria

```c
  f(int daytab[2][13]) { ... }
```

Também poderia ser

```c
  f(int daytab[][13]) { ... }
```

já que o número de linhas é irrelevante, poderíamos escrever

```c
  f(int (*daytab)[13]) { ... }
```

que diz que o parâmetro é um ponteiro para um vetor de 13 inteiros. Os parênteses são necessários, pois os colchetes **[ ]** possuem maior precedência do que **\***. Sem parênteses, a declaração

```c
  int *daytab[13]
```

é um vetor de 13 ponteiros para inteiros. De forma mais geral, somente a primeira dimensão (subscrito) de um vetor é livre; todas as outras devem ser especificadas. Na seção 5.12 há uma discussão mais aprofundada sobre declarações complicadas.

### Initialization of Pointer Arrays

Considere o problema de escrever uma função **month_name(n)**, que retorna um ponteiro para uma string de caracteres contendo o nome do n-ésimo mês. Está é uma aplicação ideal para um vetor **static**. **month_name** contém um vetor privativo de strings, e retorna um ponteiro para a string apropriada quando chamada. Esta seção mostra como este vetor de nomes é inicializado.

A sintaxe é similar à inicializações anteriores:

```c
  // month_name: retorna nome do n-ésimo mês
  char *month_name(int n)
  {
    static char *name[] = {
    "Illegal month",
    "January", "February", "March",
    "April", "May", "June",
    "July", "August", "September",
    "October", "November", "December"
    };
    
    return (n < 1 || n > 12) ? name[0] : name[n];
  }
```

A declaração de **name**, que é um vetor de ponteiros a caracteres, é similar à declaração de **lineptr** no exemplo de ordenação. O inicializador é uma lista de strings de caracteres; cada uma é atribuída à sua posição correspondente no vetor. Os caracteres da i-ésima string são colocados em algum lugar, e um ponteiro para estes é armazenado em **name[i]**. Já que o tamanho do vetor **name** não é especificado, o compilador conta os inicializadores e preenche com o número correto.

### Pointers vs. Multi-dimensional Arrays
