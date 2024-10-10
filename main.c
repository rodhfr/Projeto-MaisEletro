#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

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

void ler_string (char *str, int tamanho)
{
    fgets(str, tamanho, stdin);
    size_t len = strlen(str);
    if (len>0 && str[len-1] == '\n')
    {
        str[len-1] = '\0';
    }
    else
    {
        limpar_buffer();
    }
}

void listaClientes(Tclientes vetor_clientes[], int *variavel_contagem_vetor_cliente)
{
    printf("%-10s %-12s %-50s\n", "Codigo", "CPF", "Nome");
    for (int i=0;i<(*variavel_contagem_vetor_cliente);i++)
    {
        printf("%-10d %-12s %-30s\n", vetor_clientes[i].numero_registro_cliente, 
        vetor_clientes[i].cpf, vetor_clientes[i].nome);
    }
}

void cadastro_cliente(Tclientes vetor_clientes[], int *variavel_contagem_vetor_cliente, int *quantidade_de_clientes) {
    int index = *variavel_contagem_vetor_cliente;

    printf("Digite o nome do Cliente: ");
    ler_string(vetor_clientes[index].nome, MAX);
    limpar_buffer();  // Limpa o buffer após fgets
    vetor_clientes[index].numero_registro_cliente = index;
    (*variavel_contagem_vetor_cliente)++;

    printf("Digite o dia de nascimento do cliente: ");
    ler_string(vetor_clientes[index].data_nascimento.dia, 3);
    limpar_buffer();

    printf("Digite o mes de nascimento do cliente: ");
    ler_string(vetor_clientes[index].data_nascimento.mes, 3);
    limpar_buffer();

    printf("Digite o ano de nascimento do cliente: ");
    ler_string(vetor_clientes[index].data_nascimento.ano, 5);
    limpar_buffer();

    printf("Digite CPF do cliente: ");
    ler_string(vetor_clientes[index].cpf, MAX);
    limpar_buffer();

    printf("Digite RG do cliente: ");
    ler_string(vetor_clientes[index].rg, MAX);
    limpar_buffer();

    printf("Digite a cidade onde mora: ");
    ler_string(vetor_clientes[index].endereco.cidade, MAX);
    limpar_buffer();

    printf("Digite o bairro onde mora: ");
    ler_string(vetor_clientes[index].endereco.bairro, MAX);
    limpar_buffer();

    printf("Digite CEP: ");
    ler_string(vetor_clientes[index].endereco.cep, MAX);
    limpar_buffer();

    printf("Digite a rua onde mora: ");
    ler_string(vetor_clientes[index].endereco.rua, MAX);
    limpar_buffer();

    printf("Digite o numero da casa: ");
    ler_string(vetor_clientes[index].endereco.numero_residencia, MAX);
    limpar_buffer();
    (*quantidade_de_clientes)++;

    printf("Cadastro de cliente numero: %d \n", vetor_clientes[index].numero_registro_cliente);
}

void ListaDeProdutos (Tprodutos vetor_produtos[], int *variavel_contagem_vetor_produto)
{
    printf("%-10s %-20s %-10s\n", "Codigo", "Descricao", "Quantidade");
    for (int i=0;i<(*variavel_contagem_vetor_produto); i++)
    {
        //printf("\nCodigo: %d Nome: %s Quantidade:%d\n", vetor_produtos[i].codigo_produto, 
        printf("%-10d %-20s %-10d\n", vetor_produtos[i].codigo_produto, 
        vetor_produtos[i].descricao, vetor_produtos[i].qntd_estoque);
    }
}

void cadastro_produtos(Tprodutos vetor_produtos[], int *variavel_contagem_vetor_produto){
    int index = *variavel_contagem_vetor_produto;

    vetor_produtos[index].codigo_produto  = *variavel_contagem_vetor_produto;
    (*variavel_contagem_vetor_produto)++;

    printf("Digite a descricao do produto: ");
    ler_string(vetor_produtos[index].descricao, MAX);
    limpar_buffer();

    printf("Digite a quantidade em estoque: ");
    scanf("%d", &vetor_produtos[index].qntd_estoque);

    printf("Qual o preco da unidade do produto: ");
    scanf("%f", &vetor_produtos[index].valor_unitario);

    limpar_buffer();  // Limpa o buffer após o uso do scanf

    printf("Cadastro de produto numero: %d\n", vetor_produtos[index].codigo_produto);
}

