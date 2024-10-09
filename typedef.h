#ifndef TYPEDEF_H
#define TYPEDEF_H
#define MAX 100

typedef struct data_nascimento {
    int dia;
    int mes;
    int ano;
}TDataNascimento;

typedef struct endereco {
    char rua[MAX];
    char bairro[MAX];
    char cidade[MAX];
    int numero_residencia;
    int cep;
} Tendereco;

typedef struct clientes {
    int numero_registro_cliente;
    char nome[MAX];
    TDataNascimento data_nascimento;
    int cpf;
    int rg;
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




#endif // TYPEDEF_H



