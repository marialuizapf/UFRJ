#include <stdio.h>

double harmonica(int N);
int main(void){
    int N;
    printf("Digite algum número inteiro:");
    scanf("%d", &N);

    if(N > 100){
        printf("Número inválido");
        return -1;
    }

    printf("O valor de série é: %f", harmonica(N));
}

double harmonica(int N){
    if(N == 1){
        return 1.0;
    }else if(N == 0){
        return 0;
    }else{
        return harmonica(N - 1.0) + 1.0/N;
    }
}
