#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5   // tamanho fixo das matrizes de habilidades (5x5)

// Função para inicializar o tabuleiro com água (0)
void inicializarTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\n=== Tabuleiro Batalha Naval (Nivel Mestre) ===\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf(". ");  // água
            else if (tabuleiro[i][j] == 3) printf("N "); // navio
            else if (tabuleiro[i][j] == 5) printf("* "); // área de habilidade
        }
        printf("\n");
    }
}

// Função auxiliar para posicionar navio horizontal
void posicionarHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (coluna + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha][coluna + i] = 3;
        }
    }
}

// Função auxiliar para posicionar navio vertical
void posicionarVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    if (linha + TAM_NAVIO <= TAM_TABULEIRO) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha + i][coluna] = 3;
        }
    }
}

// ==== MATRIZES DE HABILIDADES ====
// Cone para baixo
void construirCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // condição: largura do cone aumenta conforme desce
            if (j >= (TAM_HABILIDADE/2 - i) && j <= (TAM_HABILIDADE/2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Cruz
void construirCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == centro || j == centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Octaedro (forma de losango)
void construirOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            // distância de Manhattan até o centro <= raio
            if (abs(i - centro) + abs(j - centro) <= centro) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// ==== SOBREPOSIÇÃO DA HABILIDADE NO TABULEIRO ====
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {

    int centro = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha + (i - centro);
                int colunaTab = origemColuna + (j - centro);

                // valida limites do tabuleiro
                if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {

                    // marca apenas se não tiver navio
                    if (tabuleiro[linhaTab][colunaTab] == 0) {
                        tabuleiro[linhaTab][colunaTab] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // === Posiciona alguns navios ===
    posicionarHorizontal(tabuleiro, 2, 4);
    posicionarVertical(tabuleiro, 6, 2);

    // === Matrizes de habilidades ===
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // === Aplicando habilidades no tabuleiro ===
    aplicarHabilidade(tabuleiro, cone, 1, 1);        // Cone com origem perto do topo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);        // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 8, 8);    // Octaedro canto inferior direito

    // === Exibir o tabuleiro final ===
    exibirTabuleiro(tabuleiro);

    return 0;
}
