#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado1, dado2, folha;
    struct no *anterior;
    struct no *menor;
    struct no *meio;
    struct no *maior;
}no;

int nos = 0;

no* começo(){
    no *primeiro = malloc(sizeof(no));
    if(primeiro == NULL){
        printf("Erro, memória insuficiente\n");
    }
    printf("Insira o valor do primero nó\n");
    scanf("%d", &primeiro->dado1);
    primeiro->folha = 1;
    primeiro->dado2 = 0;
    primeiro->anterior = NULL;
    primeiro->menor = NULL;
    primeiro->meio = NULL;
    primeiro->maior = NULL;
    nos++;
    return primeiro;
}

void organizar(no* current){
    if(current->dado1 > current->dado2){
        int c = current->dado1;
        current->dado1 = current->dado2;
        current->dado2 = c;
    }
}

void caso1(no*current, int valornovo){
    if(valornovo <= current->dado1){
        current->folha = 0;
        no* novo = malloc(sizeof(no));
        no* novo2 = malloc(sizeof(no));
        novo->anterior = current;
        novo->folha = 1;
        novo->dado1 = valornovo;
        novo->dado2 = 0;
        novo->menor = NULL;
        novo->meio = NULL;
        novo->maior = NULL;
        novo2->anterior = current;
        novo2->folha = 1;
        novo2->dado1 = current->dado2;
        novo2->dado2 = 0;
        novo2->menor = NULL;
        novo2->meio = NULL;
        novo2->maior = NULL;
        current->menor = novo;
        current->maior = novo2;
        current->dado2 = 0;
    }
    else if(valornovo > current->dado1 && valornovo < current->dado2){
        current->folha = 0;
        no* novo = malloc(sizeof(no));
        no* novo2 = malloc(sizeof(no));
        novo->anterior = current;
        novo->folha = 1;
        novo->dado1 = current->dado1;
        novo->dado2 = 0;
        novo->menor = NULL;
        novo->meio = NULL;
        novo->maior = NULL;
        novo2->anterior = current;
        novo2->folha = 1;
        novo2->dado1 = current->dado2;
        novo2->dado2 = 0;
        novo2->menor = NULL;
        novo2->meio = NULL;
        novo2->maior = NULL;
        current->dado1 = valornovo;
        current->menor = novo;
        current->maior = novo2;
        current->dado2 = 0;
    }
    else if(valornovo > current->dado2){
        current->folha = 0;
        no* novo = malloc(sizeof(no));
        no* novo2 = malloc(sizeof(no));
        novo->anterior = current;
        novo->folha = 1;
        novo->dado1 = current->dado1;
        novo->dado2 = 0;
        novo->menor = NULL;
        novo->meio = NULL;
        novo->maior = NULL;
        novo2->anterior = current;
        novo2->folha = 1;
        novo2->dado1 = valornovo;
        novo2->dado2 = 0;
        novo2->menor = NULL;
        novo2->meio = NULL;
        novo2->maior = NULL;
        current->dado1 = current->dado2;
        current->menor = novo;
        current->maior = novo2;
        current->dado2 = 0;
    }
}

void caso2(no* current, no* pai, int valornovo){
    if(current = pai->menor){
        if(valornovo <= current->dado1){
            pai->dado2 = current->dado1;
            current->dado1 = valornovo;
            no* novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = current->dado2;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado2 = 0;
        }
        else if(valornovo > current->dado1 && valornovo < current->dado2){
            pai->dado2 = valornovo;
            no* novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = current->dado2;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado2 = 0;
        }
        else if(valornovo > current->dado2){
            pai->dado2 = current->dado2;
            no* novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = valornovo;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado2 = 0;
        }
    }
    else if(current = pai->maior){
        if(valornovo <= current->dado1){
            pai->dado2 = current->dado1;
            no*novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = valornovo;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado1 = current->dado2;
            current->dado2 = 0;
        }
        else if(valornovo > current->dado1 && valornovo < current->dado2){
            pai->dado2 = valornovo;
            no*novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = current->dado1;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado1 = current->dado2;
            current->dado2 = 0;
        }
        else if(valornovo > current->dado2){
            pai->dado2 = current->dado2;
            no*novo = malloc(sizeof(no));
            novo->anterior = pai;
            novo->folha = 1;
            novo->dado1 = current->dado1;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->meio = novo;
            current->dado1 = valornovo;
            current->dado2 = 0;
        }
    }
}

