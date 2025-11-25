#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no* anterior;
    struct no* posterior;
} no;

no* head = NULL;
int nos = 0;

no* comeco(int dado);
void inserirInicio(int dado);
void inserirFinal(int dado);
void inserirPosicao(int dado, int posicao);
void removerPosicao(int posicao);
int buscar(int dado);
void listar();
void liberarLista();

int main() {
    int opcao, valor, posicao, resultado;

    do {
        printf("\n--- GERENCIADOR DE LISTA DUPLAMENTE ENCADEADA ---\n");
        printf("Total de nos: %d\n", nos);
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

void inserirInicio(int dado){
    no *novo = comeco(dado); 
    
    if(head != NULL){
        head->anterior = novo;
    }
    
    novo->posterior = head;
    head = novo; 
    nos++;
    printf("Inserido no inicio com sucesso.\n");
}

void inserirFinal(int dado){
    if(head == NULL){
        inserirInicio(dado);
        return;
    }

    no *novo = comeco(dado);
    no *temp = head;

    while(temp->posterior != NULL){
        temp = temp->posterior;
    }

    temp->posterior = novo;
    novo->anterior = temp;
    nos++;
    printf("Inserido no final com sucesso.\n");
}

void inserirPosicao(int dado, int posicao){
    
    if (posicao < 1 || posicao > nos + 1) {
        printf("Posicao invalida! A lista tem %d elementos.\n", nos);
        return;
    }

    if (posicao == 1) {
        inserirInicio(dado);
        return;
    }

    if (posicao == nos + 1) {
        inserirFinal(dado);
        return;
    }

    no *novo = comeco(dado);
    no *atual = head;

    for(int i = 1; i < posicao - 1; i++){
        atual = atual->posterior;
    }

    novo->posterior = atual->posterior;
    novo->anterior = atual;
    
    if (atual->posterior != NULL) {
        atual->posterior->anterior = novo;
    }
    atual->posterior = novo;
    
    nos++;
    printf("Inserido na posicao %d com sucesso.\n", posicao);
}

void removerPosicao(int posicao){
    if (head == NULL) {
        printf("Lista vazia.\n");
        return;
    }
    if (posicao < 1 || posicao > nos) {
        printf("Posicao invalida.\n");
        return;
    }

    no* temp = head;

    if (posicao == 1) {
        head = temp->posterior;
        if (head != NULL) {
            head->anterior = NULL;
        }
        free(temp);
        nos--;
        printf("Removido da posicao 1.\n");
        return;
    }

    for (int i = 1; i < posicao; i++) {
        temp = temp->posterior;
    }

    if (temp->posterior != NULL) {
        temp->posterior->anterior = temp->anterior;
    }
    if (temp->anterior != NULL) {
        temp->anterior->posterior = temp->posterior;
    }

    free(temp);
    nos--;
    printf("Removido da posicao %d.\n", posicao);
}

int buscar(int dado){
    no* temp = head;
    int pos = 1;

    while(temp != NULL){
        if(temp->dado == dado){
            return pos;
        }
        temp = temp->posterior;
        pos++;
    }
    return -1;
}

void listar(){
    if(head == NULL){
        printf("\nLista VAZIA.\n");
        return;
    }

    no* temp = head;
    printf("\nNULL <- ");
    while(temp != NULL){
        printf("[ %d ]", temp->dado);
        if(temp->posterior != NULL)
            printf(" <-> ");
        else
            printf(" -> NULL");
        
        temp = temp->posterior;
    }
    printf("\n");
}

void liberarLista(){
    no* atual = head;
    no* prox;

    while(atual != NULL){
        prox = atual->posterior;
        free(atual);
        atual = prox;
    }
    head = NULL;
    nos = 0;
}