/*Este programa implementa um jogo da velha em C. Ele utiliza uma matriz 3x3 para representar o tabuleiro do jogo 
e permite que dois jogadores joguem alternadamente. 
O programa verifica se um jogador ganhou em linhas, colunas ou diagonais,
além de detectar empates. Após cada jogada, o tabuleiro é impresso e 
os jogadores são solicitados a inserir suas coordenadas. 
O jogo continua até que um jogador vença ou ocorra um empate.
O código está devidamente comentado para facilitar a compreensão.
Lembrando que tudo acontece via terminal sem o uso de interface gráfica
*/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Declaração da matriz que representa o tabuleiro do jogo
char matriz[3][3];

// Função para preencher a matriz com espaços em branco
void preencherMatriz() {
    int linha, coluna;
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            matriz[linha][coluna] = ' ';
        }
    }
}

// Função para imprimir o tabuleiro atual
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

// Função para verificar se um jogador ganhou em uma linha específica
int ganhaJogoPorLinha(int l, char c) {
    int cont = 0;
    for (int coluna = 0; coluna < 3; coluna++) {
        if (matriz[l][coluna] == c) {
            cont++;
        }
    }
    return (cont == 3);
}

// Função para verificar se um jogador ganhou em alguma linha
int vitoriaPorLinhas(char c) {
    for (int linha = 0; linha < 3; linha++) {
        if (ganhaJogoPorLinha(linha, c)) {
            return 1;
        }
    }
    return 0;
}

// Função para verificar se um jogador ganhou em alguma coluna
int ganhaJogoPorColuna(int n, char c) {
    int cont = 0;
    for (int linha = 0; linha < 3; linha++) {
        if (matriz[linha][n] == c) {
            cont++;
        }
    }
    return (cont == 3);
}

// Função para verificar se um jogador ganhou em alguma coluna
int vitoriaPorColunas(char c) {
    for (int coluna = 0; coluna < 3; coluna++) {
        if (ganhaJogoPorColuna(coluna, c)) {
            return 1;
        }
    }
    return 0;
}

// Função para verificar se um jogador ganhou na diagonal principal
int ganhaPorDiagonalPrincipal(char c) {
    return (matriz[0][0] == c && matriz[1][1] == c && matriz[2][2] == c);
}

// Função para verificar se um jogador ganhou na diagonal secundária
int ganhaPorDiagonalSecundaria(char c) {
    return (matriz[0][2] == c && matriz[1][1] == c && matriz[2][0] == c);
}

// Função para verificar se uma coordenada é válida para a jogada
int verificaCoordenada(int linha, int coluna) {
    return (linha >= 1 && linha <= 3 && coluna >= 1 && coluna <= 3 && matriz[linha - 1][coluna - 1] == ' ');
}

// Função para ler as coordenadas da jogada do jogador
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

// Função para verificar se houve empate no jogo
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

// Função principal do jogo
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

// Função principal do programa
int main() {
    int opcao;
    // Configura a localidade para Português
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

    printf("Encerrando programa\n");
    return 0;
}
