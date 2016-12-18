#include <stdio.h>
#include <assert.h>
#include "./Score.h"




int CalculScore(int Categorie)
{
	int Score;
	switch(Categorie){	
		case 1 :
		case 2 :
		case 3 :
		case 4 :
		case 5 :
		case 6 :
			Score = (Categorie) * Occurrences[Categorie-1];
			break;			
		case 7:
			if(isBrelan())
				Score = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score = 0;
			break;
			
		case 8:
			if(isCarre())
				Score = De[0]+De[1]+De[2]+De[3]+De[4];
			else
				Score = 0;
			break;
			
		case 9:
			if(isFull())
				Score = 25;
			else
				Score = 0;
			break;
			
		case 10:
			if(isPtSuite())
				Score= 30;
			else
				Score = 0;
			break;
			
		case 11:
			if(isGdSuite())
				Score = 40;
			else
				Score = 0;
			break;
			
		case 12:
			if(isYahtzee())
			{
				Score = 50;
			}
			else
				Score = 0;
			break;
			
		case 13:
			Score = De[0]+De[1]+De[2]+De[3]+De[4];
			break;
	}
	return Score;
}


int test_CalculScore1()
// yahtzee
{
	De[0] = 1;
	De[1] = 1;
	De[2] = 1;
	De[3] = 1;
	De[4] = 1;
	Occurrences[0] = 5;
	Occurrences[1] = 0;
	Occurrences[2] = 0;
	Occurrences[3] = 0;
	Occurrences[4] = 0;
	Occurrences[5] = 0;
	assert(CalculScore(7) == 5);
	assert(CalculScore(8) == 5);
	assert(CalculScore(9) == 25);
	assert(CalculScore(10) == 0);
	assert(CalculScore(11) == 0);
	assert(CalculScore(12) == 50);
	printf("Premiers tests OK");
	return 1;
}

int test_CalculScore2()
// full
{
	De[0] = 3;
	De[1] = 3;
	De[2] = 3;
	De[3] = 1;
	De[4] = 1;
	Occurrences[0] = 2;
	Occurrences[1] = 0;
	Occurrences[2] = 3;
	Occurrences[3] = 0;
	Occurrences[4] = 0;
	Occurrences[5] = 0;
	assert(CalculScore(7) == 11);
	assert(CalculScore(8) == 0);
	assert(CalculScore(9) == 25);
	assert(CalculScore(10) == 0);
	assert(CalculScore(11) == 0);
	assert(CalculScore(12) == 0);
	printf("\nDeuxièmes tests OK");
	return 1;
}


int test_CalculScore3()
// juste un brelan
{
	De[0] = 3;
	De[1] = 3;
	De[2] = 3;
	De[3] = 2;
	De[4] = 1;
	Occurrences[0] = 1;
	Occurrences[1] = 1;
	Occurrences[2] = 3;
	Occurrences[3] = 0;
	Occurrences[4] = 0;
	Occurrences[5] = 0;
	assert(CalculScore(7) == 12);
	assert(CalculScore(8) == 0);
	assert(CalculScore(9) == 0);
	assert(CalculScore(10) == 0);
	assert(CalculScore(11) == 0);
	assert(CalculScore(12) == 0);
	printf("\ntroisiemes tests OK");
	return 1;
}

int test_CalculScore4()
//carre
{
	De[0] = 3;
	De[1] = 3;
	De[2] = 3;
	De[3] = 3;
	De[4] = 1;
	Occurrences[0] = 1;
	Occurrences[1] = 0;
	Occurrences[2] = 4;
	Occurrences[3] = 0;
	Occurrences[4] = 0;
	Occurrences[5] = 0;
	assert(CalculScore(7) == 13);
	assert(CalculScore(8) == 13);
	assert(CalculScore(9) == 0);
	assert(CalculScore(10) == 0);
	assert(CalculScore(11) == 0);
	assert(CalculScore(12) == 0);
	printf("\nquatriemes tests OK");
	return 1;
}

int test_CalculScore5()
// petite suite
{
	De[0] = 1;
	De[1] = 2;
	De[2] = 3;
	De[3] = 4;
	De[4] = 6;
	Occurrences[0] = 1;
	Occurrences[1] = 1;
	Occurrences[2] = 1;
	Occurrences[3] = 1;
	Occurrences[4] = 0;
	Occurrences[5] = 1;
	assert(CalculScore(7) == 0);
	assert(CalculScore(8) == 0);
	assert(CalculScore(9) == 0);
	assert(CalculScore(10) == 30);
	assert(CalculScore(11) == 0);
	assert(CalculScore(12) == 0);
	printf("\ncinquiemes tests OK");
	return 1;
}

int test_CalculScore6()
// gd suite
{
	De[0] = 1;
	De[1] = 2;
	De[2] = 3;
	De[3] = 4;
	De[4] = 5;
	Occurrences[0] = 1;
	Occurrences[1] = 1;
	Occurrences[2] = 1;
	Occurrences[3] = 1;
	Occurrences[4] = 1;
	Occurrences[5] = 0;
	assert(CalculScore(7) == 0);
	assert(CalculScore(8) == 0);
	assert(CalculScore(9) == 0);
	assert(CalculScore(10) == 30);
	assert(CalculScore(11) == 40);
	assert(CalculScore(12) == 0);
	printf("\nsixiemes tests OK");
	return 1;
}


int main()
{
	test_CalculScore1();
	test_CalculScore2();
	test_CalculScore3();
	test_CalculScore4();
	test_CalculScore5();
	test_CalculScore6();
}



