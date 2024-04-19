/*Este é um programa em C para gerenciamento de farmácias.
Ele permite incluir, excluir, alterar, consultar e listar fármacos, armazenando seus dados em um arquivo binário.
As informações de cada fármaco incluem nome, preço e quantidade em estoque. 
O programa oferece um menu interativo para o usuário escolher entre as operações disponíveis. 
As entradas são validadas e há verificações para evitar duplicatas de fármacos durante a inclusão e para marcar registros logicamente excluídos.


*/
#include <stdio.h>
#include <stdlib.h>  
#include <ctype.h> 
#include <string.h>
#include <locale.h>

typedef struct TpFarma
{
    char Nome[21];
    float Preco;
    int QEstoque;
} TpFARMA;


TpFARMA RgFarma;

FILE *ArqFarma;


long int Tamanho = 21 * sizeof(char) + sizeof(float) + sizeof(int);

long int TArquivo()
{
    fseek(ArqFarma, 0, 2);
    long int R = ftell(ArqFarma) / Tamanho;
    return R;
}


void Incluir() 
{ 
    system("cls");
    char Farmaco[21];
    printf("*** inclusao ***\n\n");
    printf("Nome: ");
    fflush(stdin);
    scanf(" %[^\n]s", Farmaco);

    ArqFarma = fopen("Farmacos.dat", "a+b");
    if (ArqFarma == NULL) {
        printf("Erro ao abrir o arquivo para inclusão!\n");
        return;
    }

    // Melhoria 1 - Verificar se o fármaco já está presente no arquivo
    fseek(ArqFarma, 0, SEEK_SET);
    while (fread(&RgFarma, Tamanho, 1, ArqFarma) == 1) {
        if (strcmp(RgFarma.Nome, Farmaco) == 0) {
            printf("Este fármaco já está cadastrado!\n");
            fclose(ArqFarma);
            system("pause");
            return;
        }
    }
   do {
        printf("Preço: ");
        scanf("%f", &RgFarma.Preco);
        if (RgFarma.Preco < 0) {
            printf("Preço não pode ser negativo. Por favor, insira um valor válido.\n");
        }
    } while (RgFarma.Preco < 0);

    do {
        printf("Estoque: ");
        scanf("%d", &RgFarma.QEstoque);
        if (RgFarma.QEstoque < 0) {
            printf("Quantidade em estoque não pode ser negativa. Por favor, insira um valor válido.\n");
        }
    } while (RgFarma.QEstoque < 0);


    
    fseek(ArqFarma, 0, SEEK_END);
    strcpy(RgFarma.Nome, Farmaco);
    fwrite(&RgFarma, Tamanho, 1, ArqFarma);
    system ("cls");
    printf ("\nInclusão realizada com Sucesso!\n");
    
    fclose(ArqFarma);
    system("pause");
    return;
}


void Excluir()
{
    system("cls");
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if (ArqFarma)
    {
        printf("Erro ao abrir o arquivo para leitura e escrita!\n");
        system("pause");
        return;
    }

    if (TArquivo() != 0)
    {
        printf("*** excluir ***\n\n");
        printf("Qual fármaco deseja excluir? ");
        fflush(stdin);
        char Farmaco[21];
        scanf(" %[^\n]", Farmaco);

        int Achou = 0;
        long int posicao = 0;
        fseek(ArqFarma, 0, SEEK_SET);
        while (fread(&RgFarma, Tamanho, 1, ArqFarma) == 1)
        {
            if (strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0)
            {
                Achou = 1;
                printf("Nome: %s\n", RgFarma.Nome);
                printf("Valor: %.2f\n", RgFarma.Preco);
                printf("Estoque: %d\n", RgFarma.QEstoque);
                printf("\nExclusão realizada com sucesso!\n");
                // Marcar a posição do cursor antes de sobrescrever o registro
                fseek(ArqFarma, posicao * Tamanho, SEEK_SET);
                RgFarma.Preco = -1; 
                fwrite(&RgFarma, Tamanho, 1, ArqFarma);
                break;
            }
				  // Atualiza a posição do cursor
            posicao++;
        }

        if (Achou == 0)
            printf("Fármaco inexistente!\n\n");

        fclose(ArqFarma);
    }
    else
    {
        printf("Arquivo vazio. Não existem dados a excluir.\n");
    }
    system("pause");
    return;
}

