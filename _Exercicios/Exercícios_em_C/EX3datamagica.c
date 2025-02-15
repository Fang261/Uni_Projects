#include <stdio.h>

int day, month, year;

int main() {
    printf("\nEnter a random day\n\n");
    scanf("%d", &day);
    printf("\nEnter a random month\n\n");
    scanf("%d", &month);
    printf("\nEnter a random year\n\n");

    scanf("%d", &year);

    if(day*month==year) {

        printf("\nÉ uma data mágica\n\n");

    }else {

        printf("\nNão é uma data mágica\n\n");

    }
    
    return 0;

}


















































