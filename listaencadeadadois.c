#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
    struct no *anterior;
    struct no *posterior;
}no;

int nos = 0;

no* começo(){
    no *head = malloc(sizeof(no));
    head->dado = 0;
    head->anterior = NULL;
    head->posterior = NULL;
    nos++;
    return head;
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

int inserirnofinal(){}

void inserir(no* head){
    int escolha;
    printf("1.Inserir no início\n2.Inserir em uma posição específica (O head é igual a 1)\n3.Inserir no final\n");
    scanf("%d", &escolha);
    switch(escolha){
    case '1':
    inserirnoinicio(head);
    break;
    case '2':
    inserirespecifico(head);
    break;
    case '3':
    inserirnofinal(head);
    break;
    default:
    printf("Por favor, insira um valor apropriado\n");
    }
}

void telas(no* head){
    int escolha;
    printf("1.Inserir\n2.Remover\n3.Buscar\n4.Listar");
    scanf("%d", &escolha);
    switch(escolha){
        case '1':
        inserir(head);
        break;
        case '2':
        remover(head);
        break;
        case '3':
        buscar(head);
        break;
        case '4':
        listar(head);
        break;
        default:
        printf("Por favor, insira um valor apropriado\n");
    }
}

int main(){
    no* head = começo();
    do{
        telas(head);
    }while(1);
    return 0;
}