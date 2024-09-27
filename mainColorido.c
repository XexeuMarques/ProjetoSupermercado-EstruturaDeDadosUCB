#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32 
    #include <windows.h>  // Necessário para SetConsoleTextAttribute se for copilado no windows
#else
   // #include <unistd.h>  //-> Não vou usar mais o usleep()
#endif
#include "produto.h"
#include "carrinho.h"

// Definindo as cores
#define COR_VERMELHO 1
#define COR_VERDE 2
#define COR_AMARELO 3
#define COR_AZUL 4
#define COR_BRANCO 5

// Protótipos das funções
void setCorTexto(int);
void resetCorTexto();
void limparTela();
void esperarTecla();
void exibirMenu();
void menu();

// Função main
int main() {
    menu();  // Chama o menu principal
    return 0;
}

// Função para limpar a tela do terminal, Caso for windows vai manda cls ao invez do clear no terminal
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Comando para Windows
    #else
        system("clear");  // Comando para Linux/Unix
    #endif
}

// Função para pausar a execução e esperar o usuário apertar uma tecla
void esperarTecla() {
    printf("\nPressione ENTER para continuar...");
    getchar();  // Aguarda a entrada do usuário
    fflush(stdin); // Limpa buffer do teclado
}

// Função para exibir o menu principal
void exibirMenu() {
    limparTela();  // Limpa a tela ao voltar para o menu principal

    setCorTexto(COR_AZUL);
    printf("\n====== Loja Virtual ======\n");
    resetCorTexto();

    setCorTexto(COR_VERDE);
    printf("1. Cadastrar Produto\n");
    printf("2. Listar Produtos\n");
    printf("3. Comprar Produto\n");
    printf("4. Visualizar Carrinho\n");
    printf("5. Remover Item do Carrinho\n");
    printf("6. Fechar Pedido\n");
    printf("7. Atualizar Produto\n");
    printf("8. Sair\n");
    resetCorTexto();

    setCorTexto(COR_AZUL);
    printf("==========================\n");
    resetCorTexto();
}

// Função para mudar a cor do texto
// Caso estiver no windows vai chamar a API do Windows (SetConsoleTextAttribute) --> #include <windows.h>
void setCorTexto(int cor) {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (cor) {
            case COR_VERMELHO:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
                break;
            case COR_VERDE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case COR_AMARELO:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                break;
            case COR_AZUL:
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
                break;
            case COR_BRANCO:
            default:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                break;
        }
    #else // ja no Linux usar sequências de escape ANSI, ja que e o ambiente que estou desenvolvendo
        switch (cor) {
            case COR_VERMELHO:
                printf("\033[1;31m");
                break;
            case COR_VERDE:
                printf("\033[1;32m");
                break;
            case COR_AMARELO:
                printf("\033[1;33m");  
                break;
            case COR_AZUL:
                printf("\033[1;34m");  
                break;
            case COR_BRANCO:
            default:
                printf("\033[0m"); 
                break;
        }
    #endif
}

// Função para resetar a cor do texto de volta para a cor padrão
void resetCorTexto() {
    #ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    #else
        printf("\033[0m");  // Reset para cor padrão no Linux
    #endif
}

// Função principal para gerenciar as chamadas do sistema
void menu() {
    Produto produtos[MAX_PRODUTOS];  // Array para armazenar os produtos
    Carrinho carrinho[MAX_CARRINHO];  // Array para armazenar os itens no carrinho
    int totalProdutos = 0;  // Contador de produtos cadastrados
    int totalItensCarrinho = 0;  // Contador de itens no carrinho
    int opcao;  // Variável para armazenar a escolha do usuário

    setCorTexto(COR_AZUL);
    printf("=== Bem-vindo à Loja Virtual! ===\n");
    resetCorTexto();
    esperarTecla(); 

    do {
        exibirMenu();  // Obviamente exibe o menu (Acho que ja estou comentando d+)

        // Recebe a escolha do usuário
        setCorTexto(COR_AMARELO);
        printf("Escolha uma opção: ");
        resetCorTexto();
        if (scanf("%d", &opcao) != 1) {
            setCorTexto(COR_VERMELHO);
            printf("\nErro: Entrada inválida!\n");
            resetCorTexto();
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
                listarProdutos(produtos, totalProdutos);  // Função para listar todos os produtos, ambos la do "produto.c"
                break;
            case 3: {
                int codigo;
                printf("Digite o código do produto que deseja comprar: ");
                if (scanf("%d", &codigo) != 1) {
                    setCorTexto(COR_VERMELHO);
                    printf("\nErro: Código inválido!\n");
                    resetCorTexto();
                    while (getchar() != '\n');  // Limpa o buffer
                    esperarTecla();
                    break;
                }
                Produto *produto = pegarProdutoPorCodigo(produtos, totalProdutos, codigo);
                if (produto != NULL) {
                    adicionarAoCarrinho(carrinho, &totalItensCarrinho, *produto);  // Adiciona produto ao carrinho
                } else {
                    setCorTexto(COR_VERMELHO);
                    printf("\nProduto não encontrado.\n");
                    resetCorTexto();
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
                setCorTexto(COR_AZUL);
                printf("\nEncerrando o sistema... Até mais prof.!\n");
                resetCorTexto();
                break;
            default:
                setCorTexto(COR_VERMELHO);
                printf("\nOpção inválida. Tente novamente.\n");
                resetCorTexto();
                break;
        }
        esperarTecla();  // Pausa a execução antes de limpar a tela e voltar ao menu
    } while (opcao != 8);
}