void caso3(no* current, no* pai, int valornovo){
    if(current = pai->menor){
        if(valornovo < current->dado1){
            current->folha = 0;
            pai->maior->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = current;
            novo->folha = 1;
            novo->dado1 = valornovo;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            current->menor = novo;
            novo2->anterior = current;
            novo2->folha = 1;
            novo2->dado1 = current->dado2;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            current->maior = novo2;
            novo3->anterior = pai->maior;
            novo3->folha = 1;
            novo3->dado1 = pai->meio->dado1;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            pai->maior->menor = novo3;
            novo4->anterior = pai->maior;
            novo4->folha = 1;
            novo4->dado1 = pai->maior->dado1;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            pai->maior->maior = novo4;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
        else if(valornovo > current->dado1 && valornovo < current->dado2){
            current->folha = 0;
            pai->maior->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = current;
            novo->folha = 1;
            novo->dado1 = current->dado1;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            current->menor = novo;
            novo2->anterior = current;
            novo2->folha = 1;
            novo2->dado1 = current->dado2;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            current->maior = novo2;
            novo3->anterior = pai->maior;
            novo3->folha = 1;
            novo3->dado1 = pai->meio->dado1;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            pai->maior->menor = novo3;
            novo4->anterior = pai->maior;
            novo4->folha = 1;
            novo4->dado1 = pai->maior->dado1;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            pai->maior->maior = novo4;
            current->dado1 = valornovo;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
        else if(valornovo > current->dado2){
            current->folha = 0;
            pai->maior->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = current;
            novo->folha = 1;
            novo->dado1 = current->dado1;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            current->menor = novo;
            novo2->anterior = current;
            novo2->folha = 1;
            novo2->dado1 = valornovo;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            current->maior = novo2;
            novo3->anterior = pai->maior;
            novo3->folha = 1;
            novo3->dado1 = pai->meio->dado1;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            pai->maior->menor = novo3;
            novo4->anterior = pai->maior;
            novo4->folha = 1;
            novo4->dado1 = pai->maior->dado1;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            pai->maior->maior = novo4;
            current->dado1 = current->dado2;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
    }
    else if(current = pai->maior){
        if(valornovo <= current->dado1){
            current->folha = 0;
            pai->menor->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = pai->menor;
            novo->folha = 1;
            novo->dado1 = pai->menor->dado1;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->menor->menor = novo;
            novo2->anterior = pai->menor;
            novo2->folha = 1;
            novo2->dado1 = pai->menor->dado2;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            pai->menor->maior = novo2;
            novo3->anterior = current;
            novo3->folha = 1;
            novo3->dado1 = valornovo;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            current->menor = novo3;
            novo4->anterior = current;
            novo4->folha = 1;
            novo4->dado1 = current->dado2;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            current->maior = novo4;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
        else if(valornovo > current->dado1 && valornovo < current->dado2){
            current->folha = 0;
            pai->menor->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = pai->menor;
            novo->folha = 1;
            novo->dado1 = pai->menor->dado1;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->menor->menor = novo;
            novo2->anterior = pai->menor;
            novo2->folha = 1;
            novo2->dado1 = pai->menor->dado2;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            pai->menor->maior = novo2;
            novo3->anterior = current;
            novo3->folha = 1;
            novo3->dado1 = current->dado1;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            current->menor = novo3;
            novo4->anterior = current;
            novo4->folha = 1;
            novo4->dado1 = current->dado2;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            current->maior = novo4;
            current->dado1 = valornovo;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
        else if(valornovo > current->dado2){
            current->folha = 0;
            pai->menor->folha = 0;
            no* novo = malloc(sizeof(no));
            no* novo2 = malloc(sizeof(no));
            no* novo3 = malloc(sizeof(no));
            no* novo4 = malloc(sizeof(no));
            novo->anterior = pai->menor;
            novo->folha = 1;
            novo->dado1 = pai->menor->dado1;
            novo->dado2 = 0;
            novo->maior = NULL;
            novo->meio = NULL;
            novo->menor = NULL;
            pai->menor->menor = novo;
            novo2->anterior = pai->menor;
            novo2->folha = 1;
            novo2->dado1 = pai->menor->dado2;
            novo2->dado2 = 0;
            novo2->maior = NULL;
            novo2->meio = NULL;
            novo2->menor = NULL;
            pai->menor->maior = novo2;
            novo3->anterior = current;
            novo3->folha = 1;
            novo3->dado1 = current->dado1;
            novo3->dado2 = 0;
            novo3->maior = NULL;
            novo3->meio = NULL;
            novo3->menor = NULL;
            current->menor = novo3;
            novo4->anterior = current;
            novo4->folha = 1;
            novo4->dado1 = valornovo;
            novo4->dado2 = 0;
            novo4->maior = NULL;
            novo4->meio = NULL;
            novo4->menor = NULL;
            current->maior = novo4;
            current->dado1 = current->dado2;
            current->dado2 = 0;
            pai->dado2 = 0;
        }
    }
}

no* inserir(no* primeiro){
    int valornovo;
    no* current;
    printf("Insira o valor a ser posto na árvore\n");
    scanf("%d", &valornovo);
    current = primeiro;
    for(int i = 0; i <= nos*2; i++){
        no* pai;
        if(current->anterior == NULL){}
        else{
            no* pai = current->anterior;
        }
        if(current->folha = 1 && current->dado2 == NULL){
            current->dado2 = valornovo;
            organizar(current);
            break;
        }
        else if(current->folha = 1){
            caso1(current, valornovo);
            break;
        }
        else if(current->folha == 1 && pai->dado2 == NULL){
            caso2(current, pai, valornovo);
            break;
        }
        else if(current->folha == 1 && current->dado2 != 0 && pai->dado2 != 0){
            caso3(current, pai, valornovo);
            break;
        }
        else{
            if(valornovo <= current->dado1){
                current = current->menor;
            }
            else if(valornovo > current->dado1 && valornovo < current->dado2){
                current = current->meio;
            }
            else{
                current = current->maior;
            }
        }
    }
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