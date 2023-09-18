#include <stdio.h>  // printf, scanf
#include <stdlib.h> // malloc, free, realloc
#include <string.h> // strcmp

#define TAM_MAX 1000  // tamanho máximo da agenda
#define MAX_NOME 50   // tamanho máximo do nome
#define MAX_EMAIL 30  // tamanho máximo do email
#define MAX_RUA 50    // tamanho máximo da rua
#define MAX_BAIRRO 50 // tamanho máximo do bairro
#define MAX_CIDADE 50 // tamanho máximo da cidade
#define MAX_DDD 3     // tamanho máximo do DDD
#define MAX_NUMERO 10 // tamanho máximo do número de telefone

// Definição das estruturas de dados
struct endereco // estrutura para armazenar o endereço
{
    char rua[MAX_RUA];
    char numero[MAX_NUMERO];
    char bairro[MAX_BAIRRO];
    char cidade[MAX_CIDADE];
};

struct telefone // estrutura para armazenar o telefone
{
    char ddd[MAX_DDD];
    char numero[MAX_NUMERO];
};

struct contato // estrutura para armazenar o contato completo
{
    char nome[MAX_NOME];
    char email[MAX_EMAIL];
    struct endereco end;
    struct telefone tel[2];
};

// Declaração da agenda e variáveis de controle
struct contato *agenda[TAM_MAX];
int tamAgenda = 0;     // tamanho atual da agenda
int tamMaxAgenda = 10; // tamanho máximo da agenda

// Função para cadastrar um novo contato na agenda
void cadastrar()
{
    // Verifica se a agenda está cheia
    if (tamAgenda >= tamMaxAgenda)
    {
        printf("Agenda cheia!\n");
        return;
    }

    // Aloca memória para o novo contato
    struct contato *contato = (struct contato *)malloc(sizeof(struct contato));

    // Pede as informações do contato ao usuário
    printf("Nome: ");
    scanf("%s", contato->nome);
    printf("Email: ");
    scanf("%s", contato->email);
    printf("Rua: ");
    scanf("%s", contato->end.rua);
    printf("Numero: ");
    scanf("%s", contato->end.numero);
    printf("Bairro: ");
    scanf("%s", contato->end.bairro);
    printf("Cidade: ");
    scanf("%s", contato->end.cidade);
    printf("Telefone Fixo\n");
    printf("DDD: ");
    scanf("%s", contato->tel[0].ddd);
    printf("Numero: ");
    scanf("%s", contato->tel[0].numero);
    printf("Telefone Celular\n");
    printf("DDD: ");
    scanf("%s", contato->tel[1].ddd);
    printf("Numero: ");
    scanf("%s", contato->tel[1].numero);

    // Adiciona o contato à agenda
    agenda[tamAgenda] = contato;
    tamAgenda++;
}

// Função para listar todos os contatos da agenda
void listar()
{
    int i;
    for (i = 0; i < tamAgenda; i++)
    {
        printf("\n\n\n");
        printf("Nome: %s\n", agenda[i]->nome);
        printf("Email: %s\n", agenda[i]->email);
        printf("Rua: %s\n", agenda[i]->end.rua);
        printf("Numero: %s\n", agenda[i]->end.numero);
        printf("Bairro: %s\n", agenda[i]->end.bairro);
        printf("Cidade: %s\n", agenda[i]->end.cidade);
        printf("Telefone Fixo\n");
        printf("DDD: %s\n", agenda[i]->tel[0].ddd);
        printf("Numero: %s\n", agenda[i]->tel[0].numero);
        printf("Telefone Celular\n");
        printf("DDD: %s\n", agenda[i]->tel[1].ddd);
        printf("Numero: %s\n", agenda[i]->tel[1].numero);
    }
}

