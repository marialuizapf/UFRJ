#include <stdio.h>
#include <stdlib.h>

int **aloca_linhas(int lin);
void aloca_colunas (int **matriz, int lin, int col);
void le_dados(int **matriz, int lin, int col);
void imprime_matriz(int **matriz, int lin, int col);
void troca_linhas (int **matriz, int linha1, int linha2);

int main (void) {
  int **matriz;
  int lin, col;
  int linha1, linha2;
  
  puts("Qual o numero de linhas?");
  scanf("%d",&lin);
  
  matriz = aloca_linhas(lin);
  
  puts("Qual o numero de colunas?");
  scanf("%d",&col);
  
  printf("Alocando espaço para linhas.\n");
  
  aloca_colunas(matriz, lin, col);
  
  le_dados(matriz, lin, col);
  
  imprime_matriz(matriz, lin, col);
  
  puts("Qual a primeira linha a ser trocada?");
  scanf("%d",&linha1);
  
  puts("Qual a segunda linha a ser trocada?");
  scanf("%d",&linha2);
  
  troca_linhas(matriz, linha1, linha2);
  
  imprime_matriz(matriz, lin, col);
  
  return 0;
}

int **aloca_linhas(int lin){
  
  int **matriz;
  matriz = (int**)malloc(lin * sizeof(int *));
  if (!matriz) exit(1);

  return matriz;
}

void aloca_colunas (int **matriz, int lin, int col){

  for(int i = 0; i < lin; i++){
    *(matriz + i) = (int *)malloc(col * sizeof(int));
    if (!*(matriz + i)) exit(1);
  }
}

void le_dados(int **matriz, int lin, int col){

  for(int i = 0;i < lin;i++){
    for(int j = 0;j < col;j++){
      printf("Elemnto [%d][%d]: ",i,j);
      scanf("%d",&matriz[i][j]);
    }
  }
}

void imprime_matriz(int **matriz, int lin, int col){

    for(int i = 0;i < lin;i++){
      for(int j = 0;j < col;j++){
        printf("[%d]", matriz[i][j]);
      }
      printf("\n");
    }
}

void troca_linhas (int **matriz, int linha1, int linha2){

  int lin;
  if (lin < 0 || lin > linha1 || lin > linha2) exit(1);
  int *temp = matriz[linha1]; 
  matriz[linha1] = matriz[linha2];
  matriz[linha2] = temp;
}
