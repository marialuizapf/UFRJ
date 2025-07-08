#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "mapa.h"

/*
    ==============================================
    FUNÇÃO: carregarMapa
    Descrição:
        Carrega um mapa de texto para memória, onde:
        - Cada caractere representa um tipo de bloco no jogo
        - Espera-se um arquivo com 25 linhas (LINHAS) e 60 colunas (COLUNAS)

    Retorno:
        Ponteiro para estrutura Mapa alocada dinamicamente.
    ==============================================
*/
Mapa* carregarMapa(const char* caminho) {
    FILE* fp = fopen(caminho, "r");
    if (!fp) {
        perror("Erro ao abrir mapa");
        exit(EXIT_FAILURE);
    }

    Mapa* mapa = malloc(sizeof(Mapa));
    if (!mapa) {
        perror("Erro ao alocar memória para o mapa");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // Copia o caminho do arquivo para a estrutura
    strncpy(mapa->nomeArquivo, caminho, sizeof(mapa->nomeArquivo));
    mapa->nomeArquivo[sizeof(mapa->nomeArquivo) - 1] = '\0';

    // Aloca linhas do mapa
    mapa->tiles = malloc(sizeof(char*) * LINHAS);
    if (!mapa->tiles) {
        perror("Erro ao alocar linhas do mapa");
        free(mapa);
        fclose(fp);
        exit(EXIT_FAILURE);
    }

        // Lê cada linha do arquivo e aloca sua memória
    for (int i = 0; i < LINHAS; i++) {
        mapa->tiles[i] = malloc(sizeof(char) * (COLUNAS + 1)); // +1 para '\0'
        if (!mapa->tiles[i]) {
            perror("Erro ao alocar linha do mapa");
            for (int j = 0; j < i; j++) free(mapa->tiles[j]);
            free(mapa->tiles);
            free(mapa);
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        // Lê a linha do arquivo (até COLUNAS + 1 para pegar o '\n')
        if (fgets(mapa->tiles[i], COLUNAS + 2, fp) == NULL) {
            fprintf(stderr, "Formato de mapa inválido na linha %d\n", i);
            for (int j = 0; j <= i; j++) free(mapa->tiles[j]);
            free(mapa->tiles);
            free(mapa);
            fclose(fp);
            exit(EXIT_FAILURE);
        }

        // Remove '\n' se presente
        size_t len = strlen(mapa->tiles[i]);
        if (len > 0 && mapa->tiles[i][len - 1] == '\n') {
            mapa->tiles[i][len - 1] = '\0';
            len--;
        }

        // Preenche até 60 colunas com espaço se faltar
        for (size_t j = len; j < COLUNAS; j++) {
            mapa->tiles[i][j] = ' ';
        }

        mapa->tiles[i][COLUNAS] = '\0'; // Garante terminação
    }

    fclose(fp);
    return mapa;
}

/*
    ==============================================
    FUNÇÃO: desenharMapa
    Descrição:
        Percorre a matriz de tiles e desenha visualmente
        cada bloco com base em seu caractere.

    Parâmetros:
        - mapa: ponteiro para a estrutura Mapa
        - chave: textura da chave (usada para 'C')
    ==============================================
*/
void desenharMapa(Mapa* mapa, Texture2D chave, Texture2D caixa, Texture2D paredeInv, Texture2D paredeFraca) {
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            char tile = mapa->tiles[i][j];
            int x = j * 20;
            int y = i * 20;

            switch (tile) {
                case 'W': DrawTexture(paredeInv, x, y, WHITE); break;   // Parede indestrutível
                case 'D': DrawTexture(paredeFraca, x, y, WHITE); break;  // Bloco destrutível
                case 'B': // Caixa sem chave
                case 'K': // Caixa com chave
                    DrawTexture(caixa, x, y, WHITE);
                    break;
                case 'C': // Coração / item
                    DrawTexture(chave, x, y, WHITE);
                    break;
                default:  // Espaço vazio ou desconhecido
                    //DrawRectangle(x, y, 20, 20, GREEN);
                    break;
            }
        }
    }
}

/*
    ==============================================
    FUNÇÃO: liberarMapa
    Descrição:
        Libera toda a memória alocada para o mapa
    ==============================================
*/
void liberarMapa(Mapa* mapa) {
    if (!mapa) return;

    for (int i = 0; i < LINHAS; i++)
        free(mapa->tiles[i]);

    free(mapa->tiles);
    free(mapa);
}
