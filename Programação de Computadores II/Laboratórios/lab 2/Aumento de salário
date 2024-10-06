#include <stdio.h>

void aumento(int *sal, int aum){

  *sal = *sal + (*sal * aum /100);

}

int main (void){

  int sal, aum;
  printf("Digite o salário:");
  scanf("%d", &sal);

  printf("Digite o percentual de aumento:");
  scanf("%d", &aum);

  aumento (&sal, aum);
  printf("O novo salário é: %d", sal);
  
  return 0;
}
