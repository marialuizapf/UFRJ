#include <stdio.h>

int main(void) {
  
  void tabuada(int n);
  
  int n;
  printf("Digite um número de 1 a 10:\n");
  scanf("%d", &n);
  
  if (n < 1 || n > 10) {
    printf("Número inválido!");
    return 1;
  } else { 
    tabuada(n);
  }
  return 0;
}

void tabuada(int n){
  int i = 1;
    while(i <= 10){
      printf("%d x %d = %d\n", n, i, n * i);
      i++;
    }
}
