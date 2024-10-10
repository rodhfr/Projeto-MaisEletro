#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 100
#define MAX_CPF_RG 12
#define MAX_CEP 9
#define MAX_COMPRAS 50

// Definição da função para limpar o terminal de acordo com o sistema operacional
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif

// Definição da estrutura para armazenar a data de nascimento
typedef struct dataNascimento {
    char dia[3];
    char mes[3];
    char ano[5];
} TdataNascimento;

// Definição da estrutura para armazenar o endereço
typedef struct endereco {
    char rua[MAX];
    char bairro[MAX];
    char cidade[MAX];
    char nResidencia[5];
    char cep[MAX];
} Tendereco;

// Definição da estrutura para armazenar a compra do cliente na lista de compras
typedef struct compra {
    int idProduto;
    int quantidade;
    char descricao[MAX];
    float valorTotal;
} Tcompra;

// Definição da estrutura para armazenar os dados do cliente
typedef struct cliente {
    int idCliente;
    char nome[MAX];
    int qtdCompras; // Utilizado para a lista de compras
    int qtdItensComprados; // Utilizado para o sorteio
    Tcompra listaCompras[MAX_COMPRAS]; // Utilizado para mostar na Tabela de Compras
    char cpf[MAX_CPF_RG]; // Utilizado para mostrar na Tabela de clientes
    Tendereco endereco;
    TdataNascimento dataNascimento;
    char rg[MAX_CPF_RG];
} Tcliente;

// Definição da estrutura para armazenar os dados do produto
typedef struct produtos {
    int idProduto;
    char descricao[MAX]; // Nome
    int qntdEstoque;
    float valorUnidade;
} Tprodutos;

// Definição da estrutura para armazenar os dados da venda
typedef struct vendas {
    int idVenda;
    int idCliente;
    int idProduto;
    int qtndItensVendidos; // ...
    float totalVenda;
} Tvendas;

// Definição da estrutura para armazenar os dados do cliente para o sorteio
typedef struct clienteSorteio {
    int idCliente;
    char nome[MAX];
    char cpf[MAX_CPF_RG];
} TclienteSorteio;

// Definição da estrutura para armazenar os dados do sorteio
typedef struct sorteio {
    TclienteSorteio clientesQualificados[MAX];
    int qtdClientesQualificados;
} Tsorteio;

// ------------------ FUNÇÕES AUXILIARES ------------------
// Limpa o buffer de entrada
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
// Pausa o programa e limpa o terminal
void pausar() {
    printf("Pressione Enter para continuar...");
    limparBuffer();
    system(CLEAR_COMMAND);
}

// ------------------ Inputs ------------------
// fgets que remove o \n do final da string e verifica se o input não está vazio
void inputString (char *str, int tamanho)
{
    while (1) {
        // Faz a leitura do input do usuário
        fgets(str, tamanho, stdin);
        size_t len = strlen(str);
        if (len > 0 && str[len-1] == '\n') {
            str[len-1] = '\0';
        } else {
            limparBuffer();
        }

        // Verifica se a string não está vazia
        if (strlen(str) > 0) {
            break; // Sai do loop se o input não estiver vazio
        } else {
            printf("Erro: Nenhum valor digitado! Por favor, tente novamente.\n");
        }
    }
}
// Função para verificar se o ID do cliente ou produto é válido
int verificarInputID(const char *nomeItem, int maxRegistros, int *id) {
    char input[10];
    int validInput = 0;
    while (!validInput) {
        printf("Qual o numero do registro do %s? ", nomeItem);
        inputString(input, 10);

        // Verifica se o usuário digitou algo
        if (strlen(input) == 0) {
            printf("Erro: Nenhum valor digitado!\n");
            continue;
        }

        // Converte a string para um número inteiro
        char *endptr;
        long idTemp = strtol(input, &endptr, 10);

        // Verifica se a conversão foi bem sucedida e se o usuário digitou um número inteiro
        if (*endptr != '\0') {
            printf("Erro: Entrada invalida, por favor digite um numero inteiro!\n");
            continue;
        }

        // Verifica se o ID do cliente ou produto é válido (existe)
        if (idTemp < 0 || idTemp >= maxRegistros) {
            printf("Erro: %s com o numero de registro %ld nao encontrado!\n", nomeItem, idTemp);
            continue;
        }
        
        // Seta o ID verificado
        *id = (int)idTemp;
        validInput = 1;
    }
    return 0; // Retorna 0 para indicar sucesso
}

