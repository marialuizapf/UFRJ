/*
Autor: Maria Luiza Pinheiro
Data: 10/05/2023
Descrição: < um programa em C que imprime um triângulo isósceles de asteriscos com uma função chamada arvore que caso o parâmetro invertida seja diferente de 0 imprimir a pirâmede “de cabeça para baixo”>
Entrada: < o número de linhas da figura e o parâmetro invertida>
Saída: < um triângulo isósceles >
Defesa: < não pode ser maior que 10 e maior que 0 >
*/

#include <stdio.h>

void arvore(int linhas, int invertida);
int main(void) {
  int linhas;
  int invertida;
  printf("Digite a quantidade de linhas da figura e se será invertida, se não, digite 0:\n");
  scanf("%d %d", &linhas, &invertida);
  if( linhas > 10 || linhas < 0){
    printf("Número inválido!");
    return 1;
  }
  arvore(linhas, invertida);
  return 0;
}

void arvore(int linhas, int invertida){
  int i, j;
  if(invertida == 0){ 
    for(i = 1;i <= linhas;i++){
      for(j = 1; j <= linhas - i;j++){
        printf(" ");  
      }
      for(j = 1;j < i*2;j++){
        printf("*");
      }
      printf("\n");
    }
  }else{
    for(i = 1;i <= linhas;i++){
      for(j = 1;j <= i ;j++){
        printf(" ");
      }
      for(j = 0;j <= 2*(linhas - i);j++){
        printf("*");
      }
      printf("\n");
    }
  }
}
