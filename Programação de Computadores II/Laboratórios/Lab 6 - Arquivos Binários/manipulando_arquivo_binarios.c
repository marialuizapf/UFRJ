#include <stdio.h>
#include <stdlib.h>

int grava(FILE *pFile, int N);
int* recupera(FILE *pFile);
void exibe_vetor(int *vetor, int N);
int modifica(FILE *pFile, int M);
void recupera_exibe(FILE *pFile);

int main() {
    FILE *pFile;
    int N, M, mod, *vetor;
    char nome_arquivo[100];

    // Solicitar o nome do arquivo
    printf("Informe o nome do arquivo a ser criado: ");
    fgets(nome_arquivo, sizeof(nome_arquivo), stdin);
    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0'; // Remover o '\n'

    // Solicitar o valor de N
    printf("Informe um numero positivo: ");
    scanf("%d", &N);

    // Abrir o arquivo para leitura e escrita em modo binário
    pFile = fopen(nome_arquivo, "wb+");
    if (!pFile) {
        printf("Erro na criacao do arquivo...\n");
        return -1;
    }

    // Gravar os dados no arquivo
    if (grava(pFile, N) != N) {
        printf("Erro na gravacao do arquivo...\n");
        fclose(pFile);
        return -1;
    }

    // Recuperar os dados do arquivo
    vetor = recupera(pFile);
    if (vetor == NULL) {
        printf("Erro na recuperacao de dados do arquivo...\n");
        fclose(pFile);
        return -1;
    }

    // Exibir os dados recuperados
    exibe_vetor(vetor, N);
    printf("\n");
    free(vetor);

    // Solicitar o valor de M
    printf("Informe um numero positivo M correspondente a quantidade de valores a partir do final do arquivo que deseja alterar: ");
    scanf("%d", &M);

    // Modificar os dados no arquivo
    mod = modifica(pFile, M);
    if (mod == -1) {
        printf("Valor de M fora do intervalo permitido...\n");
        fclose(pFile);
        return -1;
    }
    if (mod != M) {
        printf("Erro de leitura e/ou gravacao no arquivo...\n");
        fclose(pFile);
        return -1;
    }

    // Recuperar e exibir os dados modificados
    recupera_exibe(pFile);
    printf("\n");

    // Fechar o arquivo
    fclose(pFile);
    return 0;
}

int grava(FILE *pFile, int N) {
    int *buffer;

    buffer = (int*)malloc(N*sizeof(int));
    if(buffer ==  NULL) return -1;

    for (int i = 0; i < N; i++) {
        buffer[i] = N - i;
    }
    int escritos = fwrite(buffer, sizeof(int), N, pFile);
    if (escritos != N) {
        printf("Erro ao gravar os dados no arquivo.\n");
        return -1;
    }
    return escritos;
}

int* recupera(FILE *pFile) {
    fseek(pFile, 0, SEEK_END);
    int N = ftell(pFile) / sizeof(int);
    rewind(pFile);

    int *vetor = (int *)malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }
    if (fread(vetor, sizeof(int), N, pFile) != N) {
        printf("Erro ao ler os dados do arquivo.\n");
        free(vetor);
        return NULL;
    }
    return vetor;
}

void exibe_vetor(int *vetor, int N) {
    for (int i = 0; i < N; i++) {
        printf("%d ", vetor[i]);
    }
}

int modifica(FILE *pFile, int M) {
    fseek(pFile, 0, SEEK_END);
    int N = ftell(pFile) / sizeof(int);
    if (M <= 0 || M > N) {
        return -1;
    }

    int numero;
    for (int i = N - M; i < N; i++) {
        fseek(pFile, i * sizeof(int), SEEK_SET);
        if (fread(&numero, sizeof(int), 1, pFile) != 1) {
            printf("Erro ao ler o dado do arquivo.\n");
            return -1;
        }
        if (numero % 2 == 0) {
            numero *= 2;
            fseek(pFile, i * sizeof(int), SEEK_SET);
            if (fwrite(&numero, sizeof(int), 1, pFile) != 1) {
                printf("Erro ao gravar o dado no arquivo.\n");
                return -1;
            }
        }
    }
    return M;
}

void recupera_exibe(FILE *pFile) {
    fseek(pFile, 0, SEEK_END);
    int N = ftell(pFile) / sizeof(int);
    rewind(pFile);

    int *vetor = (int *)malloc(N * sizeof(int));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }
    if (fread(vetor, sizeof(int), N, pFile) != N) {
        printf("Erro ao ler os dados do arquivo.\n");
        free(vetor);
        return;
    }
    exibe_vetor(vetor, N);
    printf("\n");
    free(vetor);
}
