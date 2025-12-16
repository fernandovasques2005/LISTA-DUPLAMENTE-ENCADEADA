#include <stdio.h>
#include <stdlib.h>

#define COR_VERMELHA "\033[1;31m"
#define COR_RESET    "\033[0m"

typedef enum { VERMELHO, PRETO } Cor;

typedef struct No {
    int dado;
    Cor cor;
    struct No *pai;
    struct No *esquerda;
    struct No *direita;
} No;

No *TNULL;

int main();
void inicializarTNULL();
No* criarNo(int dado);
void rotacaoEsquerda(No **raiz, No *x);
void rotacaoDireita(No **raiz, No *y);
void balancearInsercao(No **raiz, No *k);
void inserir(No **raiz, int dado);
void transplante(No **raiz, No *u, No *v);
No* minimo(No *no);
void balancearRemocao(No **raiz, No *x);
void remover(No **raiz, int chave);
No* buscar(No *raiz, int valor);
void imprimirNo(No *no);
void preOrdem(No *no);
void emOrdem(No *no);
void posOrdem(No *no);
void liberarArvore(No *no);

int main() {
    inicializarTNULL();
    No *raiz = TNULL;
    int escolha, valor;
    No *res;

    do {
        printf("\n\n--- ARVORE RUBRO-NEGRA ---\n");
        printf("1. Inserir\n2. Remover\n3. Buscar\n4. Listar (Pre/Em/Pos)\n0. Sair\nEscolha: ");
        scanf("%d", &escolha);

        switch(escolha){
            case 1:
                printf("Insira o valor: ");
                scanf("%d", &valor);
                inserir(&raiz, valor);
                break;
            case 2:
                printf("Insira o valor para remover: ");
                scanf("%d", &valor);
                remover(&raiz, valor);
                break;
            case 3:
                printf("Insira o valor para buscar: ");
                scanf("%d", &valor);
                res = buscar(raiz, valor);
                if(res != TNULL) {
                    printf("Encontrado: ");
                    // Imprime o resultado colorido também
                    if (res->cor == VERMELHO) printf(COR_VERMELHA "%d" COR_RESET "\n", res->dado);
                    else printf("%d (Preto)\n", res->dado);
                } else {
                    printf("Nao encontrado.\n");
                }
                break;
            case 4:
                printf("\nPre-ordem: "); preOrdem(raiz);
                printf("\nEm ordem:  "); emOrdem(raiz);
                printf("\nPos-ordem: "); posOrdem(raiz);
                printf("\n");
                break;
            case 0:
                liberarArvore(raiz);
                free(TNULL);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while(escolha != 0);

    return 0;
}

void inicializarTNULL() {
    TNULL = (No *)malloc(sizeof(No));
    TNULL->cor = PRETO;
    TNULL->esquerda = NULL;
    TNULL->direita = NULL;
    TNULL->dado = 0;
}

No* criarNo(int dado) {
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = dado;
    novo->pai = NULL;
    novo->esquerda = TNULL;
    novo->direita = TNULL;
    novo->cor = VERMELHO;
    return novo;
}

void rotacaoEsquerda(No **raiz, No *x) {
    No *y = x->direita;
    x->direita = y->esquerda;
    if (y->esquerda != TNULL) {
        y->esquerda->pai = x;
    }
    y->pai = x->pai;
    if (x->pai == NULL) {
        *raiz = y;
    } else if (x == x->pai->esquerda) {
        x->pai->esquerda = y;
    } else {
        x->pai->direita = y;
    }
    y->esquerda = x;
    x->pai = y;
}

void rotacaoDireita(No **raiz, No *y) {
    No *x = y->esquerda;
    y->esquerda = x->direita;
    if (x->direita != TNULL) {
        x->direita->pai = y;
    }
    x->pai = y->pai;
    if (y->pai == NULL) {
        *raiz = x;
    } else if (y == y->pai->direita) {
        y->pai->direita = x;
    } else {
        y->pai->esquerda = x;
    }
    x->direita = y;
    y->pai = x;
}

void balancearInsercao(No **raiz, No *k) {
    No *u;
    while (k->pai != NULL && k->pai->cor == VERMELHO) {
        if (k->pai == k->pai->pai->direita) {
            u = k->pai->pai->esquerda;
            if (u->cor == VERMELHO) {
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->esquerda) {
                    k = k->pai;
                    rotacaoDireita(raiz, k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, k->pai->pai);
            }
        } else {
            u = k->pai->pai->direita;
            if (u->cor == VERMELHO) {
                u->cor = PRETO;
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                k = k->pai->pai;
            } else {
                if (k == k->pai->direita) {
                    k = k->pai;
                    rotacaoEsquerda(raiz, k);
                }
                k->pai->cor = PRETO;
                k->pai->pai->cor = VERMELHO;
                rotacaoDireita(raiz, k->pai->pai);
            }
        }
        if (k == *raiz) break;
    }
    (*raiz)->cor = PRETO;
}

void inserir(No **raiz, int dado) {
    No *novo = criarNo(dado);
    No *y = NULL;
    No *x = *raiz;

    while (x != TNULL) {
        y = x;
        if (novo->dado < x->dado) {
            x = x->esquerda;
        } else {
            x = x->direita;
        }
    }

    novo->pai = y;
    if (y == NULL) {
        *raiz = novo;
    } else if (novo->dado < y->dado) {
        y->esquerda = novo;
    } else {
        y->direita = novo;
    }

    if (novo->pai == NULL) {
        novo->cor = PRETO;
        return;
    }
    if (novo->pai->pai == NULL) {
        return;
    }

    balancearInsercao(raiz, novo);
    printf("Valor ");
    if(novo->cor == VERMELHO) printf(COR_VERMELHA "%d" COR_RESET, dado);
    else printf("%d", dado);
    printf(" inserido com sucesso.\n");
}

void transplante(No **raiz, No *u, No *v) {
    if (u->pai == NULL) {
        *raiz = v;
    } else if (u == u->pai->esquerda) {
        u->pai->esquerda = v;
    } else {
        u->pai->direita = v;
    }
    v->pai = u->pai;
}

No* minimo(No *no) {
    while (no->esquerda != TNULL) {
        no = no->esquerda;
    }
    return no;
}

void balancearRemocao(No **raiz, No *x) {
    No *w;
    while (x != *raiz && x->cor == PRETO) {
        if (x == x->pai->esquerda) {
            w = x->pai->direita;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoEsquerda(raiz, x->pai);
                w = x->pai->direita;
            }
            if (w->esquerda->cor == PRETO && w->direita->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->direita->cor == PRETO) {
                    w->esquerda->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoDireita(raiz, w);
                    w = x->pai->direita;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->direita->cor = PRETO;
                rotacaoEsquerda(raiz, x->pai);
                x = *raiz;
            }
        } else {
            w = x->pai->esquerda;
            if (w->cor == VERMELHO) {
                w->cor = PRETO;
                x->pai->cor = VERMELHO;
                rotacaoDireita(raiz, x->pai);
                w = x->pai->esquerda;
            }
            if (w->direita->cor == PRETO && w->esquerda->cor == PRETO) {
                w->cor = VERMELHO;
                x = x->pai;
            } else {
                if (w->esquerda->cor == PRETO) {
                    w->direita->cor = PRETO;
                    w->cor = VERMELHO;
                    rotacaoEsquerda(raiz, w);
                    w = x->pai->esquerda;
                }
                w->cor = x->pai->cor;
                x->pai->cor = PRETO;
                w->esquerda->cor = PRETO;
                rotacaoDireita(raiz, x->pai);
                x = *raiz;
            }
        }
    }
    x->cor = PRETO;
}

void remover(No **raiz, int chave) {
    No *z = TNULL;
    No *x, *y;
    No *no = *raiz;

    while (no != TNULL) {
        if (no->dado == chave) z = no;
        if (no->dado <= chave) no = no->direita;
        else no = no->esquerda;
    }

    if (z == TNULL) {
        printf("Chave %d nao encontrada.\n", chave);
        return;
    }

    y = z;
    Cor corOriginalY = y->cor;

    if (z->esquerda == TNULL) {
        x = z->direita;
        transplante(raiz, z, z->direita);
    } else if (z->direita == TNULL) {
        x = z->esquerda;
        transplante(raiz, z, z->esquerda);
    } else {
        y = minimo(z->direita);
        corOriginalY = y->cor;
        x = y->direita;
        if (y->pai == z) {
            x->pai = y;
        } else {
            transplante(raiz, y, y->direita);
            y->direita = z->direita;
            y->direita->pai = y;
        }
        transplante(raiz, z, y);
        y->esquerda = z->esquerda;
        y->esquerda->pai = y;
        y->cor = z->cor;
    }

    free(z);

    if (corOriginalY == PRETO) {
        balancearRemocao(raiz, x);
    }
    printf("Removido com sucesso.\n");
}

No* buscar(No *raiz, int valor) {
    if (raiz == TNULL || raiz->dado == valor)
        return raiz;

    if (valor < raiz->dado)
        return buscar(raiz->esquerda, valor);
    else
        return buscar(raiz->direita, valor);
}

void imprimirNo(No *no) {
    if (no->cor == VERMELHO) {
        printf(COR_VERMELHA "%d" COR_RESET " ", no->dado);
    } else {
        printf("%d ", no->dado);
    }
}

void preOrdem(No *no) {
    if (no != TNULL) {
        imprimirNo(no);
        preOrdem(no->esquerda);
        preOrdem(no->direita);
    }
}

void emOrdem(No *no) {
    if (no != TNULL) {
        emOrdem(no->esquerda);
        imprimirNo(no);
        emOrdem(no->direita);
    }
}

void posOrdem(No *no) {
    if (no != TNULL) {
        posOrdem(no->esquerda);
        posOrdem(no->direita);
        imprimirNo(no);
    }
}

void liberarArvore(No *no) {
    if (no != TNULL) {
        liberarArvore(no->esquerda);
        liberarArvore(no->direita);
        free(no);
    }

}
