#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _func
{
  char nome[40];
  int ano_nasc;
  float renda;
} Tfunc;

void * inicializa (Tfunc *cadastro, int funcionarios);
void * inclui_novos(Tfunc *cadastro, int funcionarios, int adicionais);
void imprime (Tfunc *cadastro, int inicio, int fim);

int main(void)
  {
  Tfunc *cadastro;
  int funcionarios, adicionais;
    
  printf("Quantos funcionarios? ");
  scanf("%d",&funcionarios);
    
  cadastro=inicializa(cadastro, funcionarios);
    
  if (!cadastro) return -1;
    
  printf("Quantos funcionarios a mais deseja adicionar? ");
  scanf("%d",&adicionais);
    
  cadastro = inclui_novos(cadastro, funcionarios, adicionais);
    
  if (!cadastro) return -1;
    
  printf("Lista de funcionarios cadastrados\n");
  imprime(cadastro, 0, funcionarios+adicionais);
  free(cadastro);
    
  return 0;
}

void *inicializa (Tfunc *cadastro, int funcionarios){
  
  cadastro = (Tfunc*)malloc(funcionarios*(sizeof(Tfunc)));
  for (int i = 0; i < funcionarios; i++){

    printf("Funcionário %d\n", i+1);
    
    printf("Nome:");
    scanf(" %[^\n]", cadastro[i].nome);  // Lê string com espaços
    
    printf("Ano de nascimento:");
    scanf("%d", &cadastro[i].ano_nasc);
    
    printf("Renda:");
    scanf("%f", &cadastro[i].renda);
  }
  
  return cadastro;
}

void * inclui_novos(Tfunc * cadastro, int funcionarios, int adicionais){

  cadastro = (Tfunc*)realloc(cadastro,(funcionarios + adicionais)*sizeof(Tfunc));
  for (int i = funcionarios; i < funcionarios+adicionais; i++){
    printf("Funcionário %d\n", i+1);
    
    printf("Nome:");
    scanf(" %[^\n]", cadastro[i].nome);  // Lê string com espaços
    
    printf("Ano de nascimento:");
    scanf("%d", &cadastro[i].ano_nasc);
    
    printf("Renda:");
    scanf("%f", &cadastro[i].renda);
  }
  
  return cadastro;
}
void imprime (Tfunc *cadastro, int inicio, int fim){

  for (int i = 0; i < fim; i++){
    printf("Funcionário %d\n", i+1);
    printf("Nome: %s\n", cadastro[i].nome);
    printf("Ano de nascimento: %d\n", cadastro[i].ano_nasc);
    printf("Renda: %f\n", cadastro[i].renda);
  }
}
