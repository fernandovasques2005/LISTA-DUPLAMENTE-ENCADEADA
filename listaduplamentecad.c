#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int dado;
    struct Node *esquerda;
    struct Node *direita;
} Node;

Node* criarNo(int dado);
Node* inserir(Node* raiz, int dado);
Node* remover(Node* raiz, int dado);
Node* buscarMinimo(Node* no);
int buscar(Node* raiz, int dado);
void preOrdem(Node* raiz);
void emOrdem(Node* raiz);
void posOrdem(Node* raiz);
void liberarArvore(Node* raiz);
void submenuPercursos(Node* raiz);

int main() {
    Node* raiz = NULL;
    int opcao, valor, resultado;

    do {
        printf("\n--- MENU ARVORE BINARIA DE BUSCA ---\n");
        printf("1 - Inserir valor\n");
        printf("2 - Buscar valor\n");
        printf("3 - Remover valor\n");
        printf("4 - Percorrer arvore (Submenu)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Valor inserido (se nao for duplicado).\n");
                break;

            case 2:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                resultado = buscar(raiz, valor);
                if (resultado)
                    printf("O valor %d ESTA na arvore.\n", valor);
                else
                    printf("O valor %d NAO esta na arvore.\n", valor);
                break;

            case 3:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                break;

            case 4:
                submenuPercursos(raiz);
                break;

            case 0:
                printf("Liberando memoria e saindo...\n");
                liberarArvore(raiz);
                raiz = NULL;
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}