void Alterar()
{
    system("cls");
    printf("*** alterar ***\n\n");
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if (ArqFarma == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura e escrita!\n");
        system("pause");
        return;
    }

    printf("Qual fármaco deseja alterar? ");
    char Farmaco[21];
    fflush(stdin);
    scanf(" %[^\n]", Farmaco);

    fseek(ArqFarma, 0, SEEK_SET);
    char opcao;
    int Achou = 0;
    while (fread(&RgFarma, Tamanho, 1, ArqFarma) == 1)
    {
    	///melhoria 2-  oque vc quer alterar?
        if (strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0)
        {
            Achou = 1;
            printf("Deseja alterar o nome? (S-Sim / N-Não): ");
            scanf(" %c", &opcao);
            system ("cls");
            opcao = toupper(opcao);
            if (opcao == 'S') 
            {
                printf("Digite o novo nome: ");
                scanf(" %[^\n]", RgFarma.Nome);
                system ("cls");
            }

            printf("Deseja alterar o preço? (S-Sim / N-Não): ");
            scanf(" %c", &opcao);
            system ("cls");
            opcao = toupper(opcao);
            if (opcao == 'S') 
            {
                printf("Digite o novo preço: ");
                scanf("%f", &RgFarma.Preco);
                system ("cls");
            }

            printf("Deseja alterar a quantidade em estoque? (S-Sim / N-Não): ");
            scanf(" %c", &opcao);
            system ("cls");
            opcao = toupper(opcao);
            if (opcao == 'S') 
            {
                printf("Digite a nova quantidade: ");
                scanf("%d", &RgFarma.QEstoque);
                system ("cls");
            }

            fseek(ArqFarma, -Tamanho, SEEK_CUR);
            fwrite(&RgFarma, Tamanho, 1, ArqFarma);
            printf("\nALTERAÇÕES REALIZADAS COM SUCESSO!\n\n");
            break;
        }
    }

    if (Achou == 0) {
        printf("\nFármaco não encontrado!\n\n");
    }
    
    fclose(ArqFarma);
    system("pause");
    return;
}


void Consultar()
{
    system("cls");
    printf("*** consulta ***\n\n");
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if (ArqFarma == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura!\n");
        system("pause");
        return;
    }

    printf("Qual fármaco deseja consultar? ");
    char Farmaco[21];
    fflush(stdin);
    scanf(" %[^\n]", Farmaco);

    int Achou = 0;
    while (fread(&RgFarma, Tamanho, 1, ArqFarma) == 1)
    {
        if (strcmp(RgFarma.Nome, Farmaco) == 0 && RgFarma.Preco > 0)
        {
            Achou = 1;
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: R$%.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
            break; // Sai do loop assim que encontrar o fármaco
        }
    }

    if (Achou == 0)
    {
        printf("Fármaco não encontrado!\n\n");
    }

    fclose(ArqFarma);
    system("pause");
    return;
}

void ListarTodos()
{
    system("cls");
    printf("*** lista todos ***\n\n");
    
    ArqFarma = fopen("Farmacos.dat", "r+b");
    if (ArqFarma == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura!\n");
        system("pause");
        return;
    }

    // Verificar se o arquivo está vazio
    fseek(ArqFarma, 0, SEEK_END);
    long int tamanhoArquivo = ftell(ArqFarma);
    if (tamanhoArquivo == 0)
    {
        printf("Arquivo vazio. Nenhum fármaco cadastrado.\n");
        fclose(ArqFarma);
        system("pause");
        return;
    }

    fseek(ArqFarma, 0, SEEK_SET);
    while (fread(&RgFarma, Tamanho, 1, ArqFarma) == 1)
    {
        if (RgFarma.Preco > 0) // Verificar se não é um registro excluído logicamente
        {
            printf("Nome: %s\n", RgFarma.Nome);
            printf("Valor: R$%.2f\n", RgFarma.Preco);
            printf("Estoque: %d\n", RgFarma.QEstoque);
            printf("***\n\n");
        }
    }

    fclose(ArqFarma);
    system("pause");
    return;
}


int main() {
	setlocale(LC_ALL, "Portuguese");
    ArqFarma = fopen("Farmacos.dat", "a+b");
    char Opcao;
    do
    {
        system("cls");
        printf("\n\n> > > Pague Pouco < < < \n\n");
        printf("Que deseja fazer? \n\n");
        printf("I - Incluir \n");
        printf("E - Excluir \n");
        printf("A- Alterar\n");
        printf("C - Consultar \n");
        printf("T - Listar Todos \n");
        printf("S - Sair \n\n");
        printf ("Selecione a opção:");
        scanf(" %c", &Opcao);
        Opcao = toupper(Opcao);
        switch (Opcao)
        {
        case 'I':
            Incluir();
            break;
        case 'E':
            Excluir();
            break;
        case 'A':
        	Alterar();
        	break;
        case 'C':
            Consultar();
            break;
        case 'T':
            ListarTodos();
            break;
        case 'S':
            break;
        default:
            printf("Opcão inválida\n");
            system ("pause");
            break;
        }
    } while (Opcao != 'S');
    fclose(ArqFarma);
    return 0;
}


