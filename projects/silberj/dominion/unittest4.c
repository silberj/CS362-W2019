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
	int toFlag = 0;
    int kingdoms[10] = {adventurer, council_room, feast, gardens, mine,
						remodel, smithy, village, baron, great_hall};

	struct gameState TestState;

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	

	printf ("TESTING gainCard():\n");
#if (NOISY_TEST == 1)
	printf("-- TEST 1:Test if supply pile is empty (0) or card is not used in game (-1), return -1. --\n");
#endif	
	
	TestState.supplyCount[estate] = 0;	
	
	testValue = gainCard(estate, &TestState, toFlag, currentPlayer);
	
#if (NOISY_TEST == 1)
	printf(" Return value = %d, expected = %d\n", testValue, -1);
#endif
	assertTrue(testValue, -1);

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
		for (card = 0; card < 3; card++)
		{
			TestState.deck[player][card] = estate;
			TestState.deckCount[player]++;		
		}
		for (card = 3; card < totalCards; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}

#if (NOISY_TEST == 1)
	printf("-- TEST 2:Test toFlag = 0 : add to discard. --\n");
#endif	
	
	toFlag = 0;	
	testValue = gainCard(estate, &TestState, toFlag, currentPlayer);

#if (NOISY_TEST == 1)
	printf("Discard Card = %d, result = %d\n", TestState.discard[currentPlayer][TestState.discardCount[currentPlayer] - 1], estate);
	printf("Initial discard count = %d, expected result = %d, result = %d\n",  TestState.discardCount[currentPlayer] - 1, 1, TestState.discardCount[currentPlayer]);
#endif
	assertTrue(TestState.discard[currentPlayer][TestState.discardCount[currentPlayer] - 1], estate);
	assertTrue(TestState.discardCount[currentPlayer], 1);

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	
	
	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;
		for (card = 0; card < 3; card++)
		{
			TestState.deck[player][card] = estate;
			TestState.deckCount[player]++;		
		}
		for (card = 3; card < totalCards; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}
	
#if (NOISY_TEST == 1)
	printf("-- TEST 3:Test toFlag = 1 : add to deck. --\n");
#endif	

	toFlag = 1;	
	testValue = gainCard(estate, &TestState, toFlag, currentPlayer);

#if (NOISY_TEST == 1)
	printf("Deck Card = %d, result = %d\n", TestState.deck[currentPlayer][TestState.deckCount[currentPlayer] - 1], estate);
	printf("Initial deck = %d, expected result = %d, result = %d\n",  TestState.deckCount[currentPlayer] - 1, totalCards + 1, TestState.deckCount[currentPlayer]);
#endif
	assertTrue(TestState.deck[currentPlayer][TestState.deckCount[currentPlayer] - 1], estate);
	assertTrue(totalCards + 1, TestState.deckCount[currentPlayer]);

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	
	
	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;
		for (card = 0; card < 3; card++)
		{
			TestState.deck[player][card] = estate;
			TestState.deckCount[player]++;		
		}
		for (card = 3; card < totalCards; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}

#if (NOISY_TEST == 1)
	printf("-- TEST 4:Test toFlag = 2 : add to hand. --\n");
#endif	
	
	toFlag = 2;
	testValue = gainCard(estate, &TestState, toFlag, currentPlayer);
	
#if (NOISY_TEST == 1)
	printf("Hand Card = %d, result = %d\n", TestState.hand[currentPlayer][TestState.handCount[currentPlayer] - 1], estate);
	printf("Initial handCount = %d, expected result = %d, result = %d\n",  TestState.handCount[currentPlayer] - 1, 1, TestState.handCount[currentPlayer]);
#endif
	assertTrue(TestState.hand[currentPlayer][TestState.handCount[currentPlayer] - 1], estate);
	assertTrue(1, TestState.handCount[currentPlayer]);

    printf("ALL tests on gainCard() complete!\n");	

    return 0;
}
