#include <stdio.h>
int main() {
  char letra;
  char cifra = 'a';
  printf("Digite uma letra: ");
  letra = getchar();

  if (!((letra >= 'A' && letra <= 'Z' || letra >= 'a' && letra <= 'z'))) {
    printf("Caractere invalido");
    return 0;
  }
  
  cifra = letra + 12;
  int contador = 0;

  if( cifra >= 'A' && cifra <= 'Z' || cifra >= 'a' && cifra <= 'z' ){
      contador++;
  } else if (cifra > 'z' && letra >= 'a' && letra <= 'z'){
    cifra = cifra - 'z' + 'a' - 1;
    contador++;
  } else if (cifra > 'Z' && letra >= 'A' && letra <= 'Z'){
    cifra -= 'Z'; 
    cifra += '@';
    contador++;
  }

  while (contador <= 3 && letra == 'E') {
    printf("Digite uma nova letra! ");
    return 0;
  }
  printf("A cifra de %c eh %c", letra, cifra);
  return 0;
}
