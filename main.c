#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "structs.h"
#include "funcoes.h"

// Definição da função para limpar o terminal de acordo com o sistema operacional
#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#else
    #define CLEAR_COMMAND "clear"
#endif


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