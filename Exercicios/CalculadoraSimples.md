```c
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void main()
{

    setlocale(LC_ALL, "");

    // Calculadora simples

    //Declaração de variáveis
    float n1, n2, res;
    char op;

    //Ler valores
    printf("Insira o primeiro número \n");
    scanf("%f", &n1);
    while((getchar())!='\n');
    printf("Insira a operação (+,-,*,/) \n");
    scanf("%c", &op);
    printf("Insira o segundo número \n");
    scanf("%f", &n2);

    switch(op){

      case '+':
         res = n1 + n2;
         break;
      case '-':
         res = n1 - n2;
         break;
      case '*':
         res = n1 * n2;
         break;
      case '/':
         res = n1 / n2;
         break;
      default:
         printf("Opção inválida.");

    }
    if((op == '+') || (op == '-') || (op == '*') || (op == '/')){
      printf("RESULTADO: ");
      printf("%.2f %c %.2f = %.2f", n1,op,n2,res);
    }
}
```
