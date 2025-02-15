#include <stdio.h>

long int numbr, var, result;

int main() {
    printf("\nEnter a number: ");
    scanf("%ld", &numbr);
    var= 1;
    result= 1;
    if(numbr<16){
        while(var <= numbr ) {
            result*=var;
            var++;

        }
        printf("\n%ld\n\n", result);

    }else {
        printf("\nAbusado!\n\n");

    }
}