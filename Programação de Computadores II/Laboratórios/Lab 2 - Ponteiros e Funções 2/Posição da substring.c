#include <stdio.h>
#include <string.h>

int posicao(char *substr, char *str){

  int aux = 0;
  int leng = strlen(substr);
  for(int i = 0; str[i] != '\0'; i++){

    if(str[i] == substr[aux]){
      aux++;
    } else{
      aux = 0;
    }
    if (aux == leng){
      return i - leng + 2;
    }
  }
  return -1;
}

int main(void){

  char str[100], substr [100];
  printf("Digite a string:\n");
  fgets(str, sizeof(str), stdin);
  printf("Digite a substring:\n");
  fgets(substr, sizeof(substr), stdin);

  str[strlen(str)-1] = '\0';
  substr[strlen(substr)-1] = '\0';

  int pos = posicao(substr, str);
  if(pos == -1){
    printf("Substring não encontrada\n");
  }else{
  printf("A substring está na posição %d da string", pos);
  }
  return 0;
}
