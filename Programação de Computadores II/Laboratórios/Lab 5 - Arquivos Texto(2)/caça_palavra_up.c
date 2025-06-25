#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void minusculo(char *palavra){
    for(int i=0;palavra[i];i++){
        palavra[i] = tolower(palavra[i]);
    }
}

int main(){
    char entrada[100], palavra[80], linha[80];
    int contador = 0;

    scanf("%s", entrada);
    getchar();

    FILE *arq = fopen(entrada, "r");
    if(arq == NULL) return 1;

    fgets(palavra,80,stdin);
    palavra[strcspn(palavra, "\n")] = '\0';
    minusculo(palavra);

    while(fgets(linha, 80, arq) != NULL){
        minusculo(linha);
        if(strstr(linha, palavra) != NULL){
            contador++;
        }
    }

    printf("A palavra apareceu %d vezes", contador);
    fclose(arq);
    return 0;
}
