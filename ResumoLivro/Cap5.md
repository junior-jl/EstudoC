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
