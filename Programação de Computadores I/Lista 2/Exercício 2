/*
Autor: Maria Luiza Pinheiro
Data: 10/05/2023
Descrição: < um programa em C que imprime um triângulo isósceles de asteriscos>
Entrada: < o número de linhas da figura >
Saída: < um triângulo isósceles >
Defesa: < não pode ser maior que 10 e maior que 0 >
*/


#include <stdio.h>

int main(void) {
  int n, i, j;
  printf("Digite um número de 0 a 10:\n");
  scanf("%d", &n);
  if( n > 10 || n < 0 ){
    printf("Número inválido");
    return 0;
  }
  for(i = 1;i <= n;i++){
    for(j = 1;j <= n-i;j++){
      printf(" ");
    }
    for(j = 1;j <= 2*i - 1;j++){
      printf("*");
    }
    printf("\n");
  }
  
  return 0;
}
