#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "mapa.h"

/*
    Função que carrega um mapa a partir de um arquivo de texto.
    Cada caractere no arquivo representa um tipo de elemento do jogo:
    - 'W': Parede indestrutível
    - 'D': Bloco destrutível    
    - 'B': Caixa sem chave
    - 'K': Caixa com chave
    - 'E': Inimigo
    - 'J': Jogador
    - 'C': Coração / vida extra
    - ' ': Espaço vazio

    O arquivo deve conter exatamente 25 linhas e 60 colunas visíveis.
    Essa função retorna um ponteiro para a estrutura Mapa alocada dinamicamente.
*/

Mapa* carregarMapa(const char* nomeArquivo) {
    FILE* fp = fopen(nomeArquivo, "r");
    if (!fp) {
        perror("Erro ao abrir mapa");
        exit(EXIT_FAILURE);  
    }

    Mapa* mapa = malloc(sizeof(Mapa)); // Aloca memória para a estrutura principal do mapa
    if (!mapa) {
        perror("Erro ao alocar memória para o mapa");
        fclose(fp);
        exit(EXIT_FAILURE);  
    }
    mapa->tiles = malloc(sizeof(char*) * LINHAS);  // Aloca um vetor de ponteiros, um para cada linha do mapa
    if (!mapa->tiles) {
        perror("Erro ao alocar memória para as linhas do mapa");
        free(mapa);
        fclose(fp);
        exit(EXIT_FAILURE);  
    }

    // Para cada linha, aloca memória suficiente para os caracteres + '\0'
    for (int i = 0; i < LINHAS; i++) {
        mapa->tiles[i] = malloc(sizeof(char) * (COLUNAS + 1));  // +1 para '\0'
        if (!mapa->tiles[i]) {
            perror("Erro ao alocar memória para uma linha do mapa");
            for (int j = 0; j < i; j++) free(mapa->tiles[j]); // Libera as linhas já alocadas
            free(mapa->tiles);
            free(mapa);
            fclose(fp);
            exit(EXIT_FAILURE);  
        }
        // Lê a linha do arquivo para a matriz de tiles
        if (fgets(mapa->tiles[i], COLUNAS + 2, fp) == NULL) {  // +2 para '\n' + '\0'
            fprintf(stderr, "Formato de mapa inválido na linha %d\n", i);
            exit(EXIT_FAILURE); 
        }
    }
    fclose(fp);

    // Retorna o ponteiro para o mapa carregado
    return mapa;
}

void desenharMapa(Mapa* mapa) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char tile = mapa->tiles[i][j];
            int x = j * 20;
            int y = i * 20;
            switch (tile) {
                case 'W': DrawRectangle(x, y, 20, 20, GRAY); break; // Parede indestrutível
                case 'D': DrawRectangle(x, y, 20, 20, BROWN); break; // Bloco destrutível
                case 'B': DrawRectangle(x, y, 20, 20, YELLOW); break; // Caixa sem chave
                case 'K': DrawRectangle(x, y, 20, 20, YELLOW); break; // Caixa com chave
                default:  DrawRectangle(x, y, 20, 20, BLUE); break; // Espaço vazio
            }
        }
    }
}

void liberarMapa(Mapa* mapa) {
    for (int i = 0; i < LINHAS; i++) free(mapa->tiles[i]);
    free(mapa->tiles);
    free(mapa);
}