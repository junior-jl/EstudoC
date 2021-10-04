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
palavra[strlen(palavra)-1] = '\0' /////// Ou seja, após o último char do vetor, teremos \0
```

Para imprimir uma _string_, utiliza-se %s.

Em C++, apenas a inclusão das bibliotecas <string> e <iostream> permite trabalhar com _strings_ de modo simples, sem os problemas citados anteriormente.
  
- **Ponteiros**
  
Variáveis armazenam valores. Ponteiros armazenam endereços de memória.
  
Utiliza-se o asterisco para trabalhar com ponteiros, assim, para definir o ponteiro "x", tem-se:

```c
int *x;
```

Assim, ao usar o asterisco novamente, pode-se alterar o conteúdo da memória para o qual o ponteiro x aponta. Por exemplo, se há uma variável "a" e o ponteiro x aponta para o endereço de "a", posso alterar o conteúdo da variável "a" da seguinte forma:
  
```c
int a; // Declaração da variável a
int *x; // Declaração do ponteiro x
x = &a; // O ponteiro x recebe o endereço da variável a
*x = 20; // O conteúdo apontado pelo ponteiro x recebe 20
```
  
- **Limpar a tela**
  
```
  system("CLS");
```

- **Implementação de função expoente para inteiros**
  
A função pow() da biblioteca math.h parece problemática, então implementei a função intpow() a seguir... Obviamente tem seus limites, porém teve resultado satisfatório até o momento.
  
  ```c
  int intpow(int base, int exp){
   int i,res, aux = base;
   if(exp == 0){
      res = 1;
   }else{

   for(i=2;i<=exp;i++){
   base = base*aux;
   res = base;
   }
}
   return res;
}

  ```

- **_goto_ statement**
                       
 Define-se uma _label_ em alguma linha do código, o _goto_ faz com que o programa salte para a _label_, isto é, no exemplo abaixo, o programa imprime na tela "blabla" e salta para _label_, imprimindo novamente (neste caso indefinidamente).
                       
 ```c
  label:
  printf("blabla");
  goto label;
 ```
                       
- **Função strcmp()**    

É uma função da biblioteca string.h, serve para fazer comparação entre strings.
                       
```c
int strcmp( const char *lhs, const char *rhs );                     
```           
                       
A função tem três possíveis retornos:
                       
1. 0 se _lhs_ e _rhs_ são strings iguais;
2. Valor negativo se _lhs_ precede _rhs_ em ordem lexicográfica;
3. Valor positivo se _lhs_ sucede _rhs_ em ordem lexicográfica.                       

- **Alocação dinâmica de memória**
                       
Provavelmente essa função é a solução para o problema do "vetor variável". A função
                       
```c
malloc(size_t)
```
                       
pertence a biblioteca _stdlib.h_ e aloca bytes de armazenamento. Essa função retorna um ponteiro para a posição do primero byte alocado.     
                       
Quando o espaço de memória alocado não for mais necessário, é interessante utilizar a função free() para "desalocar" o espaço de memória. 
                       
Em C++, utiliza-se a biblioteca <new> e a função new() para alocação de memória. O seguinte código é um exemplo de alocação dinâmica de memória em C++, no qual a variável "tamanho" foi previamente iniciada com o tamanho desejado do vetor.
  
```
  int *vetor = new int[tamanho];
```
