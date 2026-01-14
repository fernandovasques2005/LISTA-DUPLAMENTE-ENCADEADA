#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Estrutura do Nó 2-3:
   - chaves[3]: permite até 2 chaves; o índice 2 é usado temporariamente no split/merge.
   - filhos[4]: permite até 3 filhos; o índice 3 é usado temporariamente.
   - n_chaves: rastreia se o nó é um "2-node" (1 chave) ou "3-node" (2 chaves).
   - folha: booleano para identificar se o nó não possui filhos.
*/
typedef struct No23 {
    int chaves[3];           
    struct No23 *filhos[4];  
    int n_chaves;            
    bool folha;              
} No23;

/* Estrutura de Fila auxiliar para a exibição Por Nível (BFS) */
typedef struct Fila {
    No23* no;
    struct Fila* prox;
} Fila;

// --- UTILITÁRIOS DE FILA ---

void enfileira(Fila** inicio, Fila** fim, No23* no) {
    Fila* novo = (Fila*)malloc(sizeof(Fila));
    novo->no = no;
    novo->prox = NULL;
    if (*fim) (*fim)->prox = novo;
    else *inicio = novo;
    *fim = novo;
}

No23* desenfileira(Fila** inicio, Fila** fim) {
    if (*inicio == NULL) return NULL;
    Fila* temp = *inicio;
    No23* no = temp->no;
    *inicio = (*inicio)->prox;
    if (*inicio == NULL) *fim = NULL;
    free(temp);
    return no;
}

// --- BUSCA ---

bool buscar(No23* raiz, int chave) {
    if (!raiz) return false;
    
    // Verifica se a chave está no nó atual (pode estar na posição 0 ou 1)
    if (chave == raiz->chaves[0] || (raiz->n_chaves == 2 && chave == raiz->chaves[1]))
        return true;
    
    // Se for folha e não encontramos acima, a chave não existe
    if (raiz->folha) return false;
    
    // Navegação multivias baseada nos intervalos das chaves
    if (chave < raiz->chaves[0]) 
        return buscar(raiz->filhos[0], chave);
    else if (raiz->n_chaves == 1 || chave < raiz->chaves[1]) 
        return buscar(raiz->filhos[1], chave);
    else 
        return buscar(raiz->filhos[2], chave);
}

// --- INSERÇÃO (Lógica de Cisão Posterior) ---

No23* criarNo(bool folha) {
    No23* novo = (No23*)malloc(sizeof(No23));
    novo->n_chaves = 0;
    novo->folha = folha;
    for (int i = 0; i < 4; i++) novo->filhos[i] = NULL;
    return novo;
}

/* Realiza a cisão (split) de um nó que atingiu 3 chaves.
   A chave mediana (índice 1) é promovida para o pai.
*/
No23* split(No23* no, int *promovida, No23** novoDir) {
    No23* dir = criarNo(no->folha);
    *promovida = no->chaves[1]; // Chave do meio sobe
    
    dir->chaves[0] = no->chaves[2]; // Chave da direita vai para o novo nó
    dir->n_chaves = 1;
    
    // Se não for folha, redistribui os ponteiros dos filhos
    if (!no->folha) {
        dir->filhos[0] = no->filhos[2];
        dir->filhos[1] = no->filhos[3];
    }
    
    no->n_chaves = 1; // Nó original agora só tem a chave da esquerda
    *novoDir = dir;
    return no;
}

/* Função recursiva para encontrar o local de inserção e tratar overflow na volta */
No23* inserirRec(No23* no, int chave, int *prom, No23** nDir) {
    int i = no->n_chaves - 1;
    if (no->folha) {
        // Insere a chave ordenadamente no nó folha
        while (i >= 0 && no->chaves[i] > chave) { no->chaves[i+1] = no->chaves[i]; i--; }
        no->chaves[i+1] = chave;
        no->n_chaves++;
    } else {
        // Navega para o filho apropriado
        while (i >= 0 && no->chaves[i] > chave) i--;
        if (inserirRec(no->filhos[i+1], chave, prom, nDir)) {
            // Se o filho sofreu split, insere a chave promovida no nó atual
            int j = no->n_chaves - 1;
            while (j >= 0 && no->chaves[j] > *prom) {
                no->chaves[j+1] = no->chaves[j];
                no->filhos[j+2] = no->filhos[j+1];
                j--;
            }
            no->chaves[j+1] = *prom;
            no->filhos[j+2] = *nDir;
            no->n_chaves++;
        } else return NULL;
    }
    // Se este nó ficou com 3 chaves, dispara o split para o nível acima
    return (no->n_chaves == 3) ? split(no, prom, nDir) : NULL;
}