// Função para buscar um contato na agenda pelo nome
void buscar()
{
    char nome[50];
    printf("Digite o nome do contato: ");
    scanf("%s", nome);
    int i;
    for (i = 0; i < tamAgenda; i++)
    {
        if (strcmp(agenda[i]->nome, nome) == 0)
        {
            printf("\n\n\n");
            printf("Nome: %s\n", agenda[i]->nome);
            printf("Email: %s\n", agenda[i]->email);
            printf("Rua: %s\n", agenda[i]->end.rua);
            printf("Numero: %s\n", agenda[i]->end.numero);
            printf("Bairro: %s\n", agenda[i]->end.bairro);
            printf("Cidade: %s\n", agenda[i]->end.cidade);
            printf("Telefone Fixo\n");
            printf("DDD: %s\n", agenda[i]->tel[0].ddd);
            printf("Numero: %s\n", agenda[i]->tel[0].numero);
            printf("Telefone Celular\n");
            printf("DDD: %s\n", agenda[i]->tel[1].ddd);
            printf("Numero: %s\n", agenda[i]->tel[1].numero);
            return;
        }
    }
    printf("Contato nao encontrado!\n");
}

// Função para remover um contato da agenda pelo nome
void remover()
{
    char nome[50];
    printf("Digite o nome do contato: ");
    scanf("%s", nome);
    int i, j, k;
    int encontrados = 0;
    int escolhido = -1;
    for (i = 0; i < tamAgenda; i++)
    {
        if (strcmp(agenda[i]->nome, nome) == 0)
        {
            encontrados++;
            printf("%d - %s (%s)\n", encontrados, agenda[i]->nome, agenda[i]->tel[0].numero);
        }
    }
    if (encontrados == 0)
    {
        printf("Contato nao encontrado!\n");
        return;
    }
    else if (encontrados == 1)
    {
        for (i = 0; i < tamAgenda; i++)
        {
            if (strcmp(agenda[i]->nome, nome) == 0)
            {
                free(agenda[i]);
                for (j = i; j < tamAgenda - 1; j++)
                {
                    agenda[j] = agenda[j + 1];
                }
                tamAgenda--;
                // Realocar a memória da agenda
                *agenda = (struct contato *)realloc(agenda, tamAgenda * sizeof(struct contato *));
                printf("Contato removido!\n");
                return;
            }
        }
    }
    else
    {
        printf("Digite o numero do contato que deseja remover: ");
        scanf("%d", &escolhido);
        if (escolhido < 1 || escolhido > encontrados)
        {
            printf("Opcao invalida!\n");
            return;
        }
        k = 0;
        for (i = 0; i < tamAgenda; i++)
        {
            if (strcmp(agenda[i]->nome, nome) == 0)
            {
                k++;
                if (k == escolhido)
                {
                    free(agenda[i]);
                    for (j = i; j < tamAgenda - 1; j++)
                    {
                        agenda[j] = agenda[j + 1];
                    }
                    tamAgenda--;
                    // Realocar a memória da agenda
                    *agenda = (struct contato *)realloc(agenda, tamAgenda * sizeof(struct contato *));
                    printf("Contato removido!\n");
                    return;
                }
            }
        }
    }
}

