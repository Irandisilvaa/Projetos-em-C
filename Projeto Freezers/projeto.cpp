#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct {
    char nome[50];
    float capacidade;
    int garantia;
    float economia;
    float temperatura;
} ModeloFreezer;

void ExibeLista(ModeloFreezer freezers[], int tamanho) {
    printf("             Deia    Sul     NSul    Frio    Fri     Lux \n");
    printf("Capacidade: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%-8.1f", freezers[i].capacidade);
    }
    printf("\nGarantia:    ");
    for (int i = 0; i < tamanho; i++) {
        printf("%-8d", freezers[i].garantia);
    }
    printf("\nEconomia:    ");
    for (int i = 0; i < tamanho; i++) {
        printf("%-8.1f", freezers[i].economia);
    }
    printf("\nTemperatura: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%-8.1f", freezers[i].temperatura);
    }
    printf("\n\n");
}

void ExibeColuna(ModeloFreezer freezers[], int tamanho, int coluna) {
    const char *nomes[] = {"Deia", "Sul", "NSul", "Frio", "Fri", "Lux"};
    if (coluna > 0 && coluna <= 6) {
        printf("Modelo %s\n", nomes[coluna - 1]);
        printf("Capacidade: %.1f\n", freezers[coluna - 1].capacidade);
        printf("Garantia: %d\n", freezers[coluna - 1].garantia);
        printf("Economia: %.1f\n", freezers[coluna - 1].economia);
        printf("Temperatura: %.1f\n", freezers[coluna - 1].temperatura);
    } else {
        printf("modelo inválido.\n");
    }
}

const char *QualModelo(int modelo) {
    switch (modelo) {
    case 0:
        return "Deia";
    case 1:
        return "Sul";
    case 2:
        return "NSul";
    case 3:
        return "Frio";
    case 4:
        return "Fri";
    case 5:
        return "Lux";
    default:
        return "Desconhecido";
    }
}

void ExibeLinha(ModeloFreezer freezers[], int tamanho, int linha) {
    printf("            Deia      Sul     NSul      Frio     Fri     Lux \n");
    switch (linha) {
    case 1:
        printf("Capacidade: ");
        for (int i = 0; i < tamanho; i++) {
            printf("%-2.1f    ", freezers[i].capacidade);
        }
        printf("\n");
        break;
    case 2:
        printf("Garantia:    ");
        for (int i = 0; i < tamanho; i++) {
            printf("%-8d ", freezers[i].garantia);
        }
        printf("\n");
        break;
    case 3:
        printf("Economia:   ");
        for (int i = 0; i < tamanho; i++) {
            printf("%-8.1f ", freezers[i].economia);
        }
        printf("\n");
        break;
    case 4:
        printf("Temperatura:");
        for (int i = 0; i < tamanho; i++) {
            printf("%-8.1f ", freezers[i].temperatura);
        }
        printf("\n");
        break;
    }
    printf("\n");
}

void AlterarDado(ModeloFreezer freezers[], int modelo, int caracteristica) {
    float novovalor;
    printf("Digite o novo valor para o modelo %d, caracteristica %d: ", modelo,
           caracteristica);
    scanf("%f", &novovalor);
    switch (caracteristica) {
    case 1:
        freezers[modelo - 1].capacidade = novovalor;
        break;
    case 2:
        freezers[modelo - 1].garantia = (int)novovalor;
        break;
    case 3:
        freezers[modelo - 1].economia = novovalor;
        break;
    case 4:
        freezers[modelo - 1].temperatura = novovalor;
        break;
    }
    printf("\nDado alterado com sucesso!\n\n");
}

void EncontrarMelhorModelo(ModeloFreezer freezers[], int tamanho, int linha) {
    float melhorValor = freezers[0].temperatura;
    int modeloMelhor = 0;

    for (int i = 1; i < tamanho; i++) {
        switch (linha) {
        case 0:
            if (freezers[i].capacidade > melhorValor) {
                melhorValor = freezers[i].capacidade;
                modeloMelhor = i;
            }
            break;
        case 1:
            if (freezers[i].garantia > melhorValor) {
                melhorValor = freezers[i].garantia;
                modeloMelhor = i;
            }
            break;
        case 2:
            if (freezers[i].economia > melhorValor) {
                melhorValor = freezers[i].economia;
                modeloMelhor = i;
            }
            break;
        case 3:
            if (freezers[i].temperatura < melhorValor) {
                melhorValor = freezers[i].temperatura;
                modeloMelhor = i;
            }
            break;
        }
    }

    switch (linha) {
    case 0:
        printf("\nMelhor Freezer em Capacidade: %s\n\n", QualModelo(modeloMelhor));
        break;
    case 1:
        printf("\nMelhor Freezer em Garantia: %s\n\n", QualModelo(modeloMelhor));
        break;
    case 2:
        printf("\nMelhor Freezer em Economia: %s\n\n", QualModelo(modeloMelhor));
        break;
    case 3:
        printf("\nMelhor Freezer em Temperatura: %s\n\n", QualModelo(modeloMelhor));
        break;
    }
}

