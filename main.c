#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Definindo o limite de produtos
#define MAX_PRODUTOS 50

// Definindo os dados de um produto através de uma estrutura 
typedef struct { 
    char nome[30];
    char codigo [4];
    float preco; 
} Produto;

// Definindo os dados do Carrinho (Produtos e quantidade) através de uma estrutura 
typedef struct {
    Produto produto;
    int quantidade;
} Carrinho;

// Definindo os totais de produto cadastrados e no carrinho (por enquanto 0);
Produto produtos[MAX_PRODUTOS];
int total_produtos = 0;
Carrinho carrinho[MAX_PRODUTOS];
int total_carrinho = 0; 

// Definindo a função MENU para as escolhas do usuário 
int menu() {
    int opcao;
    
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar Produto\n");
    printf("2.Listar produtos \n");
    printf("3.Verificar se o produto ja se encontra no carrinho \n");
    printf("4.Verificar produto pelo seu codigo \n");
    printf("5.Comprar produto \n");
    printf("6.Visualizar Pedido \n");
    printf("7.Retirar produto do carrinho \n");
     printf("8.Fechar pedido\n");
    printf("9. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

// Função para cadastrar um produto

void CadastrarProdutos() {
    if (total_produtos < MAX_PRODUTOS) {
        Produto novo_produto;

        printf("Cadastro de Produto:\n");

        printf("Digite o nome do produto: ");
        scanf("%s", novo_produto.nome);

        printf("Digite o codigo do produto: ");
        scanf("%s", novo_produto.codigo);

        printf("Digite o preco do produto: ");
        scanf("%f", &novo_produto.preco);

        produtos[total_produtos++] = novo_produto;  // Adicionar o novo produto ao vetor
        printf("Produto cadastrado com sucesso!\n");
    } else {
        printf("Limite de produtos alcançado!\n");
    }
}

// Função para listar produtos

void ListarProdutos(){
    if(total_produtos == 0){
        printf("Nenhum produto cadastrado\n");
        return;
    }

    printf("Lista de produtos cadastrados: \n");
    for(int i = 0; i<total_produtos; i++){

        printf("Produto %d\n", i+1);
        printf("Nome: %s\n", produtos[i].nome);
        printf("Codigo: %s\n", produtos[i].codigo);
        printf("Preco: %f\n", produtos[i].preco);
    }}


// Funcao para verificar se o produto esta no carrinho 


int temNoCarrinho(char *codigo) {
    for (int i = 0; i < total_carrinho; i++) {
        if (strcmp(carrinho[i].produto.codigo, codigo) == 0) {
            printf("O produto '%s' ja esta no carrinho.\n", carrinho[i].produto.nome);
            return i; // Retorna o índice do produto no carrinho
        }
    }
    printf("O produto com codigo '%s' nao esta no carrinho.\n", codigo);
    return -1; // Retorna -1 se o produto não estiver no carrinho
}



// Função para pegar um produto pelo código
Produto* pegarProdutoPorCodigo(char *codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            printf("O codigo '%s' se refere ao produto '%s'.\n", codigo, produtos[i].nome);
            return &produtos[i]; 
        }
    }
    
    printf("Produto com codigo '%s' nao encontrado.\n", codigo);
    return NULL; 
}



// Funcao para comprar produtos

void ComprarProduto() {
    if (total_produtos == 0) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    char codigo[4];
    printf("Digite o codigo do produto que deseja comprar: ");
    scanf("%s", codigo);

    int produto_encontrado = 0;
    for (int i = 0; i < total_produtos; i++) {
        if (strcmp(produtos[i].codigo, codigo) == 0) {
            produto_encontrado = 1;

            printf("Produto encontrado: %s\n", produtos[i].nome);
            printf("Digite a quantidade que deseja comprar: ");
            int quantidade;
            scanf("%d", &quantidade);



    // Adicionando ao carrinho


            carrinho[total_carrinho].produto = produtos[i];
            carrinho[total_carrinho].quantidade = quantidade;
            total_carrinho++;

            printf("Produto adicionado ao carrinho!\n");
            break;
        }
    }

    if (!produto_encontrado) {
        printf("Produto com codigo %s não encontrado.\n", codigo);
    }
}




// Função para visualizar o carrinho


void VisualizarCarrinho() {
    if (total_carrinho == 0) {
        printf("O carrinho esta vazio.\n");
        return;
    }

    printf("\n--- Carrinho de Compras ---\n");
    for (int i = 0; i < total_carrinho; i++) {

        printf("Produto: %s\n", carrinho[i].produto.nome);
        printf("Quantidade: %d\n", carrinho[i].quantidade);
        printf("Preço unitario: %.2f\n", carrinho[i].produto.preco);
        printf("Preço total: %.2f\n", carrinho[i].quantidade * carrinho[i].produto.preco);
    }
}



// Função para retirar um produto do carrinho
void RetirarProdutoCarrinho() {
    if (total_carrinho == 0) {
        printf("O carrinho está vazio. Nao ha produtos para retirar.\n");
        return;
    }

    char codigo[4];
    printf("Digite o codigo do produto que deseja retirar: ");
    scanf("%s", codigo);




    // Procura o produto no carrinho
    for (int i = 0; i < total_carrinho; i++) {
        if (strcmp(carrinho[i].produto.codigo, codigo) == 0) {


            // Produto encontrado, removendo do carrinho
            printf("Produto '%s' removido do carrinho.\n", carrinho[i].produto.nome);

           
            for (int j = i; j < total_carrinho - 1; j++) {
                carrinho[j] = carrinho[j + 1];
            }
            total_carrinho--; 
            return; 
        }
    }

    printf("Produto com codigo '%s' nao encontrado no carrinho.\n", codigo);
}


// Função para fechar o pedido (calcular total, exibir fatura e limpar o carrinho)


void FecharPedido() {
    if (total_carrinho == 0) {
        printf("O carrinho esta vazio. Não e possivel fechar o pedido.\n");
        return;
    }

    float total = 0;
    printf("\n------ Fatura ------\n");
    for (int i = 0; i < total_carrinho; i++) {
        printf("Produto: %s\n", carrinho[i].produto.nome);
        printf("Quantidade: %d\n", carrinho[i].quantidade);
        printf("Preço unitario: %.2f\n", carrinho[i].produto.preco);
        float subtotal = carrinho[i].quantidade * carrinho[i].produto.preco;
        printf("Subtotal: %.2f\n", subtotal);
        total += subtotal;
    }
    printf("\nValor total da compra: %.2f\n", total);
    printf("Obrigado pela compra!\n");
    printf("----------------------");

    // Limpar o carrinho
    total_carrinho = 0;
}


int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcao;
    
    do {
        opcao = menu();
        switch (opcao) {
            case 1:
                CadastrarProdutos();
                break;

            case 2:
                ListarProdutos();
                break;

            case 3: {
                char codigo[4];
                printf("Digite o codigo do produto para verificar se está no carrinho: ");
                scanf("%s", codigo);
                temNoCarrinho(codigo);
                break;
            }

            case 4: {
                char codigo[4];
                printf("Digite o codigo do produto que deseja pegar: ");
                scanf("%s", codigo);
                Produto* produtoEncontrado = pegarProdutoPorCodigo(codigo);
                break;
}

            case 5:
                ComprarProduto();
                break;

            case 6:
                VisualizarCarrinho();
                break;
            
            case 7:
                RetirarProdutoCarrinho();
                break;

            case 8:
              FecharPedido();
                break;

            case 9:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 9);

    return 0;
}
