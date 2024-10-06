#include <stdio.h>

int main (void){

  int x;
  int i = 0;
  int j = 0;
  printf("Digite a quantidade de linhas de 1 a 10 que você gostaria que sua figura tenha:\n");
  scanf("%d", &x);

  if( x <= 0 || x > 10 ){
    printf("Erro: Digite uma quatidade de linhas dentro da faixa de números indicada!");
      return 1;
  }

  while( i < x ){
    i++;
    printf("*");
    while( j < x - i ){
      j++;
      printf("*");
    }
    printf("\n");
    j = 0;
  }
  
  return 0;
}
