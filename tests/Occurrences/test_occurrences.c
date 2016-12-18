#include <stdio.h>
#include <assert.h>

int De[5];
int Occurrences[6];

void CalculOccurrences()
{
	int i;
	for( i = 0; i < 6 ; i++)
		Occurrences[i] = 0;

	for( i = 0; i < 5 ; i++)
	{
		Occurrences[De[i]-1]++;
	}
}

int test_occurrences1()
{
	De[0] = 1;
	De[1] = 1;
	De[2] = 1;
	De[3] = 1;
	De[4] = 1;
	CalculOccurrences();
	assert(Occurrences[0] == 5);
	assert(Occurrences[1] == 0);
	assert(Occurrences[2] == 0);
	assert(Occurrences[3] == 0);
	assert(Occurrences[4] == 0);
	assert(Occurrences[5] == 0);
	printf("\nTest 1 OK");
}

int test_occurrences2()
{
	De[0] = 2;
	De[1] = 2;
	De[2] = 2;
	De[3] = 1;
	De[4] = 1;
	CalculOccurrences();
	assert(Occurrences[0] == 2);
	assert(Occurrences[1] == 3);
	assert(Occurrences[2] == 0);
	assert(Occurrences[3] == 0);
	assert(Occurrences[4] == 0);
	assert(Occurrences[5] == 0);
	printf("\nTest 2 OK");
}

int test_occurrences3()
{
	De[0] = 3;
	De[1] = 1;
	De[2] = 3;
	De[3] = 1;
	De[4] = 3;
	CalculOccurrences();
	assert(Occurrences[0] == 2);
	assert(Occurrences[1] == 0);
	assert(Occurrences[2] == 3);
	assert(Occurrences[3] == 0);
	assert(Occurrences[4] == 0);
	assert(Occurrences[5] == 0);
	printf("\nTest 3 OK");
}

int test_occurrences4()
{
	De[0] = 5;
	De[1] = 5;
	De[2] = 1;
	De[3] = 1;
	De[4] = 5;
	CalculOccurrences();
	assert(Occurrences[0] == 2);
	assert(Occurrences[1] == 0);
	assert(Occurrences[2] == 0);
	assert(Occurrences[3] == 0);
	assert(Occurrences[4] == 3);
	assert(Occurrences[5] == 0);
	printf("\nTest 4 OK");
}

int test_occurrences5()
{
	De[0] = 3;
	De[1] = 1;
	De[2] = 1;
	De[3] = 3;
	De[4] = 3;
	CalculOccurrences();
	assert(Occurrences[0] == 2);
	assert(Occurrences[1] == 0);
	assert(Occurrences[2] == 3);
	assert(Occurrences[3] == 0);
	assert(Occurrences[4] == 0);
	assert(Occurrences[5] == 0);
	printf("\nTest 5 OK");
}

int main()
{
	test_occurrences1();
	test_occurrences2();
	test_occurrences3();
	test_occurrences4();
	test_occurrences5();
}
