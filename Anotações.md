# Anotações

- **Problema com variáveis tipo char**

Antes de o valor ser designado a uma variável *char*, passa pelo buffer (espaço de memória temporário).

Pode haver "lixo" no buffer, então, antes de ler um valor para uma variável *char*, deve-se limpar o buffer.

**Recomendação do curso**: "fflush (stdin);" depois de um scanf.

De acordo com alguns sites, essa função tem comportamento indefinido, então, recomenda-se utilizar:

```c

while((getchar())!='\n'); ------- C

```

```c++

cin >> ws ------- C++

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

- Geração de número aleatório

A função rand() gera um número pseudo-aleatório. No entanto, precisa de um valor "semente" para tal, caso não seja informado nenhum valor, a função assume srand(1), assim, para que não haja repetição da sequência de valores gerados, utiliza-se a seguinte linha de código antes da geração (deve-se incluir a biblioteca time.h):

```c
srand(time(0))
```
