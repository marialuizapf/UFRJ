#include <stdio.h>
#include <string.h>

void converteParaMaiusculas(char texto []);

int main(void){

  char texto [100];
  char textoMa[100];
  printf("Digite um texto: ");
  fgets(texto, 100, stdin);
  texto[strcspn(texto, "\n")] = '\0';

  converteParaMaiusculas(texto);
   printf("String convertida para maiúsculas: %s\n", texto);
}

void converteParaMaiusculas(char texto []){
  int tam = strlen(texto);
  for(int i = 0;i < tam;i++){
    if(texto[i] >= 'a' && texto[i] <= 'z'){
      texto[i] = texto[i] - 32;
    }
  }
}
