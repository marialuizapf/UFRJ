#include <stdio.h>
#include <string.h>

void inicM(int n[3][3]){

  for(int i = 0; i < 3; i++){
    for(int j = 0 ; j < 3; j++){
      n[i][j] = 0;
    }
  }
  
}

void incluiElem (int n[3][3], int i, int j, int num){
  
  for(int l = 0; l < 3 ; l++){
    for(int c = 0; c < 3; c++){
      if(l == i && c  == j){
        n[i][j] = num;
      } 
    }
  }
}

void mostraM(int n[3][3]){

    for(int i = 0; i < 3; i++){
      for(int j = 0 ; j < 3; j++){
        printf("[%d]", n[i][j]);
      }
      printf("\n");
    }
  
}

int main (void){

  int matriz[3][3];
  int i = 1, j = 2, num = 10; 
  
  inicM(matriz);
  incluiElem(matriz, i, j, num);
  mostraM(matriz);
  
  return 0;
}
