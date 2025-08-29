#include <stdio.h>
#include <stdlib.h>   // abs()

#define TAM_TABULEIRO 10     // tamanho do tabuleiro 10x10
#define TAM_NAVIO 3          // tamanho fixo dos navios
#define TAM_HABILIDADE 5     // tamanho das matrizes de habilidades (5x5)

// =================== TABULEIRO ===================

void inicializarTabuleiro(int tabuleiro[][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0; // água
        }
    }
}

void exibirTabuleiro(int tabuleiro[][TAM_TABULEIRO]) {
    printf("\n=== Tabuleiro Batalha Naval (Nivel Mestre) ===\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0)      printf(". "); // água
            else if (tabuleiro[i][j] == 3) printf("N "); // navio
            else if (tabuleiro[i][j] == 5) printf("* "); // área de habilidade
        }
        printf("\n");
    }
}

// =================== NAVIOS ===================

void posicionarHorizontal(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    }
}

void posicionarVertical(int tabuleiro[][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// =================== HABILIDADES (matrizes 5x5) ===================

void construirCone(int habilidade[][TAM_HABILIDADE]) {
    // Cone "apontando para baixo": a largura aumenta a cada linha
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

void construirCruz(int habilidade[][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            habilidade[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

void construirOctaedro(int habilidade[][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;  // dentro do losango
            } else {
                habilidade[i][j] = 0;  // fora
            }
        }
    }
}

// =================== SOBREPOSIÇÃO NO TABULEIRO ===================

void aplicarHabilidade(int tabuleiro[][TAM_TABULEIRO],
                       int habilidade[][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab  = origemLinha + (i - centro);
                int colunaTab = origemColuna + (j - centro);

                // Limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {

                    // Não sobrescreve navio (3); marca só água (0)
                    if (tabuleiro[linhaTab][colunaTab] == 0) {
                        tabuleiro[linhaTab][colunaTab] = 5;
                    }
                }
            }
        }
    }
}

// =================== MAIN ===================

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];

    inicializarTabuleiro(tabuleiro);

    // Navios exemplo (tamanho 3)
    posicionarHorizontal(tabuleiro, 2, 4);
    posicionarVertical(tabuleiro, 6, 2);

    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicações (origens escolhidas no código)
    aplicarHabilidade(tabuleiro, cone,     1, 1);  // perto do topo/esquerda
    aplicarHabilidade(tabuleiro, cruz,     5, 5);  // centro
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);  // canto inferior direito

    exibirTabuleiro(tabuleiro);
    return 0;
}
