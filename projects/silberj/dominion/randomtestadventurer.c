/* CS362- Assignment 4 */
/* Name: Jason Silber
 * Date: 2/27/2019
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include<stdlib.h>
#include<time.h>
// bool type
#include <stdbool.h> 

#include <math.h>

#define DEBUG 0
#define NOISY_TEST 1

#define MIN_DECK 10

#define MIN_CARD 0
#define MAX_CARD 27

#define TESTCARD "adventurerTest"

bool randomTest1 = false, randomTest2 = false, randomTest3 = false;
int failedTestCriteria1 = 0, failedTestCriteria2 = 0, failedTestCriteria3 = 0;
int failedTest1 = 0, failedTest2 = 0, failedTest3 = 0;
int successTest1 = 0, successTest2 = 0, successTest3 = 0;

int randomNumber(int min, int max)
{
	int range;
	range = max-min + 1;
	return rand()%range + min;
}

int assertTrue(int a, int b)
{
	if (a == b)
	{
		return 1;
	}
	else
	{
		printf("TEST FAILED: %d != %d\n", a, b);
		fflush(stdout);		
		return 0;
	}
}

void checkAdventurerTest(int testNumber, int currentPlayer, struct gameState *postState) 
{
	int newCards = 2;
	int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0, card, copperCount = 0, silverCount = 0, goldCount = 0, totalCoins = 0, coinPosition = 0, nonCoinCards = 0;
	struct gameState preState;
	memcpy (&preState, postState, sizeof(struct gameState));

	cardEffect(adventurer, choice1, choice2, choice3, postState, handpos, &bonus);

	// ----------- TEST 1:  test if deck is empty (branch tests full as well) = deck is shuffled. --------------	
	
	if(testNumber == 0)
	{
	
		if(preState.deckCount[currentPlayer] == 0)
		{
			if(randomTest1 == false)
			{
				printf("-- TEST 1:  Test if deck is empty (branch tests full as well) = deck is shuffled. --\n");
				randomTest1 = true;
			}
			for (card = 0; card < preState.discardCount[currentPlayer]; card++) // Set to random cards.
			{
				if(preState.discard[currentPlayer][card] == copper)
					copperCount++;
				if(preState.discard[currentPlayer][card] == silver)
					silverCount++;
				if(preState.discard[currentPlayer][card] == gold)
					goldCount++;
			}		
			
			totalCoins = copperCount + silverCount + goldCount;

			if(totalCoins == preState.discardCount[currentPlayer])
			{		
				if(assertTrue(postState->deckCount[currentPlayer], preState.discardCount[currentPlayer] - newCards) == false)
				{
					printf("TEST 1.1 - Initial deckCount = %d, deckCount = %d, expected result = %d\n", 0, postState->deckCount[currentPlayer], preState.discardCount[currentPlayer] - newCards);
					failedTest1++;
				}				
				else
					successTest1++;
				if(assertTrue(postState->discardCount[currentPlayer], 0) == false)
				{
					printf("TEST 1.2 - Initial discardCount = %d, discardCount = %d, expected result = %d\n", preState.discardCount[currentPlayer], postState->discardCount[currentPlayer], 0);	
					failedTest1++;
				}				
				else
					successTest1++;
			}
		}
		else
			failedTestCriteria1++;
	}
	
	// ----------- TEST 2: test if cardDrawn == copper or silver or gold (branch tests none) = treasure cards drawn. --------------
	else if(testNumber == 1)
	{	
		
		if(preState.deckCount[currentPlayer] > 0)
		{
			if(randomTest2 == false)
			{
				printf("-- TEST 2: Test if copperCount >= 2 || silverCount >= 2 || goldCount >= 2 and cardDrawn == coin, then +2 treasure cards drawn. --\n");
				randomTest2 = true;
			}
		
			for (card = 0; card < preState.deckCount[currentPlayer]; card++) // Set to random cards.
			{
				if(preState.deck[currentPlayer][card] == copper)
					copperCount++;
				if(preState.deck[currentPlayer][card] == silver)
					silverCount++;
				if(preState.deck[currentPlayer][card] == gold)
					goldCount++;
			}		
			
			totalCoins = copperCount + silverCount + goldCount;

			for (card = 0; card < preState.deckCount[currentPlayer]; card++) // Set to random cards.
			{
				if(coinPosition == totalCoins)
					nonCoinCards++;

				if(preState.deck[currentPlayer][card] == copper)
					coinPosition++;
				else if(preState.deck[currentPlayer][card] == silver)
					coinPosition++;
				else if(preState.deck[currentPlayer][card] == gold)
					coinPosition++;
				else if(coinPosition > totalCoins - 2 && coinPosition < totalCoins)
					nonCoinCards++;
			}
	
			if(copperCount >= 2 || silverCount >= 2 || goldCount >= 2)
			{
				if(assertTrue(postState->handCount[currentPlayer], preState.handCount[currentPlayer] + newCards) == false)
				{
					printf("TEST 2.1 - Initial handCount = %d, handCount = %d, expected result = %d\n", preState.handCount[currentPlayer], postState->handCount[currentPlayer], preState.handCount[currentPlayer] + newCards);
					failedTest2++;
				}			
				else
					successTest2++;
				if(assertTrue(postState->deckCount[currentPlayer], preState.deckCount[currentPlayer] - newCards - nonCoinCards) == false)
				{
					printf("TEST 2.2 - Initial deckCount = %d, deckCount = %d, expected result = %d\n", preState.deckCount[currentPlayer], postState->deckCount[currentPlayer], preState.deckCount[currentPlayer] - newCards - nonCoinCards);
					failedTest2++;
				}				
				else
					successTest2++;
			}
		}
		else
			failedTestCriteria2++;
	}
	
	// ----------- TEST 3: Test if last 2 treasure cards in deck are last 2 cards drawn in hand. --------------
	else if(testNumber == 2)
	{	
		
		if(preState.deckCount[currentPlayer] > 0)
		{
			if(randomTest3 == false)
			{
				printf("-- TEST 3: Test if last 2 treasure cards in deck are last 2 cards drawn in hand. --\n");
				randomTest3 = true;
			}
		
			for (card = 0; card < preState.deckCount[currentPlayer]; card++)
			{
				if(preState.deck[currentPlayer][card] == copper)
					copperCount++;
				if(preState.deck[currentPlayer][card] == silver)
					silverCount++;
				if(preState.deck[currentPlayer][card] == gold)
					goldCount++;
			}		
			
			totalCoins = copperCount + silverCount + goldCount;
			int coinPositions[totalCoins];
			for (card = 0; card < preState.deckCount[currentPlayer]; card++)
			{
				if(coinPosition == totalCoins)
					nonCoinCards++;

				if(preState.deck[currentPlayer][card] == copper)
				{
					coinPositions[coinPosition] = copper;
					coinPosition++;
				}
				else if(preState.deck[currentPlayer][card] == silver)
				{
					coinPositions[coinPosition] = silver;
					coinPosition++;
				}
				else if(preState.deck[currentPlayer][card] == gold)
				{
					coinPositions[coinPosition] = gold;
					coinPosition++;
				}
				else if(coinPosition > totalCoins - 2 && coinPosition < totalCoins)
				{
					nonCoinCards++;
				}
			}
		
			if(copperCount >= 2 || silverCount >= 2 || goldCount >= 2)
			{			
				if(assertTrue(postState->hand[currentPlayer][postState->handCount[currentPlayer] - 2], coinPositions[totalCoins - 1]) == false)
				{
					printf("TEST 3.1 - card 1 = %d, expected = %d\n", postState->hand[currentPlayer][postState->handCount[currentPlayer] - 2], coinPositions[totalCoins - 1]);
					failedTest3++;
				}				
				else
					successTest3++;

				if(assertTrue(postState->hand[currentPlayer][postState->handCount[currentPlayer] - 1], coinPositions[totalCoins -2]) == false)
				{
					printf("TEST 3.2 - card 2 = %d, expected = %d\n", postState->hand[currentPlayer][postState->handCount[currentPlayer] - 1], coinPositions[totalCoins -2]);
					failedTest3++;
				}				
				else
					successTest3++;
			}
		}
		else
			failedTestCriteria3++;		
	}
}

int main () 
{
	srand(time(NULL));

	int testNumber, totalDeckSize, totalDiscardSize, totalHandSize, testRun, index, player, card, remainingDeckCards;

	struct gameState Testing;

	printf("----------------- RANDOM Testing Card: %s ----------------\n", TESTCARD);

	SelectStream(2);
	PutSeed(3);

	for (testNumber = 0; testNumber < 3; testNumber++)
	{
		for (testRun = 0; testRun < 200; testRun++)
		{
			for (index = 0; index < sizeof(struct gameState); index++) 
				((char*)&Testing)[index] = floor(Random() * 256);
	
			player = floor(Random() * 2);
			Testing.whoseTurn = player;
	
			// Set the deck to a random number of cards.
			totalDeckSize = randomNumber(MIN_DECK, MAX_DECK);
			Testing.deckCount[player] = totalDeckSize;
			if(testNumber == 0)
			{
				for (card = 0; card < totalDeckSize; card++) // Set to random cards.
				{
					Testing.deck[player][card] = randomNumber(4, 6); // Set minimum two treasure cards to prevent infinite looping of function.
				}
			}
			else
			{
				for (card = 0; card < totalDeckSize; card++) // Set to random cards.
				{
					if(card < 2)
						Testing.deck[player][card] = randomNumber(4, 6); // Set minimum two treasure cards to prevent infinite looping of function.
					else
						Testing.deck[player][card] = randomNumber(MIN_CARD, MAX_CARD);
				}
			}
			// Set the discard pile to a random number of cards from the deck.
			totalDiscardSize = randomNumber(0, totalDeckSize);		
			Testing.discardCount[player] = totalDiscardSize;
	
			for (card = 0; card < totalDiscardSize; card++)  // Set to random cards.
			{
				Testing.discard[player][card] = Testing.deck[player][card];
				Testing.deckCount[player]--;
			}
	
			// Set the discard pile to a random number of cards from the deck.
			remainingDeckCards = totalDeckSize - totalDiscardSize;
			totalHandSize = randomNumber(0, remainingDeckCards);		
			Testing.handCount[player] = totalHandSize;	
	
			for (card = 0; card < totalHandSize; card++) // Set to random cards.
			{
				Testing.hand[player][card] = Testing.deck[player][card];
				Testing.deckCount[player]--;
			}		
	
			checkAdventurerTest(testNumber, player, &Testing);
		}
	}

	// ----------- TEST RESULTS: --------------
	printf("----------------- TEST RESULTS: ----------------\n");
	printf("-- TEST 1:  Test if deck is empty (branch tests full as well) = deck is shuffled. --\n");
	printf("TESTS NOT MEETING UNIT TEST 1 CRITERIA: %d --\n", failedTestCriteria1);
	printf("FAILED TESTS: %d --\n", failedTest1);
	printf("SUCCESSFUL TESTS: %d --\n", successTest1);
	printf("-- TEST 2: Test if copperCount >= 2 || silverCount >= 2 || goldCount >= 2 and cardDrawn == coin, then +2 treasure cards drawn. --\n");
	printf("TESTS NOT MEETING UNIT TEST 2 CRITERIA: %d --\n", failedTestCriteria2);
	printf("FAILED TESTS: %d --\n", failedTest2);
	printf("SUCCESSFUL TESTS: %d --\n", successTest2);
	printf("-- TEST 3: Test if last 2 treasure cards in deck are last 2 cards drawn in hand. --\n");
	printf("TESTS NOT MEETING UNIT TEST 3 CRITERIA: %d --\n", failedTestCriteria3);
	printf("FAILED TESTS: %d --\n", failedTest3);
	printf("SUCCESSFUL TESTS: %d --\n", successTest3);
	
	printf("\n >>>>> SUCCESS: Testing %s complete <<<<<\n\n", TESTCARD);	

	return 0;
}
