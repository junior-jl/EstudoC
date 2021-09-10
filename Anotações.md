# Anotações

- **Problema com variáveis tipo char**

Antes de o valor ser designado a uma variável *char*, passa pelo buffer (espaço de memória temporário).

Pode haver "lixo" no buffer, então, antes de ler um valor para uma variável *char*, deve-se limpar o buffer.

**Recomendação do curso**: "fflush (stdin);" depois de um scanf.

De acordo com alguns sites, essa função tem comportamento indefinido, então, recomenda-se utilizar:

```c

while((getchar())!='\n'); ------- C

```

```cpp

std::cin >> ws ------- C++

```

- **Valor absoluto (abs)**

Aparentemente, a função abs() só funciona para valores inteiros, para float deve-se utilizar fabs();

- **Char (ASCII)**

Eu posso imprimir um char a partir de uma variável inteira (com o código ASCII correto) e também posso imprimir o inteiro através do char...

```c
int a = 120;

char b = 'x';

printf("%c", a); --------- imprime "x"

printf("%d", b); --------- imprime "120"
```

- **Geração de número aleatório**

A função rand() gera um número pseudo-aleatório. No entanto, precisa de um valor "semente" para tal, caso não seja informado nenhum valor, a função assume srand(1), assim, para que não haja repetição da sequência de valores gerados, utiliza-se a seguinte linha de código antes da geração (deve-se incluir a biblioteca time.h):

```c
srand(time(0))
```

- **Trabalhando com strings**

Para trabalhar com "palavras", cria-se um vetor de _chars_. No entanto, antes de receber uma palavra da entrada de dados principal _stdin_ deve-se limpar o _buffer_ através do seguinte comando:

```c
setbuf(stdin,0)
```

Agora, ao invés da função _scanf()_ utiliza-se _fgets()_...

```c
fgets( char          *str, int count, FILE          *stream );
```

Os parâmetros da função são:

1. str	-	ponteiro para um elemento de arranjo _char_
2. count	-	número de máximo de caracteres para escrever (geralmente o tamanho de str)
3. stream	-	fluxo de arquivo pelo qual o dado será lido

Para evitar o uso de "slots" desnecessários de vetor, faz-se a seguinte correção. Suponha a string **palavra**, a linha de código a seguir faz com que o vetor **palavra** tenha apenas o tamanho necessário para comportar a string recebida. O caracter \0 é conhecido como **terminador nulo** e indica o final de uma _string_.

```c
palavra[strlen(palavra-1)] = '\0' /////// Ou seja, após o último char do vetor, teremos \0
```

Para imprimir uma _string_, utiliza-se %s.

Em C++, apenas a inclusão das bibliotecas <string> e <iostream> permite trabalhar com _strings_ de modo simples, sem os problemas citados anteriormente.