// ------------------ Verificações ------------------
// Função para verificar se o cliente já atingiu o limite de compras
int checkLimiteCompras(Tcliente vetorClientes[], int idCliente) {
    if (vetorClientes[idCliente].qtdCompras >= MAX_COMPRAS) {
        printf("Erro: Limite de compras atingido para esse cliente!\n");
        return 0;
    }
    return 1;
}
// Função para verificar se o cliente foi encontrado
int searchCliente(Tcliente vetorClientes[], int *qntdClientesLoja, int idCliente) {
    // Verifica se o cliente foi encontrado
    for (int i = 0; i < *qntdClientesLoja; i++) {
        if (vetorClientes[i].idCliente == idCliente) {
            return i; // Retorna o índice do cliente encontrado
        }
    }
    printf("Erro: Cliente com o codigo %d nao encontrado!\n", idCliente);
    return -1; // Retorna -1 se o cliente não foi encontrado
}
// Função para verificar se o produto foi encontrado
int searchProduto(Tprodutos vetorProdutos[], int *qntdProdutosLoja, int idProduto) {
    // Verifica se o produto foi encontrado
    for (int i = 0; i < *qntdProdutosLoja; i++) {
        if (vetorProdutos[i].idProduto == idProduto) {
            return i; // Retorna o índice do produto encontrado
        }
    }
    printf("Erro: Produto com o codigo %d nao encontrado!\n", idProduto);
    return -1;
}