// Função para editar um contato da agenda pelo nome
void editar()
{
    char nome[50];
    printf("Digite o nome do contato: ");
    scanf("%s", nome);
    int i, j, k;
    int encontrados = 0;
    int escolhido = -1;
    for (i = 0; i < tamAgenda; i++)
    {
        if (strcmp(agenda[i]->nome, nome) == 0)
        {
            encontrados++;
            printf("%d - %s (%s)\n", encontrados, agenda[i]->nome, agenda[i]->tel[0].numero);
        }
    }
    if (encontrados == 0)
    {
        printf("Contato nao encontrado!\n");
        return;
    }
    else if (encontrados == 1)
    {
        for (i = 0; i < tamAgenda; i++)
        {
            if (strcmp(agenda[i]->nome, nome) == 0)
            {
                // Pede as novas informações do contato ao usuário
                printf("Nome: ");
                scanf("%s", agenda[i]->nome);
                printf("Email: ");
                scanf("%s", agenda[i]->email);
                printf("Rua: ");
                scanf("%s", agenda[i]->end.rua);
                printf("Numero: ");
                scanf("%s", agenda[i]->end.numero);
                printf("Bairro: ");
                scanf("%s", agenda[i]->end.bairro);
                printf("Cidade: ");
                scanf("%s", agenda[i]->end.cidade);
                printf("Telefone Fixo\n");
                printf("DDD: ");
                scanf("%s", agenda[i]->tel[0].ddd);
                printf("Numero: ");
                scanf("%s", agenda[i]->tel[0].numero);
                printf("Telefone Celular\n");
                printf("DDD: ");
                scanf("%s", agenda[i]->tel[1].ddd);
                printf("Numero: ");
                scanf("%s", agenda[i]->tel[1].numero);
                printf("Contato editado!\n");
                return;
            }
        }
    }
    else
    {
        printf("Digite o numero do contato que deseja editar: ");
        scanf("%d", &escolhido);
        if (escolhido < 1 || escolhido > encontrados)
        {
            printf("Opcao invalida!\n");
            return;
        }
        k = 0;
        for (i = 0; i < tamAgenda; i++)
        {
            if (strcmp(agenda[i]->nome, nome) == 0)
            {
                k++;
                if (k == escolhido)
                {
                    // Pede as novas informações do contato ao usuário
                    printf("Nome: ");
                    scanf("%s", agenda[i]->nome);
                    printf("Email: ");
                    scanf("%s", agenda[i]->email);
                    printf("Rua: ");
                    scanf("%s", agenda[i]->end.rua);
                    printf("Numero: ");
                    scanf("%s", agenda[i]->end.numero);
                    printf("Bairro: ");
                    scanf("%s", agenda[i]->end.bairro);
                    printf("Cidade: ");
                    scanf("%s", agenda[i]->end.cidade);
                    printf("Telefone Fixo\n");
                    printf("DDD: ");
                    scanf("%s", agenda[i]->tel[0].ddd);
                    printf("Numero: ");
                    scanf("%s", agenda[i]->tel[0].numero);
                    printf("Telefone Celular\n");
                    printf("DDD: ");
                    scanf("%s", agenda[i]->tel[1].ddd);
                    printf("Numero: ");
                    scanf("%s", agenda[i]->tel[1].numero);
                    printf("Contato editado!\n");
                    return;
                }
            }
        }
    }
}

// Função para editar o tamanho máximo da agenda
void editarTamanhoAgenda()
{
    int novoTamanho;
    printf("Digite o novo tamanho da agenda: ");
    scanf("%d", &novoTamanho);
    if (novoTamanho <= 0 || novoTamanho > TAM_MAX)
    {
        printf("Tamanho invalido!\n");
        return;
    }
    tamMaxAgenda = novoTamanho;
    printf("Tamanho da agenda alterado para %d.\n", tamMaxAgenda);
}

