/*
Autor: Maria Luiza Pinheiro
Data: 28/04/2023
Descrição: < calcule x elevado a y sem pow ()>
Entrada: < dois números inteiros x e y >
Saída: < x elevado a y>
Defesa: < x deve ser diferente de zero e y deve ser maior ou igual a zero>
*/

#include <stdio.h>
int main() {
  int x, y;
  int i = 1;
  printf("Digite dois números inteiros x e y, onde x é diferente de zero e y maior ou igual a zero:\n");
  scanf("%d %d", &x, &y);

  if (x == 0 || y < 0 ){
    printf("Erro");
    return 0;
  }

  do { i *= x; 
    y--;
  }while (y > 0);
  
  printf("O valor de x elevado a y é: %d\n", i);

return 0;
}
