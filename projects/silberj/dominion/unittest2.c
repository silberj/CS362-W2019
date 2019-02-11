/* CS261- Assignment 3 */
/* Name: Jason Silber
 * Date: 2/10/2019
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

void assertTrue(int a, int b)
{
	if (a == b)
	{
		printf("TEST SUCCESSFUL: %d == %d\n", a, b);
		fflush(stdout);
	}
	else
	{
		printf("TEST FAILED: %d != %d\n", a, b);
		fflush(stdout);		
	}
}

int main() {
	int testValue;
    int seed = 1000;
    int numberOfPlayers = 2;
    int kingdoms[10] = {adventurer, council_room, feast, gardens, mine,
						remodel, smithy, village, baron, great_hall};

	struct gameState TestState;

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	
	
		
    printf ("TESTING isGameOver():\n");
#if (NOISY_TEST == 1)
	printf("-- TEST 1:  Test if stack of Province cards is empty, the game ends. --\n");
#endif

	TestState.supplyCount[province] = 0;
	
	testValue = isGameOver(&TestState);
	
#if (NOISY_TEST == 1)
	printf("TestState.supplyCount province = %d, expected = %d, received = %d\n", TestState.supplyCount[province], 1, testValue);
#endif
	assertTrue(1, testValue); // test if stack of Province cards is empty, the game ends

    TestState.supplyCount[province] = 8;
	
	TestState.supplyCount[copper] = 0;
	TestState.supplyCount[silver] = 0;
	TestState.supplyCount[gold] = 0;

#if (NOISY_TEST == 1)
	printf("-- TEST 2:  Test if three supply pile are at 0, the game ends. --\n");
#endif	
	
	testValue = isGameOver(&TestState);
#if (NOISY_TEST == 1)
	printf("TestState.supplyCount copper = %d, TestState.supplyCount silver = %d, TestState.supplyCount gold = %d, expected = %d, received = %d\n", TestState.supplyCount[copper], TestState.supplyCount[silver], TestState.supplyCount[gold], 1, testValue);
#endif
	assertTrue(1, testValue);

	//reset number of Treasure cards
	TestState.supplyCount[copper] = 60 - (7 * numberOfPlayers);
	TestState.supplyCount[silver] = 40;
	TestState.supplyCount[gold] = 30;
	
	int index;
	for(index = 0; index < 27; index++)
		TestState.supplyCount[index] = 1;
	TestState.supplyCount[24] = 0;
	TestState.supplyCount[25] = 0;
	TestState.supplyCount[26] = 0;
	
#if (NOISY_TEST == 1)
	printf("-- TEST 3:  Test end supplies empty, the game ends --\n");
#endif		
	
	testValue = isGameOver(&TestState);
#if (NOISY_TEST == 1)
	printf("TestState.supplyCount empty on end supplies, expected = %d, received = %d\n", 0, testValue);
#endif
	assertTrue(1, testValue);
	
	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	
	
#if (NOISY_TEST == 1)
	printf("-- TEST 4:  Test if supply full, the game does not end. --\n");
#endif		
	
	testValue = isGameOver(&TestState);
#if (NOISY_TEST == 1)
	printf("TestState.supplyCount full, expected = %d, received = %d\n", 0, testValue);
#endif
	assertTrue(0, testValue);

    printf("ALL tests on isGameOver() complete!\n");	

    return 0;
}
