#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char TIPOCHAVE;

typedef struct Lista{
  TIPOCHAVE chave;
  struct Lista *prox;
}Lista;

Lista* criar_Lista();
int palindromo(Lista* topo, int tam);

int main(void){

  Lista *li = criar_Lista();
  char word[100];

  printf("Digite uma palavra:");
  scanf("%s", word);


  int tam = strlen(word);

  for(int i = 0; i < tam;i++){
    li = inserir_lista(li, word[i]);
  }

  if(palindromo(li, tam)){
    printf("A palavra é um palíndromo");
  }else{
    printf("A palavra não é um palíndromo");
  }
  return 0;
  }

Lista* criar_Lista(){
  return NULL;
}

Lista* inserir_Lista(Lista* topo, TIPOCHAVE chave, int pos){
  Lista *no = (Lista*)malloc(sizeof(Lista));
  if(no == NULL)
    return NULL;
  
  no->chave = chave;
  no->prox = topo; 
  
  return no;
}

int palindromo(Lista* topo, int tam){
  TIPOCHAVE *val = (TIPOCHAVE*) malloc(tam*sizeof(TIPOCHAVE));
  if(val == NULL)
      return NULL;
  
  Lista *atual = topo;
  for(int i = 0; i<tam;i++){
    val[i] = atual->chave;
    atual = atual->prox;
  }

  int aux = 0;
    for(int i = 0;i < tam;i++){
      if(val[i] == val[tam-i-1]){
        aux++;
      }
    }
    if(aux == tam/2){
      free(val);
      return 1;
    } else{
      free(val);
      return 0;
    }
}