// ------------------ Funções do Programa ------------------
// Printar a lista de clientes: Codigo | CPF | Nome
void listaClientes(Tcliente vetorClientes[], int *qntdClientesLoja)
{
    printf("Lista dos cliente: \n");
    // Formatação da Tabela
    printf("%-10s %-12s %-50s\n", "Codigo", "CPF", "Nome");
    // For que percorre a quantidade total de clientes para imprimir todos na tabela
    for (int v=0;v<(*qntdClientesLoja);v++)
    {
        // Formatação da Tabela
        printf("%-10d %-12s %-30s\n", vetorClientes[v].idCliente, 
        vetorClientes[v].cpf, vetorClientes[v].nome);
    }
}
// Função para cadastrar um cliente
int cadastrarCliente(Tcliente vetorClientes[], int *qntdClientesLoja) {
    int index = *qntdClientesLoja;

    printf("Digite o nome do Cliente: ");
    inputString(vetorClientes[index].nome, MAX);
    limparBuffer();

    printf("Digite CPF do cliente: ");
    inputString(vetorClientes[index].cpf, MAX);
    limparBuffer();

    printf("Digite RG do cliente: ");
    inputString(vetorClientes[index].rg, MAX);
    limparBuffer();

    printf("Digite o dia de nascimento do cliente: ");
    inputString(vetorClientes[index].dataNascimento.dia, 3);
    limparBuffer();

    printf("Digite o mes de nascimento do cliente: ");
    inputString(vetorClientes[index].dataNascimento.mes, 3);
    limparBuffer();

    printf("Digite o ano de nascimento do cliente: ");
    inputString(vetorClientes[index].dataNascimento.ano, 5);
    limparBuffer();

    printf("Digite a cidade onde mora: ");
    inputString(vetorClientes[index].endereco.cidade, MAX);
    limparBuffer();

    printf("Digite o bairro onde mora: ");
    inputString(vetorClientes[index].endereco.bairro, MAX);
    limparBuffer();

    printf("Digite CEP: ");
    inputString(vetorClientes[index].endereco.cep, MAX);
    limparBuffer();

    printf("Digite a rua onde mora: ");
    inputString(vetorClientes[index].endereco.rua, MAX);
    limparBuffer();

    printf("Digite o numero da casa: ");
    inputString(vetorClientes[index].endereco.nResidencia, MAX);
    limparBuffer();

    // Seta o ID do cliente como o index atual
    vetorClientes[index].idCliente = index;

    // Incrementa a quantidade de clientes na loja
    (*qntdClientesLoja)++;

    // Retorna o ID do cliente cadastrado
    return vetorClientes[index].idCliente;
}
// Função para listar os produtos: Codigo | Descricao | Quantidade
void listarProdutos (Tprodutos vetorProdutos[], int *qntdProdutosLoja)
{
    printf("Lista dos produtos: \n");
    // Formatação da Tabela
    printf("%-10s %-20s %-10s\n", "Codigo", "Descricao", "Quantidade");
    // For que percorre a quantidade total de produtos para imprimir todos na tabela
    for (int v=0;v<(*qntdProdutosLoja); v++)
    {
        // Formatação da Tabela
        printf("%-10d %-20s %-10d\n", vetorProdutos[v].idProduto, 
        vetorProdutos[v].descricao, vetorProdutos[v].qntdEstoque);
    }
}
// Função para cadastrar um produto
int cadastrarProduto(Tprodutos vetorProdutos[], int *qntdProdutosLoja){
    int index = *qntdProdutosLoja;

    printf("Digite a descricao do produto: ");
    inputString(vetorProdutos[index].descricao, MAX);
    limparBuffer();

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &vetorProdutos[index].qntdEstoque);

    printf("Qual o preco da unidade do produto: ");
    scanf("%f", &vetorProdutos[index].valorUnidade);
    limparBuffer();

    // Seta o ID do produto como o index atual
    vetorProdutos[index].idProduto  = *qntdProdutosLoja;

    // Incrementa a quantidade de produtos na loja
    (*qntdProdutosLoja)++;

    // Retorna o ID do cliente cadastrado
    return vetorProdutos[index].idProduto;
}
// Função para cadastrar a Venda no historico de compras do cliente (armazenar a compra do cliente na lista)
void adicionarCompra(Tcliente *cliente, int idProduto, int quantidade, char *descricao, float valorTotal){
    // Atualiza a lista de compras do cliente
    int index = cliente->qtdCompras;
    cliente->listaCompras[index].idProduto = idProduto;
    cliente->listaCompras[index].quantidade = quantidade;
    strcpy(cliente->listaCompras[index].descricao, descricao); // Copia o Conteúdo de "descricao" para o campo "descricao" da struct
    cliente->listaCompras[index].valorTotal = valorTotal;
    cliente->qtdItensComprados += quantidade;
    cliente->qtdCompras++;
}
// Função para cadastrar uma venda
int cadastrarVenda(Tcliente vetorClientes[], Tprodutos vetorProdutos[], Tvendas vetorVendas[], int *qntdVendasLoja, int *qntdProdutosLoja, int *qntdClientesLoja)
{
    int index = *qntdVendasLoja;

    listaClientes(vetorClientes, qntdClientesLoja);
    // Solicita o ID do cliente que está comprando e valida
    int idCliente;
    if (verificarInputID("cliente", *qntdClientesLoja, &idCliente) != 0) {
        printf("Erro ao verificar ID do cliente.\n");
        return -1;
    }
    vetorVendas[index].idCliente = idCliente;
    int clienteIndex = searchCliente(vetorClientes, qntdClientesLoja, idCliente);
    if (clienteIndex == -1) {
        return -1;
    }
    if (!checkLimiteCompras(vetorClientes, idCliente)) {
        return -1;
    }

    listarProdutos(vetorProdutos, qntdProdutosLoja);
    // Solicita o ID do produto que está sendo comprado e valida
    int idProduto;
    if (verificarInputID("produto", *qntdProdutosLoja, &idProduto) != 0) {
        printf("Erro ao verificar ID do produto.\n");
        return -1;
    }
    vetorVendas[index].idProduto = idProduto;
    int produtoIndex = searchProduto(vetorProdutos, qntdProdutosLoja, idProduto);
    if (produtoIndex == -1) {
        return -1;
    }

    printf("Quantos produtos esse cliente comprou? ");
    if (scanf("%d", &vetorVendas[index].qtndItensVendidos) != 1) {
        printf("Erro: Entrada inválida para quantidade de produtos.\n");
        limparBuffer();
        return -1;
    }
    limparBuffer(); 
    // Verifica se a quantidade de produtos em estoque é suficiente
    if (vetorProdutos[produtoIndex].qntdEstoque < vetorVendas[index].qtndItensVendidos) {
        printf("Erro: Quantidade de produtos em estoque insuficiente!\n");
        return -1;
    }

    // Informações da Compra
    int qtdItensComprados = vetorVendas[index].qtndItensVendidos;
    float valor_unitario_do_produto = vetorProdutos[produtoIndex].valorUnidade;
    float valorTotal = qtdItensComprados * valor_unitario_do_produto;
    vetorVendas[index].totalVenda = valorTotal;
    printf("Valor Total da compra: %.2f\n", valorTotal);

    // Adicionando a compra a lista de compras do cliente
    char descricao[MAX];
    strncpy(descricao, vetorProdutos[produtoIndex].descricao, MAX - 1);
    descricao[MAX - 1] = '\0'; // Garantir que a string esteja terminada
    adicionarCompra(&vetorClientes[clienteIndex], vetorVendas[index].idProduto, qtdItensComprados, descricao, valorTotal);

    // Atualizar estoque
    vetorProdutos[produtoIndex].qntdEstoque -= vetorVendas[index].qtndItensVendidos;
    // Atualizando o Valor Total de Vendas da Loja
    vetorVendas[index].idVenda = *qntdVendasLoja;

    (*qntdVendasLoja)++;

    return vetorVendas[index].idVenda;
}
// Função para exibir a tabela de vendas
void tabelaVendas(Tvendas vetorVendas[], Tcliente vetorClientes[], Tprodutos vetorProdutos[], float totalVendasLoja, int qntdVendasLoja) {
    int totalItensVendidos = 0;
    totalVendasLoja = 0.0; // Inicializa o total de vendas da loja
    
    printf("Tabela de Vendas\n");
    printf("--------------------------\n");
    // For para percorrer a quantidade total de vendas e exibir as informações de cada venda
    for (int v = 0; v < qntdVendasLoja; v++) {
        // Cria uma variável para armazenar as informações do cliente
        Tcliente cliente;
        // For para percorrer o MAX e comparar o id do cliente com o id do cliente da venda atual
        for (int c = 0; c < MAX; c++) {
            if (vetorClientes[c].idCliente == vetorVendas[v].idCliente) {
                cliente = vetorClientes[c];
                break;
            }
        }

        // Cria uma variável para armazenar as informações do produto
        Tprodutos produto;
        // For para percorrer o MAX e comparar o id do produto com o id do produto da venda atual
        for (int p = 0; p < MAX; p++) {
            if (vetorProdutos[p].idProduto == vetorVendas[v].idProduto) {
                produto = vetorProdutos[p];
                break;
            }
        }

        // Exibir informações da venda atual Formatadas
        printf("Cliente: %s | CPF: %s\n", cliente.nome, cliente.cpf);
        printf(
        "Descricao do produto: %s | Quantidade: %d | Valor Unitario: %.2f\n", 
        produto.descricao, vetorVendas[v].qtndItensVendidos,
        produto.valorUnidade);
        printf("Valor Total: %.2f\n", vetorVendas[v].totalVenda);
        printf("--------------------------\n");

        totalItensVendidos += vetorVendas[v].qtndItensVendidos;
        totalVendasLoja += vetorVendas[v].totalVenda; // Soma o valor da venda atual ao total
    }

    printf("Quantidade total de itens vendidos: %d\n", totalItensVendidos);
    printf("Quantidade total de vendas da loja: %d\n", qntdVendasLoja);
    printf("Valor Total de Vendas da Loja: %.2f\n", totalVendasLoja);
}
// Função para realizar o sorteio
int realizarSorteio(Tcliente vetorClientes[], int qntdClientesLoja, Tsorteio *sorteio)
{
    sorteio->qtdClientesQualificados = 0; // Inicializa a quantidade de clientes qualificados

    // Verifica clientes qualificados
    for (int v = 0; v < qntdClientesLoja; v++) {
        if (vetorClientes[v].qtdItensComprados > 5) {
            int index = sorteio->qtdClientesQualificados;
            sorteio->clientesQualificados[index].idCliente = vetorClientes[v].idCliente;
            strcpy(sorteio->clientesQualificados[index].nome, vetorClientes[v].nome);
            strcpy(sorteio->clientesQualificados[index].cpf, vetorClientes[v].cpf);
            sorteio->qtdClientesQualificados++;
        }
    }

    if (sorteio->qtdClientesQualificados == 0) {
        printf("Nenhum cliente qualificado para o sorteio\n");
        return -1;
    } else {
        srand(time(NULL)); // Inicializa o gerador de números aleatórios
        int sorteado = rand() % sorteio->qtdClientesQualificados;

        // Exibe o cliente sorteado
        printf("Cliente sorteado: %s\n", sorteio->clientesQualificados[sorteado].nome);
        printf("Numero de registro: %d\n", sorteio->clientesQualificados[sorteado].idCliente);
        printf("CPF: %s\n", sorteio->clientesQualificados[sorteado].cpf);
        return 1;
    }
}

