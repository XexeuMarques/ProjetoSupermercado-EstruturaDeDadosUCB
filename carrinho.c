#include <stdio.h>
#include "carrinho.h"

// Função para adicionar produto ao carrinho
void adicionarAoCarrinho(Carrinho carrinho[], int *totalItens, Produto produto) {
    if (*totalItens >= MAX_CARRINHO) {
        printf("\nErro: O carrinho atingiu o limite de %d itens.\n", MAX_CARRINHO);
        return;
    }

    for (int i = 0; i < *totalItens; i++) {
        if (carrinho[i].produto.codigo == produto.codigo) {
            carrinho[i].quantidade++;
            printf("\nQuantidade do produto atualizada no carrinho.\n");
            return;
        }
    }

    carrinho[*totalItens].produto = produto;
    carrinho[*totalItens].quantidade = 1;
    (*totalItens)++;
    
    printf("\nProduto adicionado ao carrinho!\n");
}

// Função para visualizar o carrinho
void visualizarCarrinho(Carrinho carrinho[], int totalItens) {
    if (totalItens == 0) {
        printf("\nCarrinho vazio.\n");
        return;
    }

    printf("\n==== Carrinho de Compras ====\n");
    for (int i = 0; i < totalItens; i++) {
        printf("Produto: %s | Quantidade: %d | Preço Unitário: R$%.2f\n", 
                carrinho[i].produto.nome, carrinho[i].quantidade, carrinho[i].produto.preco);
    }
    printf("=============================\n\n");
}

// Função para remover produto do carrinho
void removerDoCarrinho(Carrinho carrinho[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nCarrinho está vazio.\n");
        return;
    }

    int codigo;
    printf("Digite o código do produto que deseja remover: ");
    if (scanf("%d", &codigo) != 1) {
        printf("\nErro: Código inválido!\n");
        return;
    }

    for (int i = 0; i < *totalItens; i++) {
        if (carrinho[i].produto.codigo == codigo) {
            // Remover produto e ajustar carrinho
            for (int j = i; j < (*totalItens) - 1; j++) {
                carrinho[j] = carrinho[j + 1];
            }
            (*totalItens)--;
            printf("\nProduto removido do carrinho.\n");
            return;
        }
    }

    printf("\nErro: Produto não encontrado no carrinho.\n");
}

// Função para fechar o pedido e calcular o total
void fecharPedido(Carrinho carrinho[], int *totalItens) {
    if (*totalItens == 0) {
        printf("\nCarrinho vazio. Não é possível fechar o pedido.\n");
        return;
    }

    float total = 0.0;
    printf("\n==== Fatura ====\n");
    for (int i = 0; i < *totalItens; i++) {
        float subtotal = carrinho[i].quantidade * carrinho[i].produto.preco;
        printf("Produto: %s | Quantidade: %d | Subtotal: R$%.2f\n", 
                carrinho[i].produto.nome, carrinho[i].quantidade, subtotal);
        total += subtotal;
    }
    printf("=================\n");
    printf("Total da compra: R$%.2f\n", total);

    *totalItens = 0;  // Limpa o carrinho
    printf("\nPedido fechado com sucesso! Obrigado pela compra.\n");
}