void inserir(No23** raiz, int chave) {
    if (*raiz == NULL) { 
        *raiz = criarNo(true); (*raiz)->chaves[0] = chave; (*raiz)->n_chaves = 1; return; 
    }
    int prom; No23* nDir = NULL;
    // Se a raiz sofrer split, a altura da árvore aumenta
    if (inserirRec(*raiz, chave, &prom, &nDir)) {
        No23* nRaiz = criarNo(false);
        nRaiz->chaves[0] = prom; nRaiz->filhos[0] = *raiz; nRaiz->filhos[1] = nDir; nRaiz->n_chaves = 1;
        *raiz = nRaiz;
    }
}

// --- REMOÇÃO (Lógica de Underflow: Redistribuição e Fusão) ---

/* Encontra o menor valor na subárvore direita para substituir chaves em nós internos */
int pegarSucessor(No23* no) {
    No23* atual = no;
    while (!atual->folha) atual = atual->filhos[0];
    return atual->chaves[0];
}

/* Tenta pegar uma chave emprestada de um irmão adjacente */
void redistribuir(No23* pai, int idx, bool esquerda) {
    No23* filho = pai->filhos[idx];
    if (esquerda) { // Irmão da esquerda tem chaves sobrando
        No23* irmao = pai->filhos[idx-1];
        for (int i = filho->n_chaves; i > 0; i--) filho->chaves[i] = filho->chaves[i-1];
        if (!filho->folha) {
            for (int i = filho->n_chaves + 1; i > 0; i--) filho->filhos[i] = filho->filhos[i-1];
            filho->filhos[0] = irmao->filhos[irmao->n_chaves];
        }
        filho->chaves[0] = pai->chaves[idx-1]; // Desce a chave do pai
        pai->chaves[idx-1] = irmao->chaves[irmao->n_chaves-1]; // Sobe a chave do irmão
        filho->n_chaves++; irmao->n_chaves--;
    } else { // Irmão da direita tem chaves sobrando
        No23* irmao = pai->filhos[idx+1];
        filho->chaves[filho->n_chaves] = pai->chaves[idx];
        if (!filho->folha) filho->filhos[filho->n_chaves+1] = irmao->filhos[0];
        pai->chaves[idx] = irmao->chaves[0];
        for (int i = 0; i < irmao->n_chaves-1; i++) irmao->chaves[i] = irmao->chaves[i+1];
        if (!irmao->folha) {
            for (int i = 0; i < irmao->n_chaves; i++) irmao->filhos[i] = irmao->filhos[i+1];
        }
        filho->n_chaves++; irmao->n_chaves--;
    }
}

/* Une dois irmãos e uma chave do pai em um único nó */
void merge(No23* pai, int idx) {
    No23* esq = pai->filhos[idx];
    No23* dir = pai->filhos[idx+1];
    esq->chaves[esq->n_chaves] = pai->chaves[idx]; // Desce a chave do pai
    for (int i = 0; i < dir->n_chaves; i++) esq->chaves[esq->n_chaves + 1 + i] = dir->chaves[i];
    if (!esq->folha) {
        for (int i = 0; i <= dir->n_chaves; i++) esq->filhos[esq->n_chaves + 1 + i] = dir->filhos[i];
    }
    esq->n_chaves += dir->n_chaves + 1;
    // Ajusta o pai que perdeu uma chave e um ponteiro de filho
    for (int i = idx; i < pai->n_chaves - 1; i++) pai->chaves[i] = pai->chaves[i+1];
    for (int i = idx + 1; i < pai->n_chaves; i++) pai->filhos[i] = pai->filhos[i+1];
    pai->n_chaves--;
    free(dir);
}

