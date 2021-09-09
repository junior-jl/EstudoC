# Anotações

- **Problema com variáveis tipo char**

Antes de o valor ser designado a uma variável *char*, passa pelo buffer (espaço de memória temporário).

Pode haver "lixo" no buffer, então, antes de ler um valor para uma variável *char*, deve-se limpar o buffer.

**Recomendação do curso**: "fflush (stdin);" depois de um scanf.

De acordo com alguns sites, essa função tem comportamento indefinido, então, recomenda-se utilizar:

while((getchar())!='\n'); ------- C

cin >> ws ------- C++

- **Valor absoluto (abs)**

Aparentemente, a função abs() só funciona para valores inteiros, para float deve-se utilizar fabs();
