#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

  if(argc != 3) return 1;

  char *str1 = argv[1];
  
  FILE *str2 = fopen( argv[2], "r");
  if(str2 == NULL) return 1;

  char linha[81];
  int numero_de_linhas = 0;

  while(fgets(linha, sizeof(linha), str2) != NULL){
    numero_de_linhas++;
    if(strstr(linha, str1) != NULL){
      printf("%d %s", numero_de_linhas, linha);
    }
  }
  
  fclose(str2);
  return 0;
}

