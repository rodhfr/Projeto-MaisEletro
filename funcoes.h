#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

void inputString (char *str, int tamanho);
void limparBuffer();
void pausar();
void inputString (char *str, int tamanho);
int verificarInputID(const char *nomeItem, int maxRegistros, int *id);
int checkLimiteCompras(Tcliente vetorClientes[], int idCliente);
int searchCliente(Tcliente vetorClientes[], int *qntdClientesLoja, int idCliente);
int searchProduto(Tprodutos vetorProdutos[], int *qntdProdutosLoja, int idProduto);
void listaClientes(Tcliente vetorClientes[], int *qntdClientesLoja);
int cadastrarCliente(Tcliente vetorClientes[], int *qntdClientesLoja);
void listarProdutos (Tprodutos vetorProdutos[], int *qntdProdutosLoja);
int cadastrarProduto(Tprodutos vetorProdutos[], int *qntdProdutosLoja);
void adicionarCompra(Tcliente *cliente, int idProduto, int quantidade, char *descricao, float valorTotal);
int cadastrarVenda(Tcliente vetorClientes[], Tprodutos vetorProdutos[], Tvendas vetorVendas[], int *qntdVendasLoja, int *qntdProdutosLoja, int *qntdClientesLoja);
void tabelaVendas(Tvendas vetorVendas[], Tcliente vetorClientes[], Tprodutos vetorProdutos[], float totalVendasLoja, int qntdVendasLoja);
int realizarSorteio(Tcliente vetorClientes[], int qntdClientesLoja, Tsorteio *sorteio);
void carregarVendas(Tvendas vetorVendas[], int *qntdVendasLoja, const char *nomeArquivo);
void carregarProdutos(Tprodutos vetorProdutos[], int *qntdProdutosLoja, const char *nomeArquivo);
void carregarClientes(Tcliente vetorClientes[], int *qntdClientesLoja, const char *nomeArquivo);
void salvarVendas(Tvendas vetorVendas[], int qntdVendasLoja, const char *nomeArquivo);
void salvarProdutos(Tprodutos vetorProdutos[], int qntdProdutosLoja, const char *nomeArquivo);
void salvarClientes(Tcliente vetorClientes[], int qntdClientesLoja, const char *nomeArquivo);




#endif // FUNCOES_H