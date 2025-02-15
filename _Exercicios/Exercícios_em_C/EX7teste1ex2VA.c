#include <stdio.h>

int main() {
    int opcao;
    float valor = 0;
    float taxad = 0.99;
    float taxal = 0.88;
    while (0 == 0) {
      printf("Escolha a opção.\n\n");
      printf("1. Introduzir valor em euros.\n");
      printf("2. Converter valor para doláres.\n");
      printf("3. Converter valor para Libras.\n");
      printf("4. Alterar taxas de conversão.\n");
      printf("5. Sair.\n");
        scanf("%d", &opcao);
        if (opcao == 1) {
            while (0 == 0) {
                scanf("%f", &valor);
                if (valor > 0) {
                    break;
                } else {
                    printf("valor inválido, reintroduza.\n");
                }
            }

        } else if (opcao == 2) {
            while (0 == 0) {
                if (valor > 0) {
                    valor = valor * taxad;
                    break;
                } else {
                    printf("Por favor introduza um valor monetário em euros.\n");
                }
            }
        } else if (opcao == 3) {
            while (0 == 0) {
                if (valor > 0) {
                    valor = valor * taxal;
                    break;
                } else {
                    printf("Por favor introduza um valor monetário em euros.\n");
                }
            }
        } else if (opcao == 4) {
            printf("Introduza o novo valor para a taxa de dolares.\n");
            scanf("%f", &taxad);
            printf("Introduza o novo valor para a taxa de libras.\n");
            scanf("%f", &taxal);
        } else if (opcao == 5) {
            printf("saiu do programa.\n");
            break;
        } else {
            printf("opcão inválida.\n");
        }
    }

    return 0;
}