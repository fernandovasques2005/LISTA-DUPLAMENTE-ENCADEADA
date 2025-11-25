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

no* head = NULL;
int nos = 0;

//Protótipos das Funções
no* comeco(int dado);
void inserirInicio(int dado);
void inserirFinal(int dado);
void inserirPosicao(int dado, int posicao);
void removerPosicao(int posicao);
int buscar(int dado);
void listar();
void liberarLista();

int main() {

    int opcao, valor, posicao, resultado, dado;

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
                inserirInicio(valor);
                break;
            case 2:
                printf("Digite o valor: ");
                scanf("%d", &valor);
                inserirFinal(valor);
                break;
            case 3:
                printf("Digite o valor: ");
                scanf("%d", &valor);

                printf("Digite a posicao (inicia em 1): ");
                scanf("%d", &posicao);
                inserirPosicao(valor, posicao);
                break;
            case 4:
                printf("Digite a posicao para remover (inicia em 1): ");
                scanf("%d", &posicao);
                removerPosicao(posicao);
                break;
            case 5:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                resultado = buscar(valor);
                if (resultado != -1)
                    printf("Valor encontrado na posicao: %d\n", resultado);
                else
                    printf("Valor nao encontrado na lista.\n");
                break;
            case 6:
                listar();
                break;
            case 0:
                printf("Saindo e liberando memoria...\n");
                liberarLista();
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

no* comeco(int dado){
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

no* inserirnoinicio(no* head){
    no *novo = malloc(sizeof(no));
    novo->dado = 0;
    novo->anterior = NULL;
    novo->posterior = head;
    head->anterior = novo;
    head = novo;
    printf("Insira o valor do novo nó\n");
    scanf("%d", novo->dado);
    nos++;
    return head;
}

void inserirespecifico(no* head){
    int posição;
    no *current;
    no *novo = (no *)malloc(sizeof(no));
    printf("Insira o valor desejado para o nó\n");
    scanf("%d", novo->dado);
    printf("Insira a posição desejada para o nó, considerando que a primeira posição possui o valor de 1\n");
    scanf("%d", &posição);
    if(posição > nos+1){
        printf("Não há nós suficientes na lista para existir essa posição\n");
    }
    else if(posição == 1){
        inserirnoinicio(head);
    }
    else if(posição == 2){
        current = head;
        if(head->posterior = NULL){
            head->posterior = novo;
            novo->anterior = head;
            novo->posterior = NULL;
        }
        else{
            current = head->posterior;
            head->posterior = novo;
            current->anterior = novo;
            novo->anterior = head;
            novo->posterior = current;
        }
    }
    else{
        current = head;
        for(int i = 0; i < posição-1; i++){
            current = current->posterior;
        }
        if(current->posterior = NULL){
            current->posterior = novo;
            novo->anterior = current;
            novo->posterior = NULL;
        }
        else{
            novo->posterior = current->posterior;
            novo->anterior = current;
            current->posterior = novo;
        }
    }
}

int inserirnofinal(no* head){
    no *novo = (no *)malloc(sizeof(no));
    novo->dado = 0;
    novo->posterior = NULL;
    novo->anterior = head;
    head->anterior = novo;
    head = novo;
    printf("Insira o valor do novo nó\n");
    scanf("%d", novo->dado);
    nos++;
    return head;
}

int buscar(int dado){
    no* temp = head;
}
void listar(){

}
void liberarLista(){

}
