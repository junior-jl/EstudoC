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
