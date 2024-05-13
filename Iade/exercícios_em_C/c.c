#include <stdio.h>

int *insereVendasMensais(int arr_vendas[], int numvendedores, int valor_min) {
    for (int i = 0; i < numvendedores; i++) {
        scanf("%d\n", &arr_vendas[i]);
        if (arr_vendas[i] <= 0) {
            printf("vendedor não vendeu:\n");
            arr_vendas[i] = 0;
        }
    }
    for (int i = 0; i < numvendedores; i++) {
        for (int j = 0; j < numvendedores - 1; j++) {
            if (arr_vendas[j] > arr_vendas[j + 1]) {
                int check = arr_vendas[j];
                arr_vendas[j + 1] = arr_vendas[j];
                arr_vendas[j] = check;
            }
        }
    }

    return arr_vendas;
}

int main() {
    const int numvendedores = 10;
    const int valor_min = 1000;
    int arr_vendas[numvendedores - 1];
    insereVendasMensais(arr_vendas, numvendedores, valor_min);
    for (int i = 0; i < numvendedores; i++) {
        printf("%d\n", arr_vendas[i]);
    }

    return 0;
}