void inicializar()
{
    // Aloca memória para a agenda
    *agenda = (struct contato *)malloc(tamMaxAgenda * sizeof(struct contato *));
    // Inicializa a agenda com NULL
    int i;
    for (i = 0; i < tamMaxAgenda; i++)
    {
        agenda[i] = NULL;
    }

    // Cadastra alguns contatos para testar
    struct contato *contato = (struct contato *)malloc(sizeof(struct contato)); // Aloca memória para o novo contato
    strcpy(contato->nome, "Joao");
    strcpy(contato->email, "Joao@gmail.com");
    strcpy(contato->end.rua, "Rua Joao");
    strcpy(contato->end.numero, "123");
    strcpy(contato->end.bairro, "Bairro Joao");
    strcpy(contato->end.cidade, "Cidade Joao");
    strcpy(contato->tel[0].ddd, "11");
    strcpy(contato->tel[0].numero, "1111-1111");
    strcpy(contato->tel[1].ddd, "11");
    strcpy(contato->tel[1].numero, "11111-2222");

    agenda[tamAgenda] = contato;

    tamAgenda++;

    contato = (struct contato *)malloc(sizeof(struct contato)); // Aloca memória para o novo contato

    strcpy(contato->nome, "Maria");
    strcpy(contato->email, "Maria@gmail.com");
    strcpy(contato->end.rua, "Rua Maria");
    strcpy(contato->end.numero, "456");
    strcpy(contato->end.bairro, "Bairro Maria");
    strcpy(contato->end.cidade, "Cidade Maria");
    strcpy(contato->tel[0].ddd, "11");
    strcpy(contato->tel[0].numero, "2222-1111");
    strcpy(contato->tel[1].ddd, "11");
    strcpy(contato->tel[1].numero, "22222-2222");
    agenda[tamAgenda] = contato;

    tamAgenda++;

    contato = (struct contato *)malloc(sizeof(struct contato)); // Aloca memória para o novo contato

    strcpy(contato->nome, "Pedro");
    strcpy(contato->email, "Pedro@gmail.com");
    strcpy(contato->end.rua, "Rua Pedro");
    strcpy(contato->end.numero, "789");
    strcpy(contato->end.bairro, "Bairro Pedro");
    strcpy(contato->end.cidade, "Cidade Pedro");
    strcpy(contato->tel[0].ddd, "11");
    strcpy(contato->tel[0].numero, "3333-1111");
    strcpy(contato->tel[1].ddd, "11");
    strcpy(contato->tel[1].numero, "33333-2222");
    agenda[tamAgenda] = contato;

    tamAgenda++;

    contato = (struct contato *)malloc(sizeof(struct contato)); // Aloca memória para o novo contato

    strcpy(contato->nome, "Ana");
    strcpy(contato->email, "Ana@gmail.com");
    strcpy(contato->end.rua, "Rua Ana");
    strcpy(contato->end.numero, "101");
    strcpy(contato->end.bairro, "Bairro Ana");
    strcpy(contato->end.cidade, "Cidade Ana");
    strcpy(contato->tel[0].ddd, "11");
    strcpy(contato->tel[0].numero, "4444-1111");
    strcpy(contato->tel[1].ddd, "11");
    strcpy(contato->tel[1].numero, "44444-2222");
    agenda[tamAgenda] = contato;

    tamAgenda++;

    contato = (struct contato *)malloc(sizeof(struct contato)); // Aloca memória para o novo contato

    strcpy(contato->nome, "Lucas");
    strcpy(contato->email, "Lucas@gmail.com");
    strcpy(contato->end.rua, "Rua Lucas");
    strcpy(contato->end.numero, "1234");
    strcpy(contato->end.bairro, "Bairro Lucas");
    strcpy(contato->end.cidade, "Cidade Lucas");
    strcpy(contato->tel[0].ddd, "11");
    strcpy(contato->tel[0].numero, "5555-1111");
    strcpy(contato->tel[1].ddd, "11");
    strcpy(contato->tel[1].numero, "55555-2222");
    agenda[tamAgenda] = contato; // Adiciona o contato à agenda

    tamAgenda++; // Incrementa o tamanho da agenda
}

void limparMemoria()
{
    int i;
    for (i = 0; i < tamAgenda; i++)
    {
        free(agenda[i]);
    }
}
// Função principal
int main()
{
    inicializar();
    int opcao;
    do
    {
        // Exibe o menu de opções
        printf("\n\n\n");
        printf("1 - Cadastrar\n");
        printf("2 - Listar\n");
        printf("3 - Buscar\n");
        printf("4 - Remover\n");
        printf("5 - Alterar tamanho da agenda\n");
        printf("6 - Editar\n");
        printf("7 - Sair\n");
        scanf("%d", &opcao);

        // Executa a opção escolhida pelo usuário
        switch (opcao)
        {
        case 1:
            cadastrar();
            break;
        case 2:
            listar();
            break;
        case 3:
            buscar();
            break;
        case 4:
            remover();
            break;
        case 5:
            editarTamanhoAgenda();
            break;
        case 6:
            editar();
            break;
        case 7:
            printf("Saindo...\n");
            limparMemoria();
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != 7);

    return 0;
}

//feito por: Gustavo Rodrigues de Souza e Eduardo Tenorio
//programa feito para a disciplina de programação estruturado 2
//professor: Ricardo
//data: 18/09/2023