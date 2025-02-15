#include <stdio.h>


int main() {
    float semana[7];
    int dia= 1;
    float total= 0;

  /*printf("\nIntroduza o número de venddas do 1 dia\n");
    scanf("%f", &semana[0]);
    printf("\nIntroduza o número de venddas do 2 dia\n");
    scanf("%f", &semana[1]);
    printf("\nIntroduza o número de venddas do 3 dia\n");
    scanf("%f", &semana[2]);
    printf("\nIntroduza o número de venddas do 4 dia\n");
    scanf("%f", &semana[3]);
    printf("\nIntroduza o número de venddas do 5 dia\n");
    scanf("%f", &semana[4]);
    printf("\nIntroduza o número de venddas do 6 dia\n");
    scanf("%f", &semana[5]);
    printf("\nIntroduza o número de venddas do 7 dia\n");
    scanf("%f", &semana[6]);*/


    for(int i=0; i<=6; i++){
        printf("\nIntroduza o número de venddas do %d dia\n", dia);
        scanf("%f", &semana[i]);
        total+=semana[i];
        dia++;

    }

  //float total= semana[0]+semana[1]+semana[2]+semana[3]+semana[4]+semana[5]+semana[6];

    printf("\n%f\n", total);

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