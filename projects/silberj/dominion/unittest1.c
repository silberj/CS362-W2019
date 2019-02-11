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
	int currentPlayer = 0;	
    int kingdoms[10] = {adventurer, council_room, feast, gardens, mine, 
						remodel, smithy, village, baron, great_hall};

	struct gameState TestState;

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	
	
	int player;
	int card;
	int totalCards = 10;
	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;
		
		TestState.deck[player][0] = copper;
		TestState.deckCount[player]++;

		for (card = 1; card < totalCards; card++)
		{
			TestState.deck[player][card] = estate;
			TestState.deckCount[player]++;
		}		
	}
	
    printf ("TESTING fullDeckCount():\n");
#if (NOISY_TEST == 1)
	printf("-- TEST 1:  Test if the deck equals the card, the count is accurate. --\n");
#endif
	
	testValue = fullDeckCount(currentPlayer, copper, &TestState);

#if (NOISY_TEST == 1)
	printf("TestState.deck copper = %d, expected = %d\n", 1, 1);
#endif
	assertTrue(testValue, 1);

	
    TestState.hand[currentPlayer][0] = TestState.deck[currentPlayer][0];//Add card to hand
    TestState.deck[currentPlayer][0] = estate;
	TestState.deckCount[currentPlayer]--;
    TestState.handCount[currentPlayer]++;//Increment hand count

	testValue = fullDeckCount(currentPlayer, copper, &TestState);

#if (NOISY_TEST == 1)
	printf("-- TEST 2:  Test if the hand equals the card, the count is accurate. --\n");
#endif
	
#if (NOISY_TEST == 1)
	printf("TestState.hand copper = %d, expected = %d\n", TestState.handCount[currentPlayer], 1);
#endif
	assertTrue(testValue, 1);

	TestState.deck[currentPlayer][0] = TestState.hand[currentPlayer][0];//Add card to hand
	TestState.hand[currentPlayer][0] = -1;
    TestState.deckCount[currentPlayer]++;
    TestState.handCount[currentPlayer]--;//Increment hand count	

	TestState.discard[currentPlayer][0] = TestState.deck[currentPlayer][0];
    TestState.deck[currentPlayer][0] = estate;	
	TestState.deckCount[currentPlayer]--;
	TestState.discardCount[currentPlayer]++;
	
	testValue = fullDeckCount(currentPlayer, copper, &TestState);
	
#if (NOISY_TEST == 1)
	printf("-- TEST 3:  Test if the discards equals the card, the count is accurate. --\n");
#endif
	
#if (NOISY_TEST == 1)
	printf("TestState.discard copper = %d, expected = %d\n", TestState.discardCount[currentPlayer], 1);
#endif
	assertTrue(testValue, 1);

    printf("ALL tests on fullDeckCount() complete!\n");

    return 0;
}
