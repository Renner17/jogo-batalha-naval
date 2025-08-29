#include <stdio.h>

#define TAM_TABULEIRO 10   // tamanho fixo do tabuleiro
#define TAM_NAVIO 3        // tamanho fixo dos navios

// Função auxiliar para verificar se uma posição está livre
int podePosicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (tabuleiro[linha][coluna] == 3) {
        return 0; // já tem navio aqui
    }
    return 1;
}

// Função para posicionar navio horizontal
void posicionarHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO <= TAM_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (!podePosicionar(tabuleiro, linha, coluna + i)) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha][coluna + i] = 3;
            }
        }
    }
}

// Função para posicionar navio vertical
void posicionarVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (!podePosicionar(tabuleiro, linha + i, coluna)) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha + i][coluna] = 3;
            }
        }
    }
}

// Função para posicionar navio diagonal ↘ (linha++ / coluna++)
void posicionarDiagonalDireita(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO && coluna + TAM_NAVIO <= TAM_TABULEIRO) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (!podePosicionar(tabuleiro, linha + i, coluna + i)) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha + i][coluna + i] = 3;
            }
        }
    }
}

// Função para posicionar navio diagonal ↙ (linha++ / coluna--)
void posicionarDiagonalEsquerda(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO && coluna - (TAM_NAVIO - 1) >= 0) {
        int sobreposicao = 0;
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (!podePosicionar(tabuleiro, linha + i, coluna - i)) {
                sobreposicao = 1;
                break;
            }
        }
        if (!sobreposicao) {
            for (int i = 0; i < TAM_NAVIO; i++) {
                tabuleiro[linha + i][coluna - i] = 3;
            }
        }
    }
}

int main() {
    // Declaração do tabuleiro 10x10 inicializado com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // === Posicionando os 4 navios ===
    // Navios horizontais/verticais
    posicionarHorizontal(tabuleiro, 2, 4);   // navio horizontal
    posicionarVertical(tabuleiro, 5, 7);     // navio vertical

    // Navios diagonais
    posicionarDiagonalDireita(tabuleiro, 0, 0); // ↘
    posicionarDiagonalEsquerda(tabuleiro, 0, 9); // ↙

    // === Exibindo o tabuleiro ===
    printf("=== Tabuleiro Batalha Naval (Nivel Aventureiro) ===\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
