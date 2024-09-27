#ifndef PRODUTO_H
#define PRODUTO_H

#define MAX_PRODUTOS 50 // Limite máximo de produtos

// Definição da estrutura Produto
typedef struct {
    int codigo;
    char nome[30];
    float preco;
} Produto;

// Funções relacionadas ao Produto
void cadastrarProduto(Produto produtos[], int *totalProdutos);
void listarProdutos(Produto produtos[], int totalProdutos);
Produto* pegarProdutoPorCodigo(Produto produtos[], int totalProdutos, int codigo);
void atualizarProduto(Produto produtos[], int totalProdutos);
void exibirProduto(Produto prod);

#endif
