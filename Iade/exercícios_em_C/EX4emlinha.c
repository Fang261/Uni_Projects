#include <stdio.h>

long int linha, coluna, linha2, coluna2, linha3, coluna3, linha4, coluna4, linha5, coluna5, linha6, coluna6, linha7, coluna7, linha8, coluna8, linha9, coluna9;

int main() {
    long int matrix[3][3];

    while(0==0) {
        /*printf("\n\t -----------------------------------------\n");
        printf("\n\t|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n");
        printf("\n\t -----------------------------------------\n");
        printf("\n\t|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n");
        printf("\n\t -----------------------------------------\n");
        printf("\n\t|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n");
        printf("\n\t -----------------------------------------\n");
        printf("\n\t|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n");
        printf("\n\t -----------------------------------------\n");
        printf("\n\t|   %d   |   %d   |   %d   |   %d   |   %d   |   %d   |\n");
        printf("\n\t -----------------------------------------\n");*/

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha);
        scanf("%ld", &coluna);
        linha= linha-1;
        coluna= coluna-1;

        matrix[linha][coluna]= 1;

        for(int col=0;col<3;col++){
            for(int lin=0;lin<3;lin++){
                if(lin==linha && col==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha2);
        scanf("%ld", &coluna2);
        linha2= linha2-1;
        coluna2= coluna2-1;

        matrix[linha2][coluna2]= 2;

        for(int col2=0;col2<3;col2++){
            for(int lin2=0;lin2<3;lin2++){
                if(lin2==linha2 && col2==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin2==linha && col2==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);
                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        } 

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha3);
        scanf("%ld", &coluna3);
        linha3= linha3-1;
        coluna3= coluna3-1;

        matrix[linha3][coluna3]= 1;

        for(int col3=0;col3<3;col3++){
            for(int lin3=0;lin3<3;lin3++){
                if(lin3==linha3 && col3==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin3==linha2 && col3==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin3==linha && col3==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha4);
        scanf("%ld", &coluna4);
        linha4= linha4-1;
        coluna4= coluna4-1;

        matrix[linha4][coluna4]= 2;

        for(int col4=0;col4<3;col4++){
            for(int lin4=0;lin4<3;lin4++){
                if(lin4==linha4 && col4==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);

                }else if(lin4==linha3 && col4==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin4==linha2 && col4==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin4==linha && col4==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }
  
        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha5);
        scanf("%ld", &coluna5);
        linha5= linha5-1;
        coluna5= coluna5-1;

        matrix[linha5][coluna2]= 1;

        for(int col5=0;col5<3;col5++){
            for(int lin5=0;lin5<3;lin5++){
                if(lin5==linha5 && col5==coluna5) {
                    printf("|%ld| " ,matrix[linha5][coluna5]);

                }else if(lin5==linha4 && col5==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);
                
                }else if(lin5==linha3 && col5==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin5==linha2 && col5==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin5==linha && col5==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha6);
        scanf("%ld", &coluna6);
        linha6= linha6-1;
        coluna6= coluna6-1;

        matrix[linha6][coluna6]= 2;

        for(int col6=0;col6<3;col6++){
            for(int lin6=0;lin6<3;lin6++){
                if(lin6==linha6 && col6==coluna6) {
                    printf("|%ld| " ,matrix[linha6][coluna6]);

                }else if(lin6==linha5 && col6==coluna5) {
                    printf("|%ld| " ,matrix[linha5][coluna5]);
                
                }else if(lin6==linha4 && col6==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);
                
                }else if(lin6==linha3 && col6==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin6==linha2 && col6==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin6==linha && col6==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha7);
        scanf("%ld", &coluna7);
        linha7= linha7-1;
        coluna7= coluna7-1;

        matrix[linha7][coluna7]= 1;

        for(int col7=0;col7<3;col7++){
            for(int lin7=0;lin7<3;lin7++){
                if(lin7==linha7 && col7==coluna7) {
                    printf("|%ld| " ,matrix[linha7][coluna7]);

                }else if(lin7==linha6 && col7==coluna6) {
                    printf("|%ld| " ,matrix[linha6][coluna6]);
                
                }else if(lin7==linha5 && col7==coluna5) {
                    printf("|%ld| " ,matrix[linha5][coluna5]);
                
                }else if(lin7==linha4 && col7==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);
                
                }else if(lin7==linha3 && col7==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin7==linha2 && col7==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin7==linha && col7==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }

        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha8);
        scanf("%ld", &coluna8);
        linha8= linha8-1;
        coluna8= coluna8-1;

        matrix[linha8][coluna8]= 2;

        for(int col8=0;col8<3;col8++){
            for(int lin8=0;lin8<3;lin8++){
                if(lin8==linha8 && col8==coluna8) {
                    printf("|%ld| " ,matrix[linha8][coluna8]);

                }else if(lin8==linha7 && col8==coluna7) {
                    printf("|%ld| " ,matrix[linha7][coluna7]);
                
                }else if(lin8==linha6 && col8==coluna6) {
                    printf("|%ld| " ,matrix[linha6][coluna6]);
                
                }else if(lin8==linha5 && col8==coluna5) {
                    printf("|%ld| " ,matrix[linha5][coluna5]);
                
                }else if(lin8==linha4 && col8==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);

                }else if(lin8==linha3 && col8==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin8==linha2 && col8==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin8==linha && col8==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }
        printf ("\n\n\tEscolha a coluna e depois a linha:\n\n");
        scanf("%ld", &linha9);
        scanf("%ld", &coluna9);
        linha9= linha9-1;
        coluna9= coluna9-1;

        matrix[linha9][coluna9]= 1;

        for(int col9=0;col9<3;col9++){
            for(int lin9=0;lin9<3;lin9++){
                if(lin9==linha9 && col9==coluna9) {
                    printf("|%ld| " ,matrix[linha9][coluna9]);

                }else if (lin9==linha8 && col9==coluna8) {
                    printf("|%ld| " ,matrix[linha8][coluna8]);           
                
                }else if(lin9==linha7 && col9==coluna7) {
                    printf("|%ld| " ,matrix[linha7][coluna7]);
                
                }else if(lin9==linha6 && col9==coluna6) {
                    printf("|%ld| " ,matrix[linha6][coluna6]);
                
                }else if(lin9==linha5 && col9==coluna5) {
                    printf("|%ld| " ,matrix[linha5][coluna5]);
                
                }else if(lin9==linha4 && col9==coluna4) {
                    printf("|%ld| " ,matrix[linha4][coluna4]);
                
                }else if(lin9==linha3 && col9==coluna3) {
                    printf("|%ld| " ,matrix[linha3][coluna3]);

                }else if(lin9==linha2 && col9==coluna2) {
                    printf("|%ld| " ,matrix[linha2][coluna2]);

                }else if(lin9==linha && col9==coluna) {
                    printf("|%ld| " ,matrix[linha][coluna]);

                }else {
                    printf("|0| ");

                }

            }
            printf("\n\n");

        }
        
    }  
    return 0 ;

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
 