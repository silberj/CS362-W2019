/* CS362- Assignment 3 */
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
	int handPosition = 0;
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
		TestState.hand[player][0] = copper;
		TestState.handCount[player] = 1;
		for(card = 1; card < 5; card++)
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
		for (card = 3; card < totalCards - 1; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}
	
    printf ("TESTING discardCard():\n");
#if (NOISY_TEST == 1)
	printf("-- TEST 1:  Test if card is not trashed, added to Played pile. --\n");
#endif	

	discardCard(handPosition, currentPlayer, &TestState, 0);
	
#if (NOISY_TEST == 1)
	printf("TestState.playedCardCount = %d, expected = %d\n", TestState.playedCardCount, 1);
#endif
	assertTrue(TestState.playedCardCount, 1);

#if (NOISY_TEST == 1)
	printf("Test if set played card to -1 TestState.hand = %d, expected = %d\n", TestState.hand[currentPlayer][handPosition], -1);
#endif
	assertTrue(TestState.hand[currentPlayer][handPosition], -1);

#if (NOISY_TEST == 1)
	printf("-- TEST 2: Test last card in hand array is played, reduce number of cards in hand. --\n");
#endif	
	
#if (NOISY_TEST == 1)
	printf("Initial handCount = %d, expected result = %d\n", TestState.handCount[currentPlayer] + 1, TestState.handCount[currentPlayer]);
#endif
	assertTrue(TestState.handCount[currentPlayer], 0);

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	

	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.hand[player][0] = copper;
		TestState.handCount[player] = 1;
		for(card = 1; card < 5; card++)
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
		for (card = 3; card < totalCards - 1; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}	
	
	handPosition = 1;
	
#if (NOISY_TEST == 1)
	printf("-- TEST 3: Test only one card in hand, reduce number of cards in hand. --\n");
#endif	
	
#if (NOISY_TEST == 1)
	printf("Initial handCount = %d, expected result = %d\n", TestState.handCount[currentPlayer] + 1, 1);
#endif
	assertTrue(TestState.handCount[currentPlayer], 1); // check if the number of coins is correct

	memset(&TestState, 23, sizeof(struct gameState));   // clear the game state
	initializeGame(numberOfPlayers, kingdoms, seed, &TestState); // initialize a new game	

	for(player = 0; player < numberOfPlayers; player++)	
	{
		for(card = 0; card < 3; card++)	
			TestState.hand[player][card] = copper;
			
		TestState.handCount[player] = 3;
		
		for(card = 3; card < 5; card++)
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
		for (card = 3; card < totalCards - 3; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}
	}	

	handPosition = 1;

	discardCard(handPosition, currentPlayer, &TestState, 0);

#if (NOISY_TEST == 1)
	printf("-- TEST 4: Test if not last card in hand array is played and not only one card in hand. --\n");
#endif	
	
#if (NOISY_TEST == 1)
	printf("Test if replace handPosition card with last card in hand TestState.hand = %d, expected result = %d\n", TestState.hand[currentPlayer][handPosition], copper);
#endif
	assertTrue(TestState.hand[currentPlayer][handPosition], copper);

#if (NOISY_TEST == 1)	
	printf("Test last card in hand array is played. Initial last card in hand = %d, expected result= %d\n", TestState.hand[currentPlayer][TestState.handCount[currentPlayer]], -1);
#endif
	assertTrue(TestState.hand[currentPlayer][TestState.handCount[currentPlayer]], -1);

#if (NOISY_TEST == 1)	
	printf("Test reduce number of cards in hand Initial handCount = %d, expected = %d\n", TestState.handCount[currentPlayer], 2);
#endif
	assertTrue(TestState.handCount[currentPlayer], 2);

    printf("ALL tests on discardCard() complete!\n");	

    return 0;
}
