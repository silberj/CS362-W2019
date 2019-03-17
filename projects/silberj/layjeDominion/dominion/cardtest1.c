/* CS362- Assignment 3 */
/* Name: Jason Silber
 * Date: 2/10/2019
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
// stdin
// stdout
// stderr
// __FILE__ 
// __LINE__

#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurerTest"

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
    int newCards;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numberOfPlayers = 2;
    int currentPlayer = 0;
	struct gameState BaseTest, TestState;
	int kingdoms[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numberOfPlayers, kingdoms, seed, &BaseTest);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// player start deck is 3 estate - 7 copper
	// ----------- TEST 1:  test if deck is empty (branch tests full as well) = deck is shuffled. --------------
	printf("-- TEST 1:  Test if deck is empty (branch tests full as well) = deck is shuffled. --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

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

		for (card = 0; card < totalCards; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}		
	}	
	
	for(player = 0; player < numberOfPlayers; player++)
	{
		for(card = 0; card < totalCards; card++)
		{
			TestState.discard[player][card] = TestState.deck[player][card];
			TestState.deckCount[player]--;
			TestState.discardCount[player]++;
		}
	}
	
	newCards = 2;
	
	cardEffect(adventurer, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("Initial deckCount = %d, deckCount = %d, expected result = %d\n", 0, TestState.deckCount[currentPlayer], totalCards - newCards);
	assertTrue(TestState.deckCount[currentPlayer], totalCards - newCards);
	printf("Initial discardCount = %d, discardCount = %d, expected result = %d\n", totalCards, TestState.discardCount[currentPlayer], 0);
	assertTrue(TestState.discardCount[currentPlayer], 0);

	// ----------- TEST 2: test if cardDrawn == copper (branch tests none) = treasure cards drawn. --------------
	printf("-- TEST 2: Test if cardDrawn == copper  = +2 treasure cards drawn. --\n");
	
	// copy the game state to a test case
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;

		for (card = 0; card < totalCards; card++)
		{
			TestState.deck[player][card] = copper;
			TestState.deckCount[player]++;
		}		
	}

	cardEffect(adventurer, choice1, choice2, choice3, &TestState, handpos, &bonus);

	newCards = 2;
	printf("Initial handCount = %d, handCount = %d, expected result = %d\n", 0, TestState.handCount[currentPlayer], newCards);
	printf("Initial deckCount = %d, deckCount = %d, expected result = %d\n", totalCards, TestState.deckCount[currentPlayer], totalCards - newCards);
	assertTrue(TestState.handCount[currentPlayer], newCards);
	assertTrue(TestState.deckCount[currentPlayer], totalCards - newCards);
	printf("card 1 = %d, expected = %d\n", TestState.hand[currentPlayer][0], copper);
	printf("card 2 = %d, expected = %d\n", TestState.hand[currentPlayer][1], copper);
	assertTrue(TestState.hand[currentPlayer][0], copper);
	assertTrue(TestState.hand[currentPlayer][1], copper);

	// ----------- TEST 3: test if cardDrawn == silver = treasure cards drawn. --------------
	printf("-- TEST 3: Test if cardDrawn == silver = +2 treasure cards drawn. --\n");
	
	// copy the game state to a test case
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;

		for (card = 0; card < totalCards; card++)
		{
			TestState.deck[player][card] = silver;
			TestState.deckCount[player]++;
		}		
	}	
	
	cardEffect(adventurer, choice1, choice2, choice3, &TestState, handpos, &bonus);

	newCards = 2;
	printf("Initial handCount = %d, handCount = %d, expected result = %d\n", 0, TestState.handCount[currentPlayer], newCards);
	printf("Initial deckCount = %d, deckCount = %d, expected result = %d\n", totalCards, TestState.deckCount[currentPlayer], totalCards - newCards);
	assertTrue(TestState.handCount[currentPlayer], newCards);
	assertTrue(TestState.deckCount[currentPlayer], totalCards - newCards);
	printf("card 1 = %d, expected = %d\n", TestState.hand[currentPlayer][0], silver);
	printf("card 2 = %d, expected = %d\n", TestState.hand[currentPlayer][1], silver);
	assertTrue(TestState.hand[currentPlayer][0], silver);
	assertTrue(TestState.hand[currentPlayer][1], silver);

	// ----------- TEST 4: test if cardDrawn == gold = treasure cards drawn. --------------
	printf("-- TEST 4: Test if cardDrawn == gold = +2 treasure cards drawn. --\n");
	
	// copy the game state to a test case
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

	for(player = 0; player < numberOfPlayers; player++)	
	{
		TestState.handCount[player] = 0;
		for(card = 0; card < 5; card++)
			TestState.hand[player][card] = -1;
	}
	
	for (player = 0; player < numberOfPlayers; player++)
	{
		TestState.deckCount[player] = 0;

		for (card = 0; card < totalCards; card++)
		{
			TestState.deck[player][card] = gold;
			TestState.deckCount[player]++;
		}		
	}	
	
	cardEffect(adventurer, choice1, choice2, choice3, &TestState, handpos, &bonus);

	newCards = 2;
	printf("Initial handCount = %d, handCount = %d, expected result = %d\n", 0, TestState.handCount[currentPlayer], newCards);
	printf("Initial deckCount = %d, deckCount = %d, expected result = %d\n", totalCards, TestState.deckCount[currentPlayer], totalCards - newCards);
	assertTrue(TestState.handCount[currentPlayer], newCards);
	assertTrue(TestState.deckCount[currentPlayer], totalCards - newCards);
	printf("card 1 = %d, expected = %d\n", TestState.hand[currentPlayer][0], gold);
	printf("card 2 = %d, expected = %d\n", TestState.hand[currentPlayer][1], gold);
	assertTrue(TestState.hand[currentPlayer][0], gold);
	assertTrue(TestState.hand[currentPlayer][1], gold);

	printf("\n >>>>> SUCCESS: Testing %s complete <<<<<\n\n", TESTCARD);

	return 0;
}
