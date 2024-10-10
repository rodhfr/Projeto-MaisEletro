#ifndef STRUCTS_H
#define STRUCTS_H

#define MAX 100
#define MAX_CPF_RG 12
#define MAX_CEP 9
#define MAX_COMPRAS 50

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



#endif //STRUCTS_H  