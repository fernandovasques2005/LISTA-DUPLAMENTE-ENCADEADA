#include <stdio.h>

int inserção(int vetor[], int tamanho, int v){
    int v1;
    for(int v = 0; v < tamanho; v++){
        int continuar;
        printf("Insira um valor na posição atual\nPosição atual: %d\n", v);
        scanf("%d", &vetor[v]);
        v1++;
    }
    return v1;
}

void troca(int *i, int *j){
    int t = *i;
    *i = *j;
    *j = t;
}

int partição(int vetor[], int baixo, int alto){
    int pivo = alto, i, j = (baixo-1);
    for(int i = baixo; i <= alto-1; i++){
        if(vetor[i] <= vetor[pivo]){
            j++;
            troca(&vetor[i], &vetor[j]);
        }
    }
    troca(&vetor[j+1], &vetor[alto]);
    return j+1;
}

void quicksort(int vetor[], int baixo, int alto){
    if(baixo < alto){
        int pivo = partição(vetor, baixo, alto);
        quicksort(vetor, baixo, pivo-1);
        quicksort(vetor, pivo+1, alto);
    }
}

void mostrar(int vetor[], int tamanho, int v){
    for(int m = 0; m < tamanho; m++){
        if(m != tamanho-1){
            printf("%d -- ", vetor[m]);
        }
        else{
            printf("%d\n", vetor[m]);
        }
    }
    printf("\n");
}

void seleção(int vetor[], int tamanho){
    int seleção, v;
    printf("1.Inserir valor\n2.Organizar valores\n3.Mostrar valores\n");
    scanf("%d", &seleção);
    switch(seleção){
        case 1:
        v = inserção(vetor, tamanho, v);
        break;
        case 2:
        quicksort(vetor, 0, v-1);
        break;
        case 3:
        mostrar(vetor, tamanho, v);
        break;
        default:
        printf("Por favor insira um valor apropriado\n");
    }
}

int main(){
    int tamanho;
    printf("Insira o tamanho do vetor desejado\n");
    scanf("%d", &tamanho);
    if(tamanho <= 0){
        printf("Tamanho inapropriado\n");
        return 0;
    }
    int vetor[tamanho];
    do{
        seleção(vetor, tamanho);
    }while(1);
    return 0;
}