/* Coordena se deve haver redistribuição ou fusão após uma remoção que gerou underflow */
void ajustar(No23* pai, int idx) {
    if (idx > 0 && pai->filhos[idx-1]->n_chaves > 1) redistribuir(pai, idx, true);
    else if (idx < pai->n_chaves && pai->filhos[idx+1]->n_chaves > 1) redistribuir(pai, idx, false);
    else {
        if (idx < pai->n_chaves) merge(pai, idx);
        else merge(pai, idx - 1);
    }
}

bool removerRec(No23* no, int chave) {
    int i = 0;
    while (i < no->n_chaves && chave > no->chaves[i]) i++;
    if (i < no->n_chaves && no->chaves[i] == chave) {
        if (no->folha) {
            // Caso simples: remoção em nó folha
            for (int j = i; j < no->n_chaves - 1; j++) no->chaves[j] = no->chaves[j+1];
            no->n_chaves--; return true;
        } else {
            // Caso complexo: nó interno. Substitui pelo sucessor e remove na folha.
            int sucessor = pegarSucessor(no->filhos[i+1]);
            no->chaves[i] = sucessor;
            removerRec(no->filhos[i+1], sucessor);
            if (no->filhos[i+1]->n_chaves == 0) ajustar(no, i+1);
            return true;
        }
    }
    if (no->folha) return false;
    // Continua a busca pela chave nos filhos
    bool res = removerRec(no->filhos[i], chave);
    if (no->filhos[i]->n_chaves == 0) ajustar(no, i);
    return res;
}

void remover(No23** raiz, int chave) {
    if (*raiz == NULL) return;
    if (removerRec(*raiz, chave)) {
        // Se a raiz ficou vazia, o primeiro filho torna-se a nova raiz (diminui altura)
        if ((*raiz)->n_chaves == 0) {
            No23* antigo = *raiz;
            *raiz = (*raiz)->folha ? NULL : (*raiz)->filhos[0];
            free(antigo);
        }
    } else printf("Chave %d nao encontrada.\n", chave);
}

// --- EXIBIÇÃO ---

void emOrdem(No23* raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->filhos[0]);
    printf("%d ", raiz->chaves[0]);
    emOrdem(raiz->filhos[1]);
    if (raiz->n_chaves == 2) {
        printf("%d ", raiz->chaves[1]);
        emOrdem(raiz->filhos[2]);
    }
}

void porNivel(No23* raiz) {
    if (raiz == NULL) return;
    Fila *i = NULL, *f = NULL;
    enfileira(&i, &f, raiz);
    while (i) {
        int cont = 0; Fila* t = i;
        while (t) { cont++; t = t->prox; }
        // Processa todos os nós do nível atual antes de pular a linha
        while (cont--) {
            No23* n = desenfileira(&i, &f);
            printf("[");
            for (int j = 0; j < n->n_chaves; j++) printf("%d%s", n->chaves[j], j == n->n_chaves-1 ? "" : "|");
            printf("] ");
            if (!n->folha) {
                for (int j = 0; j <= n->n_chaves; j++) enfileira(&i, &f, n->filhos[j]);
            }
        }
        printf("\n");
    }
}

// --- MAIN COM MENU INTERATIVO ---

int main() {
    No23* raiz = NULL; int op, v;
    do {
        printf("\n==== ARVORE 2-3 ====\n");
        printf("1. Inserir\n2. Remover\n3. Buscar\n4. Em Ordem\n5. Nivel\n6. Sair\nEscolha: ");
        scanf("%d", &op);
        switch(op) {
            case 1: printf("Valor: "); scanf("%d", &v); inserir(&raiz, v); break;
            case 2: printf("Remover: "); scanf("%d", &v); remover(&raiz, v); break;
            case 3: printf("Busca: "); scanf("%d", &v); 
                    printf(buscar(raiz, v) ? "Valor encontrado!\n" : "Valor nao encontrado!\n"); break;
            case 4: printf("Crescente: "); emOrdem(raiz); printf("\n"); break;
            case 5: printf("Estrutura por Niveis:\n"); porNivel(raiz); break;
        }
    } while(op != 6);
    return 0;
}