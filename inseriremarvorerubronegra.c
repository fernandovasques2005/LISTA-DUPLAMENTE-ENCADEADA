#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
    int cor;
    struct no *anterior;
    struct no *menor;
    struct no *maior;
}no;

int nos = 0;

no* começo(){
    no *primeiro = malloc(sizeof(no));
    if(primeiro == NULL){
        printf("Erro, memória insuficiente\n");
    }
    printf("Insira o valor desejado no primeiro nó da árvore\n");
    scanf("%d", &primeiro->dado);
    primeiro->cor = 0;
    primeiro->anterior = NULL;
    primeiro->menor = NULL;
    primeiro->maior = NULL;
    nos++;
    return primeiro;
}

void rotaçãodireita(no* primeiro, no* novo, no* pai, no* avo, no* tio){
    int mudança;
    if(primeiro == avo){
        mudança = 1;
    }
    pai->anterior = avo->anterior;
    avo->anterior = pai;
    avo->menor = pai->maior;
    pai->maior = avo;
    if(pai->cor == 1 && avo->cor == 0){
        pai->cor = 0;
        avo->cor = 1;
    }
    else if(pai->cor == 0 && avo->cor == 1){
        pai->cor = 1;
        avo->cor = 0;
    }
    if(mudança == 1){
        primeiro->dado = pai->dado;
        primeiro->cor = pai->cor;
        primeiro = pai;
    }
    return;
}

void rotaçãoesquerda(no* primeiro, no* novo, no* pai, no* avo, no* tio){
    int mudança;
    if(primeiro == avo){
        mudança = 1;
    }
    pai->anterior = avo->anterior;
    avo->anterior = pai;
    avo->maior = pai->menor;
    pai->menor = avo;
    if(pai->cor == 1 && avo->cor == 0){
        pai->cor = 0;
        avo->cor = 1;
    }
    else if(pai->cor == 0 && avo->cor == 1){
        pai->cor = 1;
        avo->cor = 0;
    }
    if(mudança == 1){
        primeiro->dado = pai->dado;
        primeiro->cor = pai->cor;
        primeiro = pai;
    }
}

void balancear(no* primeiro, no* novo){
    if(novo == primeiro || novo->anterior == NULL || novo->anterior->cor == 0 || novo->anterior == primeiro){
        return;
    }
    no *pai = novo->anterior, *avo = novo->anterior->anterior, *tio;
    if(avo->maior == pai){
        tio = avo->menor;
    }
    else{
        tio = avo->maior;
    }
    if(tio == NULL || tio->cor == 0){
        if(avo->menor == pai && pai->menor == novo){
            rotaçãodireita(primeiro, novo, pai, avo, tio);
            balancear(primeiro, pai);
        }
        else if(avo->menor == pai && pai->maior == novo){
            avo->menor = novo;
            novo->anterior = avo;
            pai->maior = novo->menor;
            novo->menor = pai;
            pai->anterior = novo;
            rotaçãodireita(primeiro, pai, novo, avo, tio);
            balancear(primeiro, pai);
        }
        else if(avo->maior == pai && pai->maior == novo){
            rotaçãoesquerda(primeiro, novo, pai, avo, tio);
            balancear(primeiro, pai);
        }
        else if(avo->maior == pai && pai->menor == novo){
            avo->maior = novo;
            novo->anterior = avo;
            pai->menor = novo->maior;
            novo->maior = pai;
            pai->anterior = novo;
            rotaçãoesquerda(primeiro, pai, novo, avo, tio);
            balancear(primeiro, pai);
        }
    }
    else{
        pai->cor = 0;
        tio->cor = 0;
        balancear(primeiro, avo);
    }
}

no* inserir(no* primeiro){
    no *current, *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Erro, memória insuficiente\n");
        return primeiro;
    }
    printf("Insira o valor do novo nó. Caso nós tenham valores iguais, o nó novo é tratado como menor.\n");
    scanf("%d", &novo->dado);
    novo->cor = 1;
    current = primeiro;
    for(int i = 0; i < nos*2; i++){
        if(novo->dado > current->dado){
            printf("%d A %d\n", current->dado, current->cor);
            if(current->maior == NULL){
                current->maior = novo;
                novo->anterior = current;
                novo->maior = NULL;
                novo->menor = NULL;
                printf("Nó criado com sucesso\n");
                nos++;
                break;
            }
            else{
                current = current->maior;
            }
        }
        else{
            printf("%d B %d\n", current->dado, current->cor);
            if(current->menor == NULL){
                current->menor = novo;
                novo->anterior = current;
                novo->maior = NULL;
                novo->menor = NULL;
                printf("Nó criado com sucesso\n");
                nos++;
                break;
            }
            else{
                current = current->menor;
            }
        }
    }
    balancear(primeiro, novo);
    return primeiro;
}

void telas(no* primeiro){
    int escolha;
    printf("1.Inserção\n2.Remover\n3.Buscar\n4.Listar\n");
    scanf("%d", &escolha);
    switch(escolha){
        case 1:
        inserir(primeiro);
        break;
        case 2:
        break;
        case 3:
        break;
        case 4:
        break;
        default:
        printf("Por favor, insira um valor apropriado\n");
    }
}

int main(){
    no* primeiro = começo();
    do{
        telas(primeiro);
    }while(1);
    return 0;
}