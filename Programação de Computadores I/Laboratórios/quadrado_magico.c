#include <stdio.h>
int main() {

int m, n;
int matriz[99][99];
printf("Diga a quantidade de linhas da matriz:");
scanf("%d %d", &m, &n);
  if(m <= 1){
    printf("Erro");
    return 0;
  }  
  if(m != n){
      printf("Deve ser o msm numero");
      return 0;
  }
printf("Diga os valores da matriz:");
  for(int i=0;i < n;i++)
    for(int j=0;j < m;j++)
      scanf("%d", &matriz[i][j]);
int i=1;
int soma = 0;
  //soma diagonal principal
  for (i = 0; i < n; i++) {
    soma += matriz[i][i];
  }
int soma2=0;
  //soma diagonal secundaria
  for (i = 0; i < n; i++) {
    soma += matriz[i][i];
  }
int lin=0;
  //soma coluna
  for (int i=0;i < n;i++)
    for(int j=0;j < m;j++)
      if(j == m - i){
        soma += matriz[i][j];
        i++;
      }
int col=0;
  //soma linha
  for (int i=0;i < n;i++)
    for(int j=0;j < m;j++)
      if(j == m - i){
        soma += matriz[i][j];
        i++;
      }
if(col||lin||soma||soma2 == 15){
  printf("Verdadeiro");
}else {
  printf("Falso");
}
return 0;
}
