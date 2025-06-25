#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>

int main(){
    FILE *arq;
    char nome[50], letra;
    int vogais[5] = {0};
    int contador = 0;

    printf("Digite o nome do arquivo: ");
    scanf("%s", nome);

    arq = fopen(nome, "r");
    if(arq == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while((letra = fgetc(arq)) != EOF){
        letra = tolower(letra);
        switch(letra){
            case 'a' : vogais[0]++; break;
            case 'e' : vogais[1]++; break;
            case 'i' : vogais[2]++; break;
            case 'o' : vogais[3]++; break;
            case 'u' : vogais[4]++; break;
        }
    }

    printf("A vogal 'a' aparece %d vezes\n", vogais[0]);
    printf("A vogal 'e' aparece %d vezes\n", vogais[1]);
    printf("A vogal 'i' aparece %d vezes\n", vogais[2]);
    printf("A vogal 'o' aparece %d vezes\n", vogais[3]);
    printf("A vogal 'u' aparece %d vezes\n", vogais[4]);

    fclose(arq);
}

