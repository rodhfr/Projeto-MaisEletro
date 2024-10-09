#ifndef TYPEDEF_H
#define TYPEDEF_H
#define MAX 100

typedef struct data_nascimento {
    int dia;
    int mes;
    int ano;
}TDataNascimento;

typedef struct clientes {
    int numero_registro;
    char nome[MAX];
    TDataNascimento data_nascimento;
    int cpf;
    int rg;
    char cidade[MAX];
    char endereco[MAX];
}Tclientes;

typedef struct produtos {
    int codigo_produto;
    char descricao[MAX];
    int qntd_estoque;
    int valor_unitario;
}Tprodutos;

typedef struct vendas {
    int codigo_venda;
    int n_registro_cliente;
    int codigo_produto;
    float total_a_pagar;
}Tvendas;

typedef struct compras {
    int n_registro_cliente;
    int qntd_eletrodomesticos_adquiridos;
}Tcompras;

#endif // TYPEDEF_H