void vendas_realizadas(Tclientes vetor_clientes[],Tprodutos vetor_produtos[], Tvendas vetor_vendas[], Tcompras vetor_compras[], int *variavel_contagem_vetor_vendas, int *variavel_contagem_vetor_produto, int *quantidade_de_vendas, int *quantidade_de_sorteios, int *variavel_contagem_vetor_clientes)
{
    int index = *variavel_contagem_vetor_vendas;
    vetor_vendas[index].codigo_venda = *variavel_contagem_vetor_vendas;
    (*variavel_contagem_vetor_vendas)++;

    printf("Lista dos clientes: \n");
    listaClientes(vetor_clientes, variavel_contagem_vetor_clientes);

    printf("Qual o numero do registro do cliente que esta comprando? ");
    scanf("%d", &vetor_vendas[index].numero_registro_cliente);
    limpar_buffer(); 

    int clienteEncontrado = 0;
    for (int i=0;i<(*variavel_contagem_vetor_clientes);i++)
    {
        if (vetor_clientes[i].numero_registro_cliente == vetor_vendas[index].numero_registro_cliente)
        {
            clienteEncontrado = 1;

            printf("Lista dos produtos: \n");
            ListaDeProdutos(vetor_produtos, variavel_contagem_vetor_produto);
            printf("Quantos produtos esse cliente comprou? ");
            scanf("%d", &vetor_vendas[index].qntd_eletrodomesticos_adquiridos);
            limpar_buffer(); 

            printf("Qual o codigo do produto? ");
            scanf("%d", &vetor_vendas[index].codigo_produto);
            limpar_buffer(); 

            int produto_encontrado = 0;  // Verificação se o produto foi encontrado
            for (int i=0; i<(*variavel_contagem_vetor_vendas); i++)
            {
                if (vetor_produtos[i].codigo_produto == vetor_vendas[index].codigo_produto)
                {
                    if (vetor_produtos[i].qntd_estoque < vetor_vendas[index].qntd_eletrodomesticos_adquiridos)
                    {
                        printf("\nNao tem produto suficiente em estoque");
                    }
                    else
                    {
                        if (vetor_vendas[index].qntd_eletrodomesticos_adquiridos > 5)
                        {
                            vetor_compras[index].codigo_produto = vetor_vendas[index].codigo_produto;
                            vetor_compras[index].numero_registro_cliente = vetor_vendas[index].numero_registro_cliente;
                            vetor_compras[index].qnt_eletrodomesticos_adquiridos = vetor_vendas[index].qntd_eletrodomesticos_adquiridos;
                            vetor_compras[index].codigo_venda = vetor_vendas[index].codigo_venda;
                            (*quantidade_de_sorteios)++;
                        }
                        float valor_unitario_do_produto = 0;  // Certifique-se de que seja float
                        produto_encontrado = 1;  // Produto encontrado
                        valor_unitario_do_produto = vetor_produtos[i].valor_unitario;
                        float valor_total = vetor_vendas[index].qntd_eletrodomesticos_adquiridos * valor_unitario_do_produto;
                        vetor_vendas[index].total_a_pagar = valor_total;

                        printf("Valor Total da compra: %.2f\n", valor_total);
                        (*quantidade_de_vendas)++;
                        vetor_produtos[i].qntd_estoque -= vetor_vendas[index].qntd_eletrodomesticos_adquiridos;

                        break;
                    }
                }
            }
            if (!produto_encontrado) 
            {
                printf("Erro: Produto com o codigo %d nao encontrado!\n", vetor_vendas[index].codigo_produto);
            }

            break;
        }

    }
    if(!clienteEncontrado)
    {
        printf("Erro: Cliente nao existe");
    }
}

int totalize_vendas(Tvendas vetor_vendas[], int quantidade_de_vendas){
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
        //system("cls");
        printf("\nMenu\n");
        printf("Cadastro de Cliente (1): \nCadastro de Produtos (2): \nVendas (3): \nTotal de Vendas (4): \nSorteio (5): \nSair(6): ");
        scanf("%d", &entrada_usuario);

        limpar_buffer();  // Limpa o buffer após scanf

        if (entrada_usuario == 6){
            printf("Programa Finalizado");
            break;
        }
        //system("cls");
        switch (entrada_usuario){
            case 1: 
                cadastro_cliente(vetor_clientes, &variavel_contagem_vetor_cliente, &quantidade_de_clientes);
                break;
            case 2:
                cadastro_produtos(vetor_produtos, &variavel_contagem_vetor_produto);
                break;
            case 3:
                vendas_realizadas(vetor_clientes,vetor_produtos, vetor_vendas, vetor_compras, &variavel_contagem_vetor_vendas, &variavel_contagem_vetor_produto, &quantidade_de_vendas, &quantidade_de_sorteios,&variavel_contagem_vetor_cliente);
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