#include <stdio.h>

int totalLEDS(int n);
int ledsAlgarismo(int alg);

int main(void) {
  int n;
  printf("Digite um número inteiro:\n");
  scanf("%d", &n);
  printf ("A quantidade de LEDs necessária para representar o número %d é %d", n,     totalLEDS(n));
}

int totalLEDS(int n){
  int alg;
  int qtdLEDS = 0;
  
  do { alg = n % 10;
       n = n / 10;
      qtdLEDS += ledsAlgarismo(alg);
  } while ( n != 0);
  return qtdLEDS;
}

int ledsAlgarismo(int alg){
  int a;
  
  switch (alg){
    case (1) :
      a = 2;
      break;

    case (2) :
    case (5) :
    case (3) :
      a = 5;
      break;

    case (4) :
      a = 4;
      break;

    case (6) :
    case (0) :
    case (9) :
      a = 6;
      break;

    case (7) :
      a = 3;
      break;

    case (8) :
      a = 7;
      break;

    default :
      printf ("Valor invalido!\n");
  }
  return a;
}
