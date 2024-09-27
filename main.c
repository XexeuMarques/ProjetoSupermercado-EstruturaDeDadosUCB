#include <stdio.h>
#include <stdlib.h>  // Necessário para system()
#include "produto.h"
#include "carrinho.h"

// Função para limpar a tela do terminal, compatível com Windows e Linux
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux/Unix
    #endif
}

// Função para pausar a execução e esperar o usuário apertar uma tecla
void esperarTecla() {
    printf("\nAperte Enter tecla para continuar...");
    getchar();  // Aguarda a entrada do usuário
    fflush(stdin); // Limpa buffer do teclado
}

// Função para exibir o menu principal
void exibirMenu() {
    limparTela();  // Limpa a tela ao voltar para o menu principal
    printf("\n====== Loja Virtual ======\n");
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Comprar Produto\n");
    printf("4. Visualizar Carrinho\n");
    printf("5. Remover Item do Carrinho\n");
    printf("6. Fechar Pedido\n");
    printf("7. Atualizar Produto\n");
    printf("8. Sair\n");
    printf("==========================\n");
}

// Função principal para gerenciar o sistema
void menu() {
    Produto produtos[MAX_PRODUTOS];  // Array para armazenar os produtos
    Carrinho carrinho[MAX_CARRINHO];  // Array para armazenar os itens no carrinho
    int totalProdutos = 0;  // Contador de produtos cadastrados
    int totalItensCarrinho = 0;  // Contador de itens no carrinho
    int opcao;  // Variável para armazenar a escolha do usuário

    printf("=== Bem-vindo à Loja Virtual! ===\n");
    esperarTecla();  // Espera para iniciar o sistema

    do {
        exibirMenu();  // Exibe o menu principal

        // Recebe a escolha do usuário
        printf("Escolha uma opção: ");
        if (scanf("%d", &opcao) != 1) {
            printf("\nErro: Entrada inválida!\n");
            while (getchar() != '\n');  // Limpa o buffer de entrada
            esperarTecla();  // Espera antes de voltar ao menu
            continue;
        }

        while (getchar() != '\n');  // Limpa o buffer de entrada

        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &totalProdutos);  // Função para cadastrar um novo produto
                break;
            case 2:
                listarProdutos(produtos, totalProdutos);  // Função para listar todos os produtos
                break;
            case 3: {
                int codigo;
                printf("Digite o código do produto que deseja comprar: ");
                if (scanf("%d", &codigo) != 1) {
                    printf("\nErro: Código inválido!\n");
                    while (getchar() != '\n');  // Limpa o buffer
                    esperarTecla();
                    break;
                }
                Produto *produto = pegarProdutoPorCodigo(produtos, totalProdutos, codigo);
                if (produto != NULL) {
                    adicionarAoCarrinho(carrinho, &totalItensCarrinho, *produto);  // Adiciona produto ao carrinho
                } else {
                    printf("\nProduto não encontrado.\n");
                }
                break;
            }
            case 4:
                visualizarCarrinho(carrinho, totalItensCarrinho);  // Exibe o carrinho de compras
                break;
            case 5:
                removerDoCarrinho(carrinho, &totalItensCarrinho);  // Remove itens do carrinho
                break;
            case 6:
                fecharPedido(carrinho, &totalItensCarrinho);  // Finaliza o pedido e calcula o total
                break;
            case 7:
                atualizarProduto(produtos, totalProdutos);  // Atualiza dados de um produto cadastrado
                break;
            case 8:
                printf("\nEncerrando o sistema... Até logo!\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                break;
        }
        esperarTecla();  // Pausa a execução antes de limpar a tela e voltar ao menu
    } while (opcao != 8);
}

int main() {
    menu();  // Chama o menu principal
    return 0;
}