// ------------------ Main ------------------
int main(){
    // Inicialização dos vetores 
    Tcliente vetorClientes[MAX];
    Tprodutos vetorProdutos[MAX];
    Tvendas vetorVendas[MAX];
    Tsorteio vetorSorteio[MAX];

    // Variáveis para armazenar o valor Total de:
    int qntdProdutosLoja = 0;
    int qntdClientesLoja = 0;
    int qntdVendasLoja = 0;
    int totalVendasLoja = 0;

    int userInput; 

    while (1){
        system(CLEAR_COMMAND); // Limpa o terminal antes de exibir o menu
        printf("\nMenu\n");
        printf("1. Cadastro de Cliente\n");
        printf("2. Cadastro de Produto\n");
        printf("3. Cadastro de Venda\n");
        printf("4. Total de Vendas\n");
        printf("5. Sorteio\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &userInput);
        limparBuffer();
        
        system(CLEAR_COMMAND);

        switch (userInput){
            case 1: 
                {
                    int idCliente = cadastrarCliente(vetorClientes, &qntdClientesLoja);
                    if (idCliente >= 0) {
                        printf("Cliente de ID %d cadastrado com sucesso\n", idCliente);
                    } else {
                        printf("Erro ao cadastrar cliente\n");
                    }
                    pausar();
                }
                break;
            case 2:
                {
                    int idProduto = cadastrarProduto(vetorProdutos, &qntdProdutosLoja);
                    if (idProduto >= 0) {
                        printf("Produto de ID %d cadastrado com sucesso\n", idProduto);
                    } else {
                        printf("Erro ao cadastrar produto\n");
                    }
                    pausar();
                }
                break;
            case 3:
                {
                    int idVenda = cadastrarVenda(vetorClientes, vetorProdutos, vetorVendas, &qntdVendasLoja, &qntdProdutosLoja, &qntdClientesLoja);
                    if (idVenda >= 0) {
                        printf("Venda de ID %d cadastrada com sucesso\n", idVenda);
                    } else {
                        printf("Erro ao cadastrar venda\n");
                    }
                    pausar();
                }
                break;
            case 4:
                system(CLEAR_COMMAND);
                tabelaVendas(vetorVendas, vetorClientes, vetorProdutos, totalVendasLoja, qntdVendasLoja);
                pausar();
                break;
            case 5:
                {
                    int sorteio = realizarSorteio(vetorClientes, qntdClientesLoja, &vetorSorteio[0]);
                    if (sorteio >= 0) {
                        printf("Sorteio realizado com sucesso\n");
                    } else {
                        printf("Erro ao realizar sorteio\n");
                    }
                    pausar();
                }
                break;
            case 6:
                printf("Programa Finalizado");
                return 0;
            default:
                printf("Opcao invalida\n");
                pausar();
                break;
        } 
    }
}