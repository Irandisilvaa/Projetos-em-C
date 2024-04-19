#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <locale.h>

struct RegMoto {
    char Nome[20];
    char Modelo[10];
    char Placa[7];
    char Defeito[50];
    char Status;
    float Preco;
};

typedef struct RegMoto TpRegMoto;
TpRegMoto VZonda[50];

int Quant = -1; //Controla o preenchimento do vetor

void SolicitaServico() {
    char Sair = 'S';
    do {
        system("cls");
        printf("\n\n >>> Motos Zonda <<< \n\n");
        Quant = Quant + 1;
        printf("Qual o nome do cliente? ");
        scanf(" %[^\n]s", VZonda[Quant].Nome);
        printf("Qual o modelo da moto? ");
        scanf(" %[^\n]s", VZonda[Quant].Modelo);
        printf("Qual a placa da moto? ");
        scanf(" %[^\n]s", VZonda[Quant].Placa);
        printf("Qual o defeito da moto? ");
        scanf(" %[^\n]s", VZonda[Quant].Defeito);
        VZonda[Quant].Status = '0';
        VZonda[Quant].Preco = 0;
        printf("\n\nDeseja inserir novo servico? S|N ");
        scanf(" %c", &Sair);
        Sair = toupper(Sair);
    } while (Sair != 'N');
}

void IniciaServico() {
    char P[7];
    printf("Placa da moto para iniciar serviço: ");
    scanf(" %[^\n]s", P);
    int Pos = -1; //posição da moto P no vetor
    //busca da moto para iniciar serviço
    for (int Cont = 0; Cont <= Quant; Cont++)
        if (strcmp(VZonda[Cont].Placa, P) == 0)
            Pos = Cont;
    if (Pos == -1)
        printf("Moto não cadastrada!");
    else {
        printf("\n Cliente %d: %s", Pos + 1, VZonda[Pos].Nome);
        printf("\n Modelo: %s", VZonda[Pos].Modelo);
        printf("\n Placa: %s", VZonda[Pos].Placa);
        printf("\n Defeito: %s", VZonda[Pos].Defeito);
        VZonda[Pos].Status = '1';
        printf("\n Status: %c-SERVIÇO INICIADO!", VZonda[Pos].Status);
        if (VZonda[Pos].Preco == 0)
            printf("\n Preco: NÃO DEFINIDO");
        else
            printf("\n Preco: %.2f", VZonda[Pos].Preco);
    }
}

void RemoverSolicitacao() {
    char P[7];
    printf("Placa da moto para remover solicitação: ");
    scanf(" %[^\n]s", P);
    int Pos = -1; //posição da moto P no vetor
    //busca da moto para remover solicitação
    for (int Cont = 0; Cont <= Quant; Cont++)
        if (strcmp(VZonda[Cont].Placa, P) == 0)
            Pos = Cont;
    if (Pos == -1)
        printf("Moto não cadastrada!");
    else {
        if (VZonda[Pos].Status == '0') {
            VZonda[Pos].Status = '2';
            printf("Solicitação removida para a moto com placa %s", VZonda[Pos].Placa);
        } else {
            printf("O serviço para esta moto já foi iniciado ou concluído.");
        }
    }
}

void ConsultarSolicitacoes() {
    printf("\n\n >>> Motos Zonda <<< \n\n");
    if (Quant == -1)
        printf("Não há serviços cadastrados.");
    else {
        int encontrou = 0; // Variável para indicar se pelo menos uma solicitação foi encontrada
        for (int Cont = 0; Cont <= Quant; Cont++) {
            if (VZonda[Cont].Status == '0' || VZonda[Cont].Status == '1') { // Alteração aqui
                encontrou = 1;
                printf("\n Cliente %d: %s", Cont + 1, VZonda[Cont].Nome);
                printf("\n Modelo: %s", VZonda[Cont].Modelo);
                printf("\n Placa: %s", VZonda[Cont].Placa);
                printf("\n Defeito: %s", VZonda[Cont].Defeito);
                if (VZonda[Cont].Status== '1') printf("\n Status:SERVIÇO INICIADO!");
                else if (VZonda[Cont].Status== '0') printf("\n Status:SERVIÇO NÃO INICIADO!");
                if (VZonda[Cont].Preco == 0)
                    printf("\n Preco: NAO DEFINIDO");
                else
                    printf("\n Preco: %.2f", VZonda[Cont].Preco);
                printf("\n --------------------- \n\n");
            }
        }
        if (!encontrou)
            printf("Não há serviços em aberto.");
    }
}



