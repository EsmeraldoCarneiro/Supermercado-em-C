#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUTOS 100

typedef struct {
    char nome[50];
    float preco;
} Produto;

typedef struct {
    Produto produto;
    int quantidade;
} ItemVenda;

typedef struct {
    ItemVenda itensVenda[MAX_PRODUTOS];
    int totalItens;
} Carrinho;

void adicionarItem(Carrinho *carrinho, Produto *produto, int quantidade) {
    strcpy(carrinho->itensVenda[carrinho->totalItens].produto.nome, produto->nome);
    carrinho->itensVenda[carrinho->totalItens].produto.preco = produto->preco;
    carrinho->itensVenda[carrinho->totalItens].quantidade = quantidade;
    carrinho->totalItens++;
}

void mostrarCarrinho(Carrinho carrinho) {
    printf("----- Carrinho -----\n");
    float totalVenda = 0.0;

    // Percorre o carrinho e agrupa itens iguais
    for (int i = 0; i < carrinho.totalItens; i++) {
        ItemVenda item = carrinho.itensVenda[i];
        int quantidadeTotal = item.quantidade;

        // Verifica se há mais itens iguais e soma suas quantidades
        for (int j = i + 1; j < carrinho.totalItens; j++) {
            if (strcmp(item.produto.nome, carrinho.itensVenda[j].produto.nome) == 0) {
                quantidadeTotal += carrinho.itensVenda[j].quantidade;
                // Define a quantidade do item atual para 0 para não ser contabilizado novamente
                carrinho.itensVenda[j].quantidade = 0;
            }
        }

        if (quantidadeTotal > 0) {
            float subtotal = item.produto.preco * quantidadeTotal;
            printf("%s - R$ %.2f x %d = R$ %.2f\n", item.produto.nome, item.produto.preco, quantidadeTotal, subtotal);
            totalVenda += subtotal;
        }
    }

    if (totalVenda > 100.0) {
        float desconto = totalVenda * 0.1;
        totalVenda -= desconto;
        printf("Desconto aplicado (10%%): R$ %.2f\n", desconto);
    }

    printf("Total: R$ %.2f\n", totalVenda);
    printf("--------------------\n");
}

int main() {
    Carrinho carrinho;
    carrinho.totalItens = 0;

    Produto produtos[MAX_PRODUTOS];
    int totalProdutos = 0;

    // Exemplo de cadastro de produtos
    Produto p1 = { "Arroz", 10.0 };
    produtos[totalProdutos++] = p1;

    Produto p2 = { "Feijão", 5.0 };
    produtos[totalProdutos++] = p2;

    Produto p3 = { "Macarrão", 3.5 };
    produtos[totalProdutos++] = p3;

    int opcao;
    do {
        printf("----- Menu -----\n");
        printf("1 - Registrar venda\n");
        printf("2 - Mostrar carrinho\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int codigoProduto, quantidade;

                printf("Digite o código do produto: ");
                scanf("%d", &codigoProduto);

                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);

                if (codigoProduto >= 0 && codigoProduto < totalProdutos) {
                    Produto produtoSelecionado = produtos[codigoProduto];
                    adicionarItem(&carrinho, &produtoSelecionado, quantidade);
                    printf("Produto adicionado ao carrinho!\n");
                } else {
                    printf("Código de produto inválido!\n");
                }

                break;
            }
            case 2: {
                mostrarCarrinho(carrinho);
                break;
            }
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

    } while (opcao != 0);

    return 0;
}
