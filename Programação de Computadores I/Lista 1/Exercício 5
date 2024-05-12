/*
Autor: Maria Luiza Pinheiro
Data: 10/05/2023
Descrição: < um programa que leia um número natural n e dois números naturais a e b diferentes de 0 e apresente na tela em ordem crescente os n primeiros naturais que são múltiplos de a ou de b>
Entrada: < os números naturais n , a e b >
Saída: < n primeiros naturais que são múltiplos de a ou de b >
Defesa: < os números não podem ser menor que 0 >
*/

#include<stdio.h>

int ehMultiplo(int r, int s);
void multiplos(int q, int x, int y);
int main(){
  int q, x, y;
  printf("Digite três números naturais: n, a e b. Com n sendo os n primeiros naturais que são múltiplos de a ou b:\n");
  scanf("%d %d %d", &q, &x, &y); 
  multiplos(q, x, y);
  return 0;
  if(q<0 || x<0 || y<0){
    printf("Número inválido");
    return 0;
  }
}

void multiplos(int q, int x, int y){
  int r = 0, contador = 0;
  while(contador < q){
    if(ehMultiplo(r,x) == 1 || ehMultiplo(r,y) == 1){
        printf("%d", r);
        printf(" ");
        contador++;
    }
        r++ ;
  }
}

int ehMultiplo(int r, int s){
  if(r%s==0){
    return 1;
  } else {
    return 0;
  }
}