void ConcluirServico() {
    char P[7];
    printf("Placa da moto para concluir serviço: ");
    scanf(" %[^\n]s", P);
    int Pos = -1; //posição da moto P no vetor
    //busca da moto para concluir serviço
    for (int Cont = 0; Cont <= Quant; Cont++)
        if (strcmp(VZonda[Cont].Placa, P) == 0)
            Pos = Cont;
    if (Pos == -1)
        printf("Moto não cadastrada!");
    else {
        if (VZonda[Pos].Status == '1') {
            float preco, troco, valorPago;
            printf("Digite o preço final do serviço: ");
            scanf("%f", &preco);
            do {
                printf("Digite o valor pago por %s: ", VZonda[Pos].Nome);
                scanf("%f", &valorPago);
                if (valorPago < preco) {
                    printf("Valor pago insuficiente. Por favor, insira um valor igual ou maior que %.2f\n", preco);
                }
            } while (valorPago < preco);
            
            troco = valorPago - preco;
            printf("Troco: R$ %.2f\n", troco);
            VZonda[Pos].Preco = preco;
            VZonda[Pos].Status = '3';
            printf("Serviço concluído para a moto com placa %s\n", VZonda[Pos].Placa);
        } else {
            printf("O serviço para esta moto ainda não foi iniciado ou já foi concluído.\n");
        }
    }
}


void EncerrarExpediente() {
    printf("\n\n >>> Motos Zonda <<< \n\n");
    printf("Serviços realizados:\n");
    float total = 0;
    for (int Cont = 0; Cont <= Quant; Cont++) {
        if (VZonda[Cont].Status == '3') {
            printf("\n Cliente %d: %s", Cont + 1, VZonda[Cont].Nome);
            printf("\n Modelo: %s", VZonda[Cont].Modelo);
            printf("\n Placa: %s", VZonda[Cont].Placa);
            printf("\n Defeito: %s", VZonda[Cont].Defeito);
            printf("\n Preco: %.2f", VZonda[Cont].Preco);
            printf("\n --------------------- \n\n");
            total += VZonda[Cont].Preco;
        }
    }
    printf("\n\nValor total obtido com os serviços: %.2f\n", total);
}

int main() {
	setlocale(LC_ALL, "Portuguese"); 
    int Opcao;
    
    do {   
        printf("\n\n >>> Motos Zonda <<< \n\n");
        printf("1 - Solicitar Servico \n");
        printf("2 - Iniciar Servico \n");
        printf("3 - Remover Solicitacao \n");
        printf("4 - Consultar Solicitacoes \n");
        printf("5 - Concluir Servico \n");
        printf("6 - Encerrar Expediente \n");
        printf("7 - Sair \n\n");
        printf("Digite a opcao desejada: ");
        scanf("%d", &Opcao);
        while (Opcao<1 || Opcao >7){
            printf ("Opção invalida!\nPor favor Digite uma opção válida: ");
            scanf("%d",&Opcao);
            continue;
        }
        system("cls");
        switch (Opcao) {
            case 1:
                SolicitaServico();
                break;
            case 2:
                IniciaServico();
                break;
            case 3:
                RemoverSolicitacao();
                break;
            case 4:
                ConsultarSolicitacoes();
                break;
            case 5:
                ConcluirServico();
                break;
            case 6:
                EncerrarExpediente();
                break;
            case 7: printf ("Saindo do Programa! \nAté ja :)");
                break;
        }
    } while (Opcao != 7);
    return 0;
}

