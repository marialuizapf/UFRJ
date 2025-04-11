#include <stdio.h>
#include <string.h>

int main(void){

  int *i, j, n = 10;
  float *notas;
  char *nome;

  i = &n;

  notas = (float *)malloc(5*sizeof(float));
  if (notas == NULL){
    printf("Erro de alocação de memória");
    return 1;
  }

  nome = (char *)malloc(100*sizeof(char));
  if (nome == NULL){
    printf("Erro de alocação de memória");
    return 1;
  }

  printf("Digite o nome do aluno:\n");
  fgets(nome, 100, stdin);
  
  printf("Digite as notas dos alunos:\n");
  for(int j = 0; j < 5; j++){
    scanf("%f", &notas[j]);
    if (notas[j] < 0 || notas[j] > 10){
      printf("Nota inválida");
      return 1;
    }
  }

  nome[strlen(nome)-1] = '\0';

  for(int i = 0; i < strlen(nome); i++){
    if(nome[i] >= 'A' && nome[i] <= 'Z'){
      nome[i] += 32;
    }
  }

  if(nome[0] != '\0'){
    nome[0] -= 32;
  }
  
  for(int i = 0; i < strlen(nome); i++){
    if(nome[i-1] == ' '){
      nome[i] -= 32;
    }
  }

  printf("Nome do aluno: %s\n", nome);
  
  printf("As notas do alunos são:\n");
  for(int j = 0; j < 5; j++){
    printf("%.1f\n", notas[j]);
  }

  return 0;
}
