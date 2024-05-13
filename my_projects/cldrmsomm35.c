#include <stdio.h>

int main() {
    long int numbr, result;

	printf("\nEscreva o número inteiro que quiser:\n\n");
	scanf("%ld", &numbr);

    float multFive = numbr/5;
    float mulThree = numbr/3;
	long double multFift = numbr/15;
	long double smFive = ((((multFive+1)/2)*multFive)*5);
	long double smThree = ((((mulThree+1)/2)*mulThree)*3);
	long double smFift = ((((multFift+1)/2)*multFift)*15);
	
	if (numbr>=0) {

		if (numbr%5==0 || numbr%3==0){

			result = (((smFive+smThree)-smFift)-numbr);

		}else {

			result = ((smFive+smThree)-smFift);

		}

	printf("\nO resultado é %ld\n\n", result);

	}else {

		result = 0;
		printf("\nO resultado é %ld\n\n", result);

	}

	return 0;
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
