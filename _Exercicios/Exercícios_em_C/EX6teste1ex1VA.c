#include <stdbool.h>
#include <stdio.h>

int main() {
    int num_alunos;
    float notas[num_alunos];
    int num_alunos_passados = 0;
    bool checker = false;
    while (checker == false) {
        printf("Insira o numero de alunos.");
        scanf("%d", &num_alunos);
        if (num_alunos > 0) {
            checker = true;
        } else {
            printf("Valor inválido, reintroduza o valor\n");
        }
    }

    int i = 0;
    while (i < num_alunos) { 
        printf("Insira uma nota.");
        scanf("%f", &notas[i]);
        if (notas[i] >= 0 && notas[i] <= 20) {
            i++;
        } else {
            printf("Valor de nota inválida, reintroduza a nota\n");
        }
    }

    for (int i = 0; i < num_alunos; i++) {
        if (notas[i] >= 9.5) {
            num_alunos_passados++;
        }
    }
    printf("Numero de alunos passados %d.\n", num_alunos_passados);
    return 0;
}