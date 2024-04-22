/*
Autora: Maria Luiza Pinheiro Ferreira;
Proposta: Programa que retorna a idade quando dada em dias para o formato de  ano(s), mes(es) e dia(s).;
Entrada: Um número inteiro;
Saída: A quantidade de anos, meses e dias de vida de alguém;
Defesa: Números negativos.
*/

#include <stdio.h>

int main() {

  int idade;

  printf("Digite a idade em dias.");
  scanf("%d", &idade);

    int anos = idade / 365;
    int meses = (idade % 365) / 30;
    int dias = (idade % 365) % 30;

    if (meses == 12) {
       anos = anos + 1; 
       meses = 0;
    }

    if (dias == 30) {
       meses = meses + 1; 
       dias = 0;
    }

    else if (idade < 0) {
       printf("A idade não pode ser negativa!");
       return 0;
    }

  printf("A idade é correspondente a: %d ano(s), %d mes(es), %d dia(s)", anos, meses, dias);
  return 0;
}
