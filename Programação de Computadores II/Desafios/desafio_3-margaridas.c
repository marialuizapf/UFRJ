#include <stdio.h>
#include <stdlib.h>

int main (){
    
    int L, C, M, N;
    scanf("%d %d %d %d", &L, &C, &M, &N);
    
     if(L < 1 || C < 1 || M > L || N > C){
        return 1;
    }
    
    int **m;
    m = (int **)malloc(L*sizeof(int *));
    for(int i = 0; i < L ; i++){
        m[i] = (int *)malloc(C*sizeof(int));
        for(int j = 0; j < C; j++){
            scanf("%d", &m[i][j]);
        }
    }
    
        
    int max = 0;
    for(int x = 0 ; x <= L - M; x+=M){
        for(int y = 0 ; y <= C - N; y+=N){
        
        int soma = 0;
            for(int i = 0; i < M ; i++){
                for(int j = 0; j < N; j++){
                    soma += m[i+x][j+y];
                }
            }
            
            if(soma > max){
                max = soma;
            }
        }
    }
    
    printf("%d\n", max);
    
    for(int i = 0; i < L; i++){
        free(m[i]);
    }
    free(m);
    
    return 0;
}
