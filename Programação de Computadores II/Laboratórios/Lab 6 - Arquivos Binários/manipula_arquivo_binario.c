#include <stdio.h>
#include <stdlib.h>

int grava(FILE *pFile, int N);
int* recupera(FILE *pFile);
void exibe_vetor(int *vetor, int N);
int modifica(FILE *pFile, int M);
void recupera_exibe(FILE *pFile);

int main()
{
    FILE *pFile;
    int i, N, M, num, mod, *vetor;
    char nome_arquivo[100];
    
    printf("Informe o nome do arquivo a ser criado: ");
    gets(nome_arquivo);
    printf("Informe um numero positivo: ");
    scanf("%d",&N);
    
    pFile = fopen (nome_arquivo , "wb+");
    
    if (!pFile){ 
        printf("Erro na criacao do arquivo...");
        return -1;
    }
    
    if (grava(pFile, N)!=N){
        printf("Erro na gravacao do arquivo...");
        return -1;
    }
    
    vetor=recupera(pFile);
    
    if(vetor==NULL){
        printf("Erro na recuperacao de dados do arquivo...");
        return -1;
    }
    
    exibe_vetor(vetor,N);
    printf("Informe um numero positivo M correspondente a quantidade de valores a partir do final do arquivo que deseja alterar: "); 
    scanf("%d",&M);
    
    mod=modifica(pFile,M);

    if(mod==-1){
        printf("Valor de M fora do intervalo permitido...");
        return -1;
    }

    if(mod!=M){ 
        printf("Erro de leitura e/ou gravacao no arquivo...");
        return -1;
    }

    recupera_exibe(pFile);
    
    fclose (pFile);
    return 0;
}

int grava(FILE *pFile, int N){
    int escritos = 0;
    for(int i=N; i>0; i--){
        if (fwrite(&i, sizeof(int), 1, pFile) != 1){
            printf("Erro na gravacao do arquivo...");
            return -1;
        }
        escritos++;
    }
    rewind(pFile);
    return escritos;
}

int* recupera(FILE *pFile){
    int tam, *vetor, lidos, count;

    fseek(pFile, 0, SEEK_END);
    tam = ftell(pFile); 
    rewind(pFile);
    count = tam / sizeof(int);            

    vetor = (int*)malloc(count*sizeof(int));
    if (vetor == NULL)   return NULL;
    
    lidos = fread(vetor, sizeof(int), count, pFile);
    if (lidos != count){
        printf("Erro na leitura do arquivo...");
        free(vetor);
        return NULL;
    }
    rewind(pFile);

    return vetor;
}

void exibe_vetor(int *vetor, int N){
    for(int i = 0; i<N;i++){
        printf("%d", vetor[i]);
    }
    printf("\n");  // Pula linha no final
}

int modifica(FILE *pFile, int M){
    int tam, qtd, *aux;

    fseek(pFile,0, SEEK_END);
    tam = ftell(pFile);
    qtd = tam / sizeof(int);
    rewind(pFile);

    if (M <= 0 || M > qtd) return -1; 

    aux = (int*)malloc(qtd*sizeof(int));
    if (aux == NULL) return -1;

    if (fread(aux, sizeof(int), qtd, pFile) != qtd){
        printf("Erro na leitura do arquivo...");
        free(aux);
        return -1;
    }

    rewind(pFile);

    for(int i = qtd - M; i<qtd; i++){
        if(aux[i] % 2 == 0){
            aux[i] = aux[i] * 2;
        }
    }

    if (fwrite(aux, sizeof(int), qtd, pFile) != qtd){
        printf("Erro na gravacao do arquivo...");
        free(aux);
        return -1;
    }

    free(aux);
    rewind(pFile);
    return M;
} 

void recupera_exibe(FILE *pFile){
    int tam, qtd, *aux, lidos;
    
    fseek(pFile, 0, SEEK_END);
    tam = ftell(pFile);
    qtd = tam / sizeof(int);
    rewind(pFile);

    aux = (int*)malloc(qtd*sizeof(int));
    if (aux == NULL) {
        printf("Erro na alocacao de memoria...");
        return;
    }

    lidos = fread(aux, sizeof(int), qtd, pFile);
    if (lidos != qtd){
        printf("Erro na leitura do arquivo...");
        free(aux);
        return;
    }
    rewind(pFile);

    for(int i = 0; i < qtd; i++){
        printf("%d ", aux[i]);
    }
    printf("\n");  
    free(aux);
}

