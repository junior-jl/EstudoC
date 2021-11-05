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

