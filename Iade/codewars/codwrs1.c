int solution(int numbr, int result) {

  float multFive = numbr/5;
  float mulThree = numbr/3;
	float multFift = numbr/15;
	float smFive = ((((multFive+1)/2)*multFive)*5);
	float smThree = ((((mulThree+1)/2)*mulThree)*3);
	float smFift = ((((multFift+1)/2)*multFift)*15);
	
	if (numbr>=0) {

		if (numbr%5==0){

			result = (((smFive+smThree)-smFift)-numbr);

		}else if (numbr%3==0) {

			result = (((smFive+smThree)-smFift)-numbr);

		}else {

			result = ((smFive+smThree)-smFift);

		}

	}else {

		result = 0;

	}

	return result;
}