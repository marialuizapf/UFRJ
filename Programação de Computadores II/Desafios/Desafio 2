#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct{
  int hora, minuto;
}t_Momento;

void tempoatual(int percorrido, t_Momento *momento){

  percorrido = percorrido / 60;
  int m1 = momento[0].hora - percorrido;
    if(m1 < 0){
      m1 = -m1;
    }
  int m2 = momento[1].hora - percorrido;
    if(m2 < 0){
      m2 = -m2;
    }
  if(m1 <= m2){
    printf("%d %d", momento[0].hora, momento[0].minuto);
  } else{
    printf("%d %d", momento[1].hora, momento[1].minuto);
  }
}

int main(int argc, char *argv[]) {

  
  if (argc != 2) {
    printf("Erro: número de argumentos inválido");
    return 1;
  }
  
  int n = atoi(argv[1]);

  for(int i = 0; i < n; i++){
  
    int percorrido;
    t_Momento *momento;
  
    momento = (t_Momento*)malloc(3*sizeof(t_Momento));
  
    if(momento == NULL){
      printf("Erro: não foi possível alocar memória");
      return 1;
    }
  
    printf("Digite a hora e o minuto do momento 1:\n");
    scanf("%d %d", &momento[0].hora, &momento[0].minuto);
  
    printf("Digite a hora e o minuto do momento 2:\n");
    scanf("%d %d", &momento[1].hora, &momento[1].minuto);
    
    printf("Digite o tempo percorrido:\n");
    scanf("%d", &percorrido);
  
    tempoatual(percorrido, momento);
  }
  return 0;
}
