#include <stdio.h>

int main() {
    int opcao;
    int condição=1;
    float a1, b1, resultado1;
    float a2, b2, resultado2;
    float a3, b3, resultado3;
    float a4, b4, resultado4;

    while (condição==1) {
        printf("\n1. Soma\n");
        printf("2. Subtrção\n");
        printf("3. Multipliçâo\n");
        printf("4. Divisâo\n");
        printf("5. Sair\n\n");

        scanf("%d", &opcao);


      /*switch (opcao) {
    
        case 1:
            printf("\nEscolha o \"a\":  ");
            scanf("%f\n\n", &a1);
            printf("Escolha o \"b\":  ");
            scanf("%f\n\n", &b1);
    
            resultado1= a1+b1;
    
            printf("\n\nO resultado é %f\n\n", resultado1);
            
            return 0;

            break;
        
        case 2:
            printf("\nEscolha o \"a\":  ");
            scanf("%f\n\n", &a2);
            printf("Escolha o \"b\":  ");
            scanf("%f\n\n", &b2);
    
            resultado2= a2-b2;
    
            printf("\n\nO resultado é %f\n\n", resultado2);       
    
            return 0;

            break;
    
        case 3:
            printf("\nEscolha o \"a\":  ");
            scanf("%f\n\n", &a3);
            printf("Escolha o \"b\":  ");
            scanf("%f\n\n", &b3);
    
            resultado3= a3*b3;
    
            printf("\n\nO resultado é %f\n\n", resultado3);       
    
            return 0;

            break;
    
        case 4:
            printf("\nEscolha o \"a\":  ");
            scanf("%f\n\n", &a4);
            printf("Escolha o \"b\":  ");
            scanf("%f\n\n", &b4);
    
            resultado3= a4/b4;
    
            printf("\n\nO resultado é %f\n\n", resultado4);       
    
            return 0;

            break;
    
    
        default:
            condição=2;

            return 0;
        
            break;
        }*/


        for(opcao; opcao==1;) {
            printf("\nEscolha o \"a\":  ");
            scanf("%f", &a1);
            printf("\nEscolha o \"b\":  ");
            scanf("%f", &b1);
    
            resultado1= a1+b1;
    
            printf("\n\nO resultado é %f\n\n", resultado1);

            opcao+=5;

        }

        for(opcao; opcao==2;) {
          printf("\nEscolha o \"a\":  ");
            scanf("%f", &a2);
            printf("\nEscolha o \"b\":  ");
            scanf("%f", &b2);
    
            resultado2= a2-b2;
    
            printf("\n\nO resultado é %f\n\n", resultado2); 

            opcao+=5;

        }

        for(opcao; opcao==3;) {
            printf("\nEscolha o \"a\":  ");
            scanf("%f", &a3);
            printf("\nEscolha o \"b\":  ");
            scanf("%f", &b3);
    
            resultado3= a3*b3;
    
            printf("\n\nO resultado é %f\n\n", resultado3);

            opcao+=5;

        }

        for(opcao; opcao==4;) {
            printf("\nEscolha o \"a\":  ");
            scanf("%f", &a4);
            printf("\nEscolha o \"b\":  ");
            scanf("%f", &b4);
    
            resultado4= a4/b4;
    
            printf("\n\nO resultado é %f\n\n", resultado4);

            opcao+=5;

        }

        for(opcao; opcao==5;) {
            system("C:\\WINDOWS\\System32\\shutdown /s");

        }

    }


  
}

/******************\
|     __    __     |
|    /  \__/  \    |
|   |  _    _  |   |
|   |          |   |
|    \ #FANG# /    |
|     \______/     |
|                  |
\******************/