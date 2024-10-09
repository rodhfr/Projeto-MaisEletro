#include <stdio.h>

#define MAX 100

typedef struct data_nascimento {
    char dia[3];
    char mes[3];
    char ano[5];
}TDataNascimento;

typedef struct endereco {
    char rua[MAX];
    char bairro[MAX];
    char cidade[MAX];
    char numero_residencia[MAX];
    char cep[MAX];
} Tendereco;

typedef struct clientes {
    int numero_registro_cliente;
    char nome[MAX];
    TDataNascimento data_nascimento;
    char cpf[MAX];
    char rg[MAX];
    Tendereco endereco;
}Tclientes;

typedef struct produtos {
    int codigo_produto;
    char descricao[MAX];
    int qntd_estoque;
    float valor_unitario;
}Tprodutos;

typedef struct vendas {
    int codigo_venda;
    int numero_registro_cliente;
    int codigo_produto;
    float total_a_pagar;
}Tvendas;

typedef struct compras {
    int numero_registro_cliente;
    int qntd_eletrodomesticos_adquiridos;
}Tcompras;


Tclientes vetor_clientes[MAX];

int variavel_contagem_vetor_cliente = 0;

void cadastro_cliente(Tclientes vetor_clientes[], int *variavel_contagem_vetor_cliente) {
    // esse index e para ver qual o cliente estamos mexendo
    int index = *variavel_contagem_vetor_cliente;

    // cadastro do nome 
    printf("Digite o nome do Cliente: ");
    fgets(vetor_clientes[index].nome, MAX, stdin);
    vetor_clientes[index].numero_registro_cliente = index;
    (*variavel_contagem_vetor_cliente)++;

    // cadastro nascimento do cliente
    printf("Digite o dia de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.dia, MAX, stdin);

    printf("Digite o mes de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.mes, MAX, stdin);

    printf("Digite o ano de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.ano, MAX, stdin);

    // cadastro cpf
    printf("Digite CPF do cliente: ");
    fgets(vetor_clientes[index].cpf, MAX, stdin);

    // cadastro rg
    printf("Digite RG do cliente: ");
    fgets(vetor_clientes[index].rg, MAX, stdin);

    // cidade onde mora
    printf("Digite a cidade onde mora: ");
    fgets(vetor_clientes[index].endereco.cidade, MAX, stdin);

    // bairro onde mora
    printf("Digite a bairro onde mora: ");
    fgets(vetor_clientes[index].endereco.bairro, MAX, stdin);

    // cep
    printf("Digite CEP: ");
    fgets(vetor_clientes[index].endereco.cep, MAX, stdin);
    
    // rua onde mora
    printf("Digite a rua onde mora: ");
    fgets(vetor_clientes[index].endereco.rua, MAX, stdin);

    // numero de onde mora
    printf("Digite o numero da casa: ");
    fgets(vetor_clientes[index].endereco.numero_residencia, MAX, stdin);
}


