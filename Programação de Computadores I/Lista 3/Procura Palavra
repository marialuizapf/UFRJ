#include <stdio.h>
#include <string.h>

int procuraPalavra(char texto[], char palavra[]);

int main(void) {
  char texto[100], palavra[20];
  printf("Digite o texto:");
  fgets(texto, 100, stdin);
  texto[strcspn(texto, "\n")] = '\0';
  printf("Digite a palavra:");
  scanf("%s", palavra);

  int indice = procuraPalavra(texto, palavra);
  printf("Indice: %d", indice);
}

int procuraPalavra(char texto[], char palavra[]){
  int i , j = 0;

  for(i = 0; i < strlen(texto); i++){
    if(texto[i] == palavra[j]){
      j++;
    }else{
      j = 0;
    }
    if(j == strlen(palavra)){
      return i - j + 1;
    } 
  }
  return -1;
}
