#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
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
    primeiro->anterior = NULL;
    primeiro->menor = NULL;
    primeiro->maior = NULL;
    nos++;
    return primeiro;
}

no* inserir(no* primeiro){
    no *current, *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Erro, memória insuficiente\n");
        return primeiro;
    }
    printf("Insira o valor do novo nó. Caso nós tenham valores iguais, o nó novo é tratado como menor.\n");
    scanf("%d", &novo->dado);
    current = primeiro;
    for(int i = 0; i < nos*2; i++){
        if(novo->dado > current->dado){
            printf("%d A\n", current->dado);
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
            printf("%d B\n", current->dado);
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