#include <stdio.h>
#include "produto.h"
#include "carrinho.h"

// Função para mostrar o menu
void exibirMenu() {
    printf("\n==== Menu Principal ====\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Comprar Produto\n");
    printf("4. Visualizar Carrinho\n");
    printf("5. Remover Item do Carrinho\n");
    printf("6. Fechar Pedido\n");
    printf("7. Atualizar Produto\n");
    printf("8. Sair\n");
    printf("========================\n");
}

// Função principal para gerenciar o sistema
void menu() {
    Produto produtos[MAX_PRODUTOS];
    Carrinho carrinho[MAX_CARRINHO];
    int totalProdutos = 0;
    int totalItensCarrinho = 0;
    int opcao;

    printf("=== Bem-vindo ao Sistema de Loja Virtual ===\n");

    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nErro: Entrada inválida!\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');  // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &totalProdutos);
                break;
            case 2:
                listarProdutos(produtos, totalProdutos);
                break;
            case 3: {
                int codigo;
                printf("Digite o código do produto que deseja comprar: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Código inválido!\n");
                    while (getchar() != '\n');
                    break;
                }
                Produto *produto = pegarProdutoPorCodigo(produtos, totalProdutos, codigo);
                if (produto != NULL) {
                    adicionarAoCarrinho(carrinho, &totalItensCarrinho, *produto);
                } else {
                    printf("\nProduto não encontrado.\n");
                }
                break;
            }
            case 4:
                visualizarCarrinho(carrinho, totalItensCarrinho);
                break;
            case 5:
                removerDoCarrinho(carrinho, &totalItensCarrinho);
                break;
            case 6:
                fecharPedido(carrinho, &totalItensCarrinho);
                break;
            case 7:
                atualizarProduto(produtos, totalProdutos);
                break;
            case 8:
                printf("\nEncerrando o sistema... Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 8);
}

int main() {
    menu();
    return 0;
}
