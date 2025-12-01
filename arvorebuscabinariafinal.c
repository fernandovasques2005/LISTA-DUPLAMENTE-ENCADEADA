#include <stdio.h>
#include <stdlib.h>

// --- Definição da Estrutura do Nó ---
typedef struct no {
    int dado;           // O valor numérico armazenado
    struct no *esq;     // Ponteiro para a subárvore esquerda (valores menores)
    struct no *dir;     // Ponteiro para a subárvore direita (valores maiores)
} no;

// Variável global para contar o total de elementos na árvore
int nos = 0;

// --- Protótipos das Funções (Índice do código) ---
no* criarNo(int valor);
no* inserir(no* raiz, int valor);
no* remover(no* raiz, int valor);
void buscar(no* raiz, int valor);
void preOrdem(no* raiz);
void emOrdem(no* raiz);
void posOrdem(no* raiz);
void liberarArvore(no* raiz);
void submenuPercursos(no* raiz);

// --- Função Principal (Menu) ---
int main() {
    no* raiz = NULL; // A árvore começa vazia
    int opcao, valor;

    do {
        printf("\n--- ARVORE BST (%d nos) ---\n", nos);
        printf("1. Inserir\n");
        printf("2. Remover\n");
        printf("3. Buscar\n");
        printf("4. Percorrer\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor para inserir: ");
                scanf("%d", &valor);
                // IMPORTANTE: Atualizamos a raiz, pois ela pode mudar (ex: inserir na árvore vazia)
                raiz = inserir(raiz, valor);
                break;
            case 2:
                printf("Digite o valor para remover: ");
                scanf("%d", &valor);
                // IMPORTANTE: Atualizamos a raiz, pois podemos ter removido o nó raiz
                raiz = remover(raiz, valor);
                break;
            case 3:
                printf("Digite o valor para buscar: ");
                scanf("%d", &valor);
                buscar(raiz, valor);
                break;
            case 4:
                submenuPercursos(raiz);
                break;
            case 0:
                printf("Liberando memoria e saindo...\n");
                liberarArvore(raiz); // Limpeza de memória antes de fechar
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Função Auxiliar: Criação de Nó ---
no* criarNo(int valor) {
    // malloc: Pede espaço na memória RAM para um novo nó
    no *novo = (no*)malloc(sizeof(no));
    if (novo == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        exit(1);
    }
    novo->dado = valor;
    novo->esq = NULL; // Inicializa ponteiros como NULL para evitar lixo de memória
    novo->dir = NULL;
    return novo;
}

// --- Inserção Iterativa (Sem recursão) ---
no* inserir(no* raiz, int valor) {
    
    // Caso especial: Árvore vazia, o novo nó vira a raiz
    if (raiz == NULL) {
        nos++;
        return criarNo(valor);
    }

    no *atual = raiz;

    // Loop infinito para navegar até achar uma vaga (folha)
    while (1) {
        if (valor < atual->dado) {
            // Vai para a Esquerda
            if (atual->esq == NULL) {
                // Achou uma vaga na esquerda! Insere aqui.
                atual->esq = criarNo(valor);
                nos++;
                printf("Inserido na esquerda de %d\n", atual->dado);
                break; // Sai do loop
            } else {
                atual = atual->esq; // Continua descendo para a esquerda
            }
        } 
        else if (valor > atual->dado) {
            // Vai para a Direita
            if (atual->dir == NULL) {
                // Achou uma vaga na direita! Insere aqui.
                atual->dir = criarNo(valor);
                nos++;
                printf("Inserido na direita de %d\n", atual->dado);
                break; // Sai do loop
            } else {
                atual = atual->dir; // Continua descendo para a direita
            }
        } 
        else {
            printf("Valor %d ja existe (duplicado). Ignorado.\n", valor);
            break;
        }
    }
    return raiz; // Retorna a raiz intacta (ou a nova raiz se era vazia)
}

// --- Remoção Recursiva (A lógica mais complexa) ---
no* remover(no* raiz, int valor) {
    // Caso base: Árvore vazia ou valor não encontrado
    if (raiz == NULL) {
        printf("Valor nao encontrado ou arvore vazia.\n");
        return NULL;
    }

    // --- Navegação ---
    if (valor < raiz->dado) {
        // O valor está na esquerda, chama a função para a subárvore esquerda
        raiz->esq = remover(raiz->esq, valor);
    }
    else if (valor > raiz->dado) {
        // O valor está na direita, chama a função para a subárvore direita
        raiz->dir = remover(raiz->dir, valor);
    }
    else {
        // --- Valor Encontrado! (raiz->dado == valor) ---

        // CASOS 1 e 2: Nó sem filhos ou com apenas 1 filho
        if (raiz->esq == NULL) {
            no* temp = raiz->dir; // Salva o filho da direita (pode ser NULL)
            free(raiz);           // Apaga o nó atual
            nos--;
            printf("No removido.\n");
            return temp;          // Retorna o filho para ocupar o lugar do pai
        }
        else if (raiz->dir == NULL) {
            no* temp = raiz->esq; // Salva o filho da esquerda
            free(raiz);           // Apaga o nó atual
            nos--;
            printf("No removido.\n");
            return temp;          // Retorna o filho para ocupar o lugar do pai
        }

        // CASO 3: Nó com 2 filhos
        // Estratégia: Substituir pelo "Sucessor" (O menor valor da subárvore direita)
        
        no* temp = raiz->dir; // Começa indo para a direita
        while (temp->esq != NULL) {
            temp = temp->esq; // Desce tudo para a esquerda
        }

        // Copia o valor do sucessor para o nó que queríamos remover
        raiz->dado = temp->dado;

        // Agora precisamos remover o sucessor original (que está duplicado lá embaixo)
        // Chamamos remover recursivamente na direita
        raiz->dir = remover(raiz->dir, temp->dado);
    }
    return raiz;
}

// --- Busca Iterativa ---
void buscar(no* raiz, int valor) {
    no* atual = raiz;
    // Enquanto não chegar no fim (NULL)
    while (atual != NULL) {
        if (valor == atual->dado) {
            printf("Valor %d ENCONTRADO na arvore!\n", valor);
            return;
        }
        // Decide se vai para esquerda ou direita
        if (valor < atual->dado)
            atual = atual->esq;
        else
            atual = atual->dir;
    }
    printf("Valor %d NAO encontrado.\n", valor);
}

// --- Submenu para os Percursos ---
void submenuPercursos(no* raiz) {
    int subOpcao;
    if (raiz == NULL) {
        printf("A arvore esta vazia.\n");
        return;
    }
    printf("\n--- TIPO DE PERCURSO ---\n");
    printf("1. Pre-ordem (Raiz-Esq-Dir)\n2. Em ordem (Esq-Raiz-Dir)\n3. Pos-ordem (Esq-Dir-Raiz)\nEscolha: ");
    scanf("%d", &subOpcao);
    
    printf("Resultado: [ ");
    switch(subOpcao){
        case 1: preOrdem(raiz); break;
        case 2: emOrdem(raiz); break;
        case 3: posOrdem(raiz); break;
        default: printf("Opcao invalida");
    }
    printf("]\n");
}

// --- Algoritmos de Percurso (Recursivos) ---
void preOrdem(no* raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->dado); // Visita Raiz
        preOrdem(raiz->esq);       // Visita Esquerda
        preOrdem(raiz->dir);       // Visita Direita
    }
}

void emOrdem(no* raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);        // Visita Esquerda
        printf("%d ", raiz->dado); // Visita Raiz
        emOrdem(raiz->dir);        // Visita Direita
    }
}

void posOrdem(no* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);       // Visita Esquerda
        posOrdem(raiz->dir);       // Visita Direita
        printf("%d ", raiz->dado); // Visita Raiz
    }
}

// --- Liberação de Memória (Anti-Leak) ---
void liberarArvore(no* raiz) {
    // Usa Pós-Ordem: Filhos morrem antes do pai
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz); // Só deleta o nó depois de deletar seus descendentes
    }
}