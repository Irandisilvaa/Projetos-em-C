#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

char matriz[3][3];

void preencherMatriz() {
    int linha, coluna;
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            matriz[linha][coluna] = ' ';
        }
    }
}

void imprimirMatriz() {
    printf("\n");
    printf("      1     2     3\n");
    printf("        |     |     \n");
    printf("1    %c  |  %c  |  %c  \n", matriz[0][0], matriz[0][1], matriz[0][2]);
    printf("    ____|_____|_____\n");
    printf("        |     |     \n");
    printf("2    %c  |  %c  |  %c  \n", matriz[1][0], matriz[1][1], matriz[1][2]);
    printf("    ____|_____|_____\n");
    printf("        |     |     \n");
    printf("3    %c  |  %c  |  %c  \n", matriz[2][0], matriz[2][1], matriz[2][2]);
    printf("        |     |     \n");
}

int ganhaJogoPorLinha(int l, char c) {
    int cont = 0;
    for (int coluna = 0; coluna < 3; coluna++) {
        if (matriz[l][coluna] == c) {
            cont++;
        }
    }
    return (cont == 3);
}

int vitoriaPorLinhas(char c) {
    for (int linha = 0; linha < 3; linha++) {
        if (ganhaJogoPorLinha(linha, c)) {
            return 1;
        }
    }
    return 0;
}

int ganhaJogoPorColuna(int n, char c) {
    int cont = 0;
    for (int linha = 0; linha < 3; linha++) {
        if (matriz[linha][n] == c) {
            cont++;
        }
    }
    return (cont == 3);
}

int vitoriaPorColunas(char c) {
    for (int coluna = 0; coluna < 3; coluna++) {
        if (ganhaJogoPorColuna(coluna, c)) {
            return 1;
        }
    }
    return 0;
}

int ganhaPorDiagonalPrincipal(char c) {
    return (matriz[0][0] == c && matriz[1][1] == c && matriz[2][2] == c);
}

int ganhaPorDiagonalSecundaria(char c) {
    return (matriz[0][2] == c && matriz[1][1] == c && matriz[2][0] == c);
}

int verificaCoordenada(int linha, int coluna) {
    return (linha >= 1 && linha <= 3 && coluna >= 1 && coluna <= 3 && matriz[linha - 1][coluna - 1] == ' ');
}

void lerCoordenadas(char j) {
    int linha, coluna;
    printf("\nDigite a linha e a coluna que você quer jogar: ");
    scanf("%d%d", &linha, &coluna);

    while (!verificaCoordenada(linha, coluna)) {
        printf("Opção inválida! Digite novamente: ");
        scanf("%d%d", &linha, &coluna);
    }
    matriz[linha - 1][coluna - 1] = j;
}

int empate() {
    for (int linha = 0; linha < 3; linha++) {
        for (int coluna = 0; coluna < 3; coluna++) {
            if (matriz[linha][coluna] == ' ') {
                return 0;
            }
        }
    }
    return 1;
}

void jogar() {
    int opJogador = 1;
    char jogador1 = 'X', jogador2 = 'O';

    printf("Deseja ser o jogador 1 (X) ou o jogador 2 (O)? ");
    scanf("%d", &opJogador);
    system ("cls");
    do {
        imprimirMatriz();
        if (opJogador == 1) {
            printf("\nJogador 1 (X): ");
            lerCoordenadas(jogador1);
            opJogador = 2;
            system("cls");
        } else {
            printf("\nJogador 2 (O): ");
            lerCoordenadas(jogador2);
            opJogador = 1;
            system("cls");
        }
    } while (!empate() && !vitoriaPorLinhas(jogador1) && !vitoriaPorColunas(jogador1) && !ganhaPorDiagonalPrincipal(jogador1) && !ganhaPorDiagonalSecundaria(jogador1) &&
             !vitoriaPorLinhas(jogador2) && !vitoriaPorColunas(jogador2) && !ganhaPorDiagonalPrincipal(jogador2) && !ganhaPorDiagonalSecundaria(jogador2));

    imprimirMatriz();
    if (vitoriaPorLinhas(jogador1) || vitoriaPorColunas(jogador1) || ganhaPorDiagonalPrincipal(jogador1) || ganhaPorDiagonalSecundaria(jogador1)) {
        printf("\nJogador 1 (X) venceu!\n");
    } else if (vitoriaPorLinhas(jogador2) || vitoriaPorColunas(jogador2) || ganhaPorDiagonalPrincipal(jogador2) || ganhaPorDiagonalSecundaria(jogador2)) {
        printf("\nJogador 2 (O) venceu!\n");
    } else {
        printf("\nEmpate!\n");
    }
}

int main() {
    int opcao;
        setlocale(LC_ALL, "Portuguese");
    do {
        preencherMatriz();
        jogar();
        printf("\nDeseja jogar novamente?\n1 - Sim\n2 - Não\n");
        scanf("%d", &opcao);
        while (opcao < 1 || opcao > 2) {
            printf("Opção inválida!\n");
            printf("Deseja jogar novamente?\n1 - Sim\n2 - Não\n");
            scanf("%d", &opcao);
        }
    } while (opcao != 2);
    printf ("Encerrando programa");
    return 0;
}