int main() {
    setlocale(LC_ALL,"Portuguese");

    // Matriz de valores
    float M[4][6] = {{385, 534, 309, 546, 503, 477},
                     {12, 121, 12, 3, 24, 12},
                     {35.9, 72.1, 46.2, 74.3, 78, 90},
                     {-28, -18, -18, -18, -22, -18}};

    ModeloFreezer freezers[6];

    // Preenchendo a lista de freezers
    for (int j = 0; j < 6; j++) {
        freezers[j].capacidade = M[0][j];
        freezers[j].garantia = (int)M[1][j];
        freezers[j].economia = M[2][j];
        freezers[j].temperatura = M[3][j];
    }

    do {
        system("cls");
        printf(">>> Pesquisa Freezer <<<\n\n");
        printf("1 - Exibir Levantamento\n");
        printf("2 - Exibir dados de uma Caracteristica\n");
        printf("3 - Exibir todos dados de um modelo\n");
        printf("4 - Alterar Dado\n");
        printf("5 - Melhor Freezer em Capacidade\n");
        printf("6 - Melhor Freezer em Garantia\n");
        printf("7 - Melhor Freezer em Economia\n");
        printf("8 - Melhor Freezer em Temperatura\n");
        printf("9 - Sair\n");
        printf("Selecione a opcao desejada:");
        int Op;
        scanf("%d", &Op);
        while (Op<1 || Op >9){
            printf ("Opção invalida!\nPor favor Digite uma opção válida: ");
            scanf("%d",&Op);
            continue;
        }
        switch (Op) {
        case 1:
            ExibeLista(freezers, 6);
            system("pause");
            break;
        case 2:
            printf("Selecione a caracteristica desejada (1-4):\n1-Capacidade\n2-Garantia\n3-Economia\n4-Temperatura\n");
            int caracteristica;
            scanf("%d", &caracteristica);
            if (caracteristica >= 1 && caracteristica <= 4) {
                ExibeLinha(freezers, 6, caracteristica);
                system("pause");
            } else {
                printf("Opção inválida!\n");
                system("pause");
            }
            break;
        case 3:
            printf("Digite o modelo desejado (1-6):\n1-Deia\n2-Sul\n3-NSul\n4-Frio\n5-Fri\n6-Lux\n");
            int modelo;
            scanf("%d", &modelo);
            if (modelo >= 1 && modelo <= 6) {
                ExibeColuna(freezers, 6, modelo);
                system("pause");
            } else {
                printf("Opção inválida!\n");
                system("pause");
            }
            break;
        case 4:
            printf("Selecione o freezer desejado (1-6):\n1-Deia\n2-Sul\n3-NSul\n4-Frio\n5-Fri\n6-Lux\n");
            int freezer;
            scanf("%d", &freezer);
            if (freezer >= 1 && freezer <= 6) {
                printf("Selecione a caracteristica desejada para alterar (1-4):\n1-Capacidade\n2-Garantia\n3-Economia\n4-Temperatura\n");
                int caracteristica;
                scanf("%d", &caracteristica);
                if (caracteristica >= 1 && caracteristica <= 4) {
                    AlterarDado(freezers, freezer, caracteristica);
                    ExibeLista(freezers, 6);
                    system("pause");
                } else {
                    printf("Opção inválida para a caracteristica!\n");
                    system("pause");
                }
            } else {
                printf("Opção inválida para o freezer!\n");
                system("pause");
            }
            break;
        case 5:
            EncontrarMelhorModelo(freezers, 6, 0);
            ExibeLista(freezers, 6);
            system("pause");
            break;
        case 6:
            EncontrarMelhorModelo(freezers, 6, 1);
            ExibeLista(freezers, 6);
            system("pause");
            break;
        case 7:
            EncontrarMelhorModelo(freezers, 6, 2);
            ExibeLista(freezers, 6);
            system("pause");
            break;
        case 8:
            EncontrarMelhorModelo(freezers, 6, 3);
            ExibeLista(freezers, 6);
            system("pause");
            break;
        case 9:
            printf("Programa encerrado!! desenvolved by Irandi Silva ;)\n");
            break;
        }
        if (Op == 9)
            break;
    } while (1);

    return 0;
}

