#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
    int qntd_eletrodomesticos_adquiridos;
}Tvendas;

typedef struct compras {
    int codigo_produto;
    int qnt_eletrodomesticos_adquiridos;
    int numero_registro_cliente;
    int codigo_venda;
}Tcompras;

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}  // Limpa o buffer de entrada
}

void cadastro_cliente(Tclientes vetor_clientes[], int *variavel_contagem_vetor_cliente, int *quantidade_de_clientes) {
    int index = *variavel_contagem_vetor_cliente;

    printf("Digite o nome do Cliente: ");
    fgets(vetor_clientes[index].nome, MAX, stdin);
    limpar_buffer();  // Limpa o buffer após fgets
    vetor_clientes[index].numero_registro_cliente = index;
    (*variavel_contagem_vetor_cliente)++;

    printf("Digite o dia de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.dia, 3, stdin);
    limpar_buffer();

    printf("Digite o mes de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.mes, 3, stdin);
    limpar_buffer();

    printf("Digite o ano de nascimento do cliente: ");
    fgets(vetor_clientes[index].data_nascimento.ano, 5, stdin);
    limpar_buffer();

    printf("Digite CPF do cliente: ");
    fgets(vetor_clientes[index].cpf, MAX, stdin);
    limpar_buffer();

    printf("Digite RG do cliente: ");
    fgets(vetor_clientes[index].rg, MAX, stdin);
    limpar_buffer();

    printf("Digite a cidade onde mora: ");
    fgets(vetor_clientes[index].endereco.cidade, MAX, stdin);
    limpar_buffer();

    printf("Digite o bairro onde mora: ");
    fgets(vetor_clientes[index].endereco.bairro, MAX, stdin);
    limpar_buffer();

    printf("Digite CEP: ");
    fgets(vetor_clientes[index].endereco.cep, MAX, stdin);
    limpar_buffer();

    printf("Digite a rua onde mora: ");
    fgets(vetor_clientes[index].endereco.rua, MAX, stdin);
    limpar_buffer();

    printf("Digite o numero da casa: ");
    fgets(vetor_clientes[index].endereco.numero_residencia, MAX, stdin);
    limpar_buffer();

    (*quantidade_de_clientes)++;

    printf("Cadastro de cliente numero: %d \n", vetor_clientes[index].numero_registro_cliente);
}

void cadastro_produtos(Tprodutos vetor_produtos[], int *variavel_contagem_vetor_produto){
    int index = *variavel_contagem_vetor_produto;

    vetor_produtos[index].codigo_produto  = *variavel_contagem_vetor_produto;
    (*variavel_contagem_vetor_produto)++;

    printf("Digite a descricao do produto: ");
    fgets(vetor_produtos[index].descricao, MAX, stdin);
    limpar_buffer();

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &vetor_produtos[index].qntd_estoque);

    printf("Qual o preco da unidade do produto: ");
    scanf("%f", &vetor_produtos[index].valor_unitario);

    limpar_buffer();  // Limpa o buffer após o uso do scanf

    printf("Cadastro de produto numero: %d\n", vetor_produtos[index].codigo_produto);
}

int vendas_realizadas(Tclientes vetor_clientes[], Tprodutos vetor_produtos[], Tvendas vetor_vendas[], Tcompras vetor_compras[], int *variavel_contagem_vetor_vendas, int *variavel_contagem_vetor_produto, int quantidade_de_vendas, int *quantidade_de_sorteios){

    int index = *variavel_contagem_vetor_vendas;
    vetor_vendas[index].codigo_venda = *variavel_contagem_vetor_vendas;
    (*variavel_contagem_vetor_vendas)++;

    printf("Qual o numero do registro do cliente que esta comprando? \n");
    scanf("%d", &vetor_vendas[index].numero_registro_cliente);

    printf("Qual o codigo do produto? \n");
    scanf("%d", &vetor_vendas[index].codigo_produto);

    printf("Quantos produtos esse cliente comprou? i\n");
    scanf("%d", &vetor_vendas[index].qntd_eletrodomesticos_adquiridos);

    limpar_buffer();  // Limpa o buffer após o uso de scanf

    if (vetor_vendas[index].qntd_eletrodomesticos_adquiridos > 5){
        vetor_compras[index].codigo_produto = vetor_vendas[index].codigo_produto;
        vetor_compras[index].numero_registro_cliente = vetor_vendas[index].numero_registro_cliente;
        vetor_compras[index].qnt_eletrodomesticos_adquiridos = vetor_vendas[index].qntd_eletrodomesticos_adquiridos;
        vetor_compras[index].codigo_venda = vetor_vendas[index].codigo_venda;
    }

    int valor_unitario_do_produto = 0;
    for (int i = 0; i < *variavel_contagem_vetor_produto; i++) {
        if (vetor_produtos[i].codigo_produto == vetor_vendas[index].codigo_produto){
            valor_unitario_do_produto = vetor_produtos[i].valor_unitario;
            (*quantidade_de_sorteios)++;
        }
    }

    int valor_total = vetor_vendas[index].qntd_eletrodomesticos_adquiridos * valor_unitario_do_produto;
    vetor_vendas[index].total_a_pagar = valor_total;

    printf("Valor Total da compra: %d\n", valor_total);

    quantidade_de_vendas++;
    printf("numero total de vendas", quantidade_de_vendas);
    return quantidade_de_vendas;
}

int totalize_vendas(Tvendas vetor_vendas[], const int quantidade_de_vendas){
    int total_das_vendas = 0;
    for (int i = 0; i < quantidade_de_vendas; i++){
        total_das_vendas += vetor_vendas[i].total_a_pagar;
    }
    return total_das_vendas;
}

void sorteio(const int quantidade_de_sorteios, Tcompras vetor_compras[], Tclientes vetor_clientes[], const int quantidade_de_clientes){

    srand(time(NULL));

    int random_number = rand() % quantidade_de_sorteios;
    printf("Numero Sorteado: %d\n", random_number);

    int numero_registro_cliente;
    numero_registro_cliente = vetor_compras[random_number].numero_registro_cliente;
    for (int i = 0; i < quantidade_de_clientes; i++){
        if (vetor_clientes[i].numero_registro_cliente == numero_registro_cliente){
            printf("Ganhador e o cliente: %s", vetor_clientes[i].nome);
        }
    }

}

int main(){

    Tclientes vetor_clientes[MAX];
    Tprodutos vetor_produtos[MAX];

    int variavel_contagem_vetor_produto = 0;
    int variavel_contagem_vetor_cliente = 0;
    int entrada_usuario; 

    Tvendas vetor_vendas[MAX];
    Tcompras vetor_compras[MAX];
    int quantidade_de_vendas = 0;
    int quantidade_de_sorteios = 0;
    int quantidade_de_clientes = 0;


    int variavel_contagem_vetor_vendas = 0;

    while (1){
        printf("\nMenu\n");
        printf("Cadastro de Cliente (1): \nCadastro de Produtos (2): \nVendas (3): \nTotal de Vendas (4): \nSorteio (5): \nSair(6): ");
        scanf("%d", &entrada_usuario);

        limpar_buffer();  // Limpa o buffer após scanf

        if (entrada_usuario == 6){
            printf("Programa Finalizado");
            break;
        }

        switch (entrada_usuario){
            case 1: 
                cadastro_cliente(vetor_clientes, &variavel_contagem_vetor_cliente, &quantidade_de_clientes);
                break;
            case 2:
                cadastro_produtos(vetor_produtos, &variavel_contagem_vetor_produto);
                break;
            case 3:
                vendas_realizadas(vetor_clientes, vetor_produtos, vetor_vendas, vetor_compras, &variavel_contagem_vetor_vendas, &variavel_contagem_vetor_produto, quantidade_de_vendas, &quantidade_de_sorteios);
                break;
            case 4:
                printf("Total de Vendas: %d\n", totalize_vendas(vetor_vendas, quantidade_de_vendas));
                break;
            case 5:
                sorteio(quantidade_de_sorteios, vetor_compras, vetor_clientes, quantidade_de_clientes);
                break;
            default:
                printf("Opcao invalida\n");
                break;
        } 
    }
}
