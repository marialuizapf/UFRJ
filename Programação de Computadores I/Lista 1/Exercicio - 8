/*
Autora: Maria Luiza Pinheiro Ferreira;
Proposta: Programa determina qual a quantidade máxima de bolos que podem ser feitos;
Entrada: Três números inteiros representando cada ingrediente;
Saída: A quantidade de bolos que podem ser feitos;
Defesa: Números menores que 2, 3 e 5.
*/

#include <stdio.h>

int main() {

  int A, B, C;
  int a, b, c;
  
  printf("Digite a quantidade de xícaras de farinha de trigo, ovos e colheres de sopa de leite.");
  scanf("%d%d%d", &A, &B, &C);
  
  if(A < 2 || B < 3 || C < 5){
      printf("Não é possível fazer a receita.");
  }
  else{
    
    a = A / 2;
    b = B / 3;
    c = C / 5;
  
    if(a <= b && a <= c){
       printf("É possível fazer %d bolo(s)", a);
    }
   else if(b <= a && b <= c){
       printf("É possível fazer %d bolo(s)", b);
    }
   else if(c <= a && c <= b){
         printf("É possível fazer %d bolo(s)", c);
    }
  }
return 0;
}
