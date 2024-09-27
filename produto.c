#include <stdio.h>
#include <string.h>
#include "produto.h"

// Exibe as informações detalhadas de um produto
void exibirProduto(Produto prod) {
    printf("Código: %d | Nome: %s | Preço: R$%.2f\n", prod.codigo, prod.nome, prod.preco);
}

// Função para cadastrar um novo produto com validação
void cadastrarProduto(Produto produtos[], int *totalProdutos) {
    if (*totalProdutos >= MAX_PRODUTOS) {
        printf("\nNão é possível cadastrar mais produtos. Limite de %d atingido.\n", MAX_PRODUTOS);
        return;
    }

    Produto novoProduto;
    novoProduto.codigo = 1000 + (*totalProdutos);

    printf("Digite o nome do produto (máx. 30 caracteres): ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = 0;  // Remove a nova linha
    
    if (strlen(novoProduto.nome) == 0) {
        printf("\nErro: O nome do produto não pode ser vazio!\n");
        return;
    }

    printf("Digite o preço do produto (valor positivo): ");
    if (scanf("%f", &novoProduto.preco) != 1 || novoProduto.preco <= 0) {
        printf("\nErro: Preço inválido!\n");
        while (getchar() != '\n');  // Limpa o buffer
        return;
    }
    while (getchar() != '\n');  // Limpa o buffer de entrada
    
    produtos[*totalProdutos] = novoProduto;
    (*totalProdutos)++;
    
    printf("\nProduto cadastrado com sucesso!\n\n");
}

// Função para listar todos os produtos
void listarProdutos(Produto produtos[], int totalProdutos) {
    if (totalProdutos == 0) {
        printf("\nNenhum produto cadastrado ainda.\n");
        return;
    }

    printf("\n==== Produtos Disponíveis ====\n");
    for (int i = 0; i < totalProdutos; i++) {
        exibirProduto(produtos[i]);
    }
    printf("==============================\n\n");
}

// Função para buscar um produto pelo código, retorna ponteiro ou NULL
Produto* pegarProdutoPorCodigo(Produto produtos[], int totalProdutos, int codigo) {
    for (int i = 0; i < totalProdutos; i++) {
        if (produtos[i].codigo == codigo) {
            return &produtos[i];
        }
    }
    return NULL;  // Retorna NULL se o produto não for encontrado
}

// Função para atualizar informações de um produto existente
void atualizarProduto(Produto produtos[], int totalProdutos) {
    int codigo;
    printf("Digite o código do produto que deseja atualizar: ");
    if (scanf("%d", &codigo) != 1) {
        printf("\nErro: Código inválido!\n");
        return;
    }
    while (getchar() != '\n');  // Limpa o buffer

    Produto *produto = pegarProdutoPorCodigo(produtos, totalProdutos, codigo);
    if (produto == NULL) {
        printf("\nProduto com código %d não encontrado.\n", codigo);
        return;
    }

    printf("Digite o novo nome: ");
    fgets(produto->nome, sizeof(produto->nome), stdin);
    produto->nome[strcspn(produto->nome, "\n")] = 0;

    printf("Digite o novo preço: ");
    if (scanf("%f", &produto->preco) != 1 || produto->preco <= 0) {
        printf("\nErro: Preço inválido!\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');  // Limpa o buffer
    
    printf("\nProduto atualizado com sucesso!\n");
}
