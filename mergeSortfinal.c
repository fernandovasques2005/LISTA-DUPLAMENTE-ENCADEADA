#include <stdio.h>
#include <stdlib.h>

// Função para mesclar os subvetores
void merge(int arr[], int left, int mid, int right) {
    int i = left;      // Início do subvetor esquerdo
    int j = mid + 1;   // Início do subvetor direito
    int k = 0;         // Índice para o vetor auxiliar
    int size = right - left + 1;

    // Alocação do VETOR AUXILIAR (Rascunho)
    int *temp = (int *)malloc(size * sizeof(int));

    // 1. COMPARAÇÃO ENTRE SUBVETORES e INSERÇÃO ORDENADA NO VETOR AUXILIAR
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) { // Comparação
            temp[k] = arr[i];   // Inserção ordenada
            i++;
        } else {
            temp[k] = arr[j];   // Inserção ordenada
            j++;
        }
        k++;
    }

    // Caso sobrem elementos no subvetor esquerdo
    while (i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    // Caso sobrem elementos no subvetor direito
    while (j <= right) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    // 2. CÓPIA DE VOLTA PARA O VETOR ORIGINAL
    for (k = 0; k < size; k++) {
        arr[left + k] = temp[k];
    }

    // Liberação da memória auxiliar
    free(temp);
}

// FUNÇÃO RECURSIVA mergeSort
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Chamadas recursivas para dividir o vetor
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Mesclagem das partes divididas
        merge(arr, left, mid, right);
    }
}

// Função auxiliar para imprimir o vetor
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vetor original: ");
    printArray(arr, n);

    mergeSort(arr, 0, n - 1);

    printf("Vetor ordenado: ");
    printArray(arr, n);

    return 0;
}