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

#define TESTCARD "council_roomTest"

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
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numberOfPlayers = 2;
    int currentPlayer = 0;
    int otherPlayer = 1;
	struct gameState BaseTest, TestState;
	int kingdoms[10] = {adventurer, embargo, village, minion, mine, cutpurse,
						sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numberOfPlayers, kingdoms, seed, &BaseTest);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: Test that the hand has increased by 4 cards. --------------
	printf("-- TEST 1: test that the hand has increased by 4 minus 1 for a discard. --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));
	
	int player;
	int card;
	int totalCards = 10;
	int drawnCards = 4;

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
	
	cardEffect(council_room, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("Initial handCount = %d, handCount = %d, expected = %d\n", 1 , TestState.handCount[currentPlayer], drawnCards);
	assertTrue(TestState.handCount[currentPlayer], drawnCards);
	printf("Initial deckCount = %d, deckCount = %d, expected = %d\n", totalCards - 1, TestState.deckCount[currentPlayer], totalCards - 1 - drawnCards);
	assertTrue(TestState.deckCount[currentPlayer], totalCards - 1 - drawnCards);
	
	// ----------- TEST 2: Test that the hand has increased by 1 buys. --------------
	printf("-- TEST 2: Test that the hand has increased by 1 buys. --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));
	
	int newNumberOfBuys = 1;
	
	cardEffect(council_room, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("Initial numBuys = %d, expected = %d, received = %d\n", BaseTest.numBuys, BaseTest.numBuys + newNumberOfBuys, TestState.numBuys);
	assertTrue(BaseTest.numBuys + newNumberOfBuys, TestState.numBuys);

	// ----------- TEST 3: Test that the other player hand has increased by 1 card. --------------
	printf("-- TEST 3: Test that the other player hand has increased by 1 card. --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

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
	
	drawnCards = 1;
	
	cardEffect(council_room, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("Initial handCount = %d, handCount = %d, expected = %d\n", 1 , TestState.handCount[otherPlayer], drawnCards + 1);
	assertTrue(TestState.handCount[otherPlayer], drawnCards + 1);
	printf("Initial deckCount = %d, deckCount = %d, expected = %d\n", totalCards - 1, TestState.deckCount[otherPlayer], totalCards - 1 - drawnCards);
	assertTrue(TestState.deckCount[otherPlayer], totalCards - 1 - drawnCards);
	
	
	// ----------- TEST 4: Test that the input handPos card is discarded. --------------
	printf("-- TEST 4: Test that input handPos card is discarded and replaced with card from back (treasure card). --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

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
	
	drawnCards = 4;	
	
	cardEffect(council_room, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("Initial handCount = %d, handCount = %d, expected = %d\n", 1 , TestState.handCount[currentPlayer], drawnCards);
	assertTrue(TestState.handCount[currentPlayer], drawnCards);
	printf("TestState.hand = %d, expected = %d\n", TestState.hand[currentPlayer][handpos], copper);
	assertTrue(TestState.hand[currentPlayer][handpos], copper);

	// ----------- TEST 5: Test that the input handPos card is not trashed. --------------
	printf("-- TEST 5: Test that the input handPos card is not trashed. --\n");

	// copy the game state to a test case		
	memcpy(&TestState, &BaseTest, sizeof(struct gameState));

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
	
	cardEffect(council_room, choice1, choice2, choice3, &TestState, handpos, &bonus);
		
	printf("TestState.handplayedCardCount = %d, expected = %d\n", TestState.playedCardCount, 1);
	assertTrue(TestState.playedCardCount, 1);
	
	
	printf("\n >>>>> SUCCESS: Testing %s complete <<<<<\n\n", TESTCARD);

	return 0;
}
