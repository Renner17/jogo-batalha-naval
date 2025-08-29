#include <stdio.h>

#define TAM_TABULEIRO 10   // tamanho fixo do tabuleiro
#define TAM_NAVIO 3        // tamanho fixo dos navios

int main() {
    // Declaração do tabuleiro 10x10, inicializado com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Coordenadas iniciais escolhidas no código (poderiam ser entrada do usuário em versões futuras)
    int linhaNavioHorizontal = 2; // linha inicial do navio horizontal
    int colunaNavioHorizontal = 4; // coluna inicial do navio horizontal

    int linhaNavioVertical = 5; // linha inicial do navio vertical
    int colunaNavioVertical = 7; // coluna inicial do navio vertical

    // ---- Posicionamento do navio horizontal ----
    // Valida se cabe no tabuleiro
    if (colunaNavioHorizontal + TAM_NAVIO <= TAM_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] == 3) {
                sobreposicao = 1; // detecta sobreposição
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = 3;
            }
        }
    }

    // ---- Posicionamento do navio vertical ----
    // Valida se cabe no tabuleiro
    if (linhaNavioVertical + TAM_NAVIO <= TAM_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] == 3) {
                sobreposicao = 1; // detecta sobreposição
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = 3;
            }
        }
    }

    // ---- Exibição do tabuleiro ----
    printf("=== Tabuleiro Batalha Naval ===\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
