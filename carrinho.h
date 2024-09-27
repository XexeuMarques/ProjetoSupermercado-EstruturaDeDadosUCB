#ifndef CARRINHO_H
#define CARRINHO_H

#include "produto.h"

#define MAX_CARRINHO 50  // Limite máximo de itens no carrinho

// Definição da estrutura Carrinho
typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

// Funções relacionadas ao Carrinho
void adicionarAoCarrinho(Carrinho carrinho[], int *totalItens, Produto produto);
void visualizarCarrinho(Carrinho carrinho[], int totalItens);
void removerDoCarrinho(Carrinho carrinho[], int *totalItens);
void fecharPedido(Carrinho carrinho[], int *totalItens);

#endif
