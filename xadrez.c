 #include <stdio.h>
#include <stdlib.h> // necessário para abs()

#define TAM 8  // tamanho do tabuleiro

// Constantes de movimento
const int MAX_BISPO = 7;
const int MAX_TORRE = 7;
const int MAX_CAVALO = 1; // cada "passo" do cavalo é fixo
const int MAX_RAINHA = 7; // combina Torre + Bispo

// Função para imprimir coordenadas válidas
void imprimirMovimentos(int movimentos[][2], int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("(%d, %d)\n", movimentos[i][0], movimentos[i][1]);
    }
}

// Movimentação do Bispo (diagonal)
int moverBispo(int linha, int coluna, int movimentos[][2]) {
    int count = 0;
    for (int i = 1; i <= MAX_BISPO; i++) {
        // diagonal superior direita
        if (linha + i < TAM && coluna + i < TAM) {
            movimentos[count][0] = linha + i;
            movimentos[count][1] = coluna + i;
            count++;
        }
        // diagonal superior esquerda
        if (linha + i < TAM && coluna - i >= 0) {
            movimentos[count][0] = linha + i;
            movimentos[count][1] = coluna - i;
            count++;
        }
        // diagonal inferior direita
        if (linha - i >= 0 && coluna + i < TAM) {
            movimentos[count][0] = linha - i;
            movimentos[count][1] = coluna + i;
            count++;
        }
        // diagonal inferior esquerda
        if (linha - i >= 0 && coluna - i >= 0) {
            movimentos[count][0] = linha - i;
            movimentos[count][1] = coluna - i;
            count++;
        }
    }
    return count;
}

// Movimentação da Torre (horizontal e vertical)
int moverTorre(int linha, int coluna, int movimentos[][2]) {
    int count = 0;
    for (int i = 0; i < TAM; i++) {
        if (i != linha) { // vertical
            movimentos[count][0] = i;
            movimentos[count][1] = coluna;
            count++;
        }
        if (i != coluna) { // horizontal
            movimentos[count][0] = linha;
            movimentos[count][1] = i;
            count++;
        }
    }
    return count;
}

// Movimentação da Rainha (combina Torre + Bispo)
int moverRainha(int linha, int coluna, int movimentos[][2]) {
    int count = 0;
    count += moverBispo(linha, coluna, movimentos); // diagonais
    int torreMov[TAM*2][2]; // auxiliar para movimentos da torre
    int torreCount = moverTorre(linha, coluna, torreMov);
    for (int i = 0; i < torreCount; i++) {
        movimentos[count][0] = torreMov[i][0];
        movimentos[count][1] = torreMov[i][1];
        count++;
    }
    return count;
}

// Movimentação do Cavalo (em L) usando loops aninhados
int moverCavalo(int linha, int coluna, int movimentos[][2]) {
    int count = 0;
    for (int dx = -2; dx <= 2; dx++) {
        if (dx == 0 || dx == -1 || dx == 1) continue;
        for (int dy = -2; dy <= 2; dy++) {
            if (dy == 0 || dy == -1 || dy == 1) continue;
            if (!(abs(dx) == 2 && abs(dy) == 1) && !(abs(dx) == 1 && abs(dy) == 2)) continue;
            int novaLinha = linha + dx;
            int novaColuna = coluna + dy;
            if (novaLinha >= 0 && novaLinha < TAM && novaColuna >= 0 && novaColuna < TAM) {
                movimentos[count][0] = novaLinha;
                movimentos[count][1] = novaColuna;
                count++;
            }
        }
    }
    return count;
}

int main() {
    int movimentos[32][2]; // espaço máximo para movimentos
    int qtd;

    printf("Movimentos do Bispo a partir de (3,3):\n");
    qtd = moverBispo(3, 3, movimentos);
    imprimirMovimentos(movimentos, qtd);

    printf("\nMovimentos da Torre a partir de (3,3):\n");
    qtd = moverTorre(3, 3, movimentos);
    imprimirMovimentos(movimentos, qtd);

    printf("\nMovimentos da Rainha a partir de (3,3):\n");
    qtd = moverRainha(3, 3, movimentos);
    imprimirMovimentos(movimentos, qtd);

    printf("\nMovimentos do Cavalo a partir de (3,3):\n");
    qtd = moverCavalo(3, 3, movimentos);
    imprimirMovimentos(movimentos, qtd);

    return 0;
}
