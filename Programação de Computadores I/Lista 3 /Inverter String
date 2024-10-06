#include <stdio.h>
#include <string.h>

int main(void) {
  char string[100], stringinv[100];

  printf("Digite uma string:");
  fgets(string, 100, stdin);

  int tam = strlen(string);

  if (string[tam - 1] == '\n') {
    string[tam - 1] = '\0';
    tam--;
  }

  int j = tam - 1;

  for(int i = 0; j >= 0; i++) {
    stringinv[i] = string[j];
    j--;
  }

  stringinv[tam] = '\0'; 

  printf("String invertida: %s\n", stringinv);

  return 0;
}
