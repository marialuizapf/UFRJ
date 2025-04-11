#include <stdio.h>
#include <string.h>

int vogais(char *str){

  int contador = 0;
  while(*str != '\0'){

    if(*str == 'a' || *str == 'e' || *str == 'i' || *str == 'o'|| *str == 'u'||  *str == 'A' || *str == 'E' || *str == 'I' || *str == 'O'|| *str == 'U'){
      contador++;
    }
    str++;
  }

  return contador;
}

int main (void){

  char str[100];

  printf("Escreva uma frase:");
  fgets(str, 100, stdin);

  str[strcspn(str, "\n")] = '\0';

  printf("Número de vogais é: %d\n", vogais(str));
  return 0;
}
