#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARACTERES 300
#define MAX_ITEMS 1000

int ler_dados(const char *arquivo, char nomes[][100], int anos[], int volumes[]);

void ordenar(int total_linhas, char nomes[][100], int anos[], int volumes[], int opcao);

void escrita_dados(const char *arquivo, char nomes[][100], int anos[], int volumes[], int total_linhas);

int main()
{
    const char arquivo_entrada[50] = "livro.csv";
    char arquivo_saida[100];
    char nomes[MAX_ITEMS][100];
    int anos[MAX_ITEMS];
    int volumes[MAX_ITEMS];

    int total_linhas = ler_dados(arquivo_entrada, nomes, anos, volumes);

    int opcao;

    do
    {
        printf("\nDos dados dos livros, escolha o campo para os ordenar:\n");
        printf("1 - Nome\n");
        printf("2 - Ano\n");
        printf("3 - Volume\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao < 1 || opcao > 3)
        {
            printf("\nNumero invalido, tente novamente\n");
        }

    } while (opcao < 1 || opcao > 3);

    ordenar(total_linhas, nomes, anos, volumes, opcao);

    printf("\nDigite o nome do arquivo CSV de saida: ");
    scanf("%s", arquivo_saida);

    escrita_dados(arquivo_saida, nomes, anos, volumes, total_linhas);

    printf("\nArquivo '%s' gerado com sucesso!\n", arquivo_saida);

    return 0;
}

int ler_dados(const char *arquivo, char nomes[][100], int anos[], int volumes[])
{
    FILE *file = fopen(arquivo, "r");
    if (file == NULL)
    {
        perror("Erro ao abrir arquivo de entrada");
        return -1;
    }

    int total_linhas = 0;
    char linha[MAX_CARACTERES];

    while (fgets(linha, sizeof(linha), file) && total_linhas < MAX_ITEMS)
    {

        char *token = strtok(linha, ",");
        strcpy(nomes[total_linhas], token);

        token = strtok(NULL, ",");
        anos[total_linhas] = atoi(token);

        token = strtok(NULL, ",");
        volumes[total_linhas] = atoi(token);

        total_linhas++;
    }

    fclose(file);
    return total_linhas;
}

void ordenar(int total_linhas, char nomes[][100], int anos[], int volumes[], int opcao)
{
    for (int i = 0; i < total_linhas - 1; i++)
    {
        for (int j = i + 1; j < total_linhas; j++)
        {
            int troca = 0;

            switch (opcao)
            {
            case 1:
                if (strcmp(nomes[i], nomes[j]) > 0)
                {
                    troca = 1;
                }
                break;

            case 2:
                if (anos[i] > anos[j])
                {
                    troca = 1;
                }
                break;

            case 3:
                if (volumes[i] > volumes[j])
                {
                    troca = 1;
                }
                break;
            }

            if (troca)
            {

                char temp_nome[100];
                strcpy(temp_nome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], temp_nome);

                int temp_ano = anos[i];
                anos[i] = anos[j];
                anos[j] = temp_ano;

                int temp_volume = volumes[i];
                volumes[i] = volumes[j];
                volumes[j] = temp_volume;
            }
        }
    }
}

void escrita_dados(const char *arquivo, char nomes[][100], int anos[], int volumes[], int total_linhas)
{
    FILE *file_saida = fopen(arquivo, "w");
    if (file_saida == NULL)
    {
        perror("Erro na criacao do arquivo de saida");
        exit(1);
    }

    for (int i = 0; i < total_linhas; i++)
    {
        fprintf(file_saida, "%s,%d,%d\n", nomes[i], anos[i], volumes[i]);
    }

    fclose(file_saida);
}