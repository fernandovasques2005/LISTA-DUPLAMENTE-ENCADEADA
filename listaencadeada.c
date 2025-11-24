#include <stdio.h>
#include <stdlib.h>

/*
typedef -> cria um apelido
struct -> cria uma estrutura
estrutura_no_rotulo -> o rótulo dessa estrutura enquanto o apelido estrutura_no ainda não foi criado
estrutura_no -> o apelido dessa estrutura
*/
typedef struct no{
    int dado;
    struct no* anterior;
    struct no* posterior;
} no;


//Protótipos das Funções
no* comeco(int dado);
void inserirInicio(no** head, int dado);
void inserirFinal(no** head, int dado);
void inserirPosicao(no** head, int dado, int posicao);
void removerPosicao(no** head, int posicao);
int buscar(no* head, int dado);
void listar(no* head);
void liberarLista(no** head);

//Função principal onde vai rodar o que o usuario enxerga
int main() {
    no* lista = NULL; // Inicializa a lista vazia
    int opcao, valor, posicao, resultado;

    do {
        printf("\n--- GERENCIADOR DE LISTA DUPLAMENTE ENCADEADA ---\n");
        printf("1. Inserir no Inicio\n");
        printf("2. Inserir no Final\n");
        printf("3. Inserir em Posicao Especifica\n");
        printf("4. Remover de Posicao Especifica\n");
        printf("5. Buscar Valor\n");
        printf("6. Listar Elementos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserirInicio(&lista, valor);
                break;
            case 2:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserirFinal(&lista, valor);
                break;
            case 3:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                printf("Digite a posicao (inicia em 1): ");
                scanf("%d", &posicao);
                inserirPosicao(&lista, valor, posicao);
                break;
            case 4:
                printf("Digite a posicao para remover (inicia em 1): ");
                scanf("%d", &posicao);
                removerPosicao(&lista, posicao);
                break;
            case 5:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                resultado = buscar(lista, valor);
                if (resultado != -1)
                    printf("Valor encontrado na posicao: %d\n", resultado);
                else
                    printf("Valor nao encontrado na lista.\n");
                break;
            case 6:
                listar(lista);
                break;
            case 0:
                printf("Saindo e liberando memoria...\n");
                liberarLista(&lista);
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

//criação do no e se há espaço na memória
no* comecoCriar(int dado){
    no* novoNo = (no *)malloc(sizeof(no));
    if (novoNo == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->anterior = NULL;
    novoNo->posterior = NULL;
    return novoNo;
}
