#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int getRandomNumber(const int min, const int max) {
	int x;
	// Get an integer that is divisible by range for uniform distribution
	do {
		x = rand();
	} while (x >= RAND_MAX - RAND_MAX % (max-min+1));
    return x % (max-min+1) + min;
}

enum CHAMPION createChampion() {
	int randNum =getRandomNumber(0, 2);
	return randNum + (randNum == 2) *1;

}

int getChampionPoints(const enum CHAMPION champion) {
	switch (champion) {
		case TANK:
			return getRandomNumber(5, 9);
		case FIGHTER:
			return getRandomNumber(3, 7);
		case MAGE:
			return getRandomNumber(1, 8);
		default:
			return 0;
	}
}

void printChampion(const enum CHAMPION champion) {

	switch (champion) {
		case TANK:
			printf("Tank");
			break;
		case FIGHTER:
			printf("Fighter");
			break;
		case MAGE:
			printf("Mage");
			break;
		default:
			printf("Unknown!");
	}
}

void playRound(int *p1_total, int *p2_total, const enum CHAMPION c1, const int c1_points, const enum CHAMPION c2, const int c2_points) {
	printf("Player points at the start of the round -- p1 = %d        p2 = %d\n", *p1_total, *p2_total);
	printf("P1 : ");
	printChampion(c1);
	printf("-%d    vs    P2 : ", c1_points);
	printChampion(c2);
	printf("-%d\n", c2_points);

	// Difference in player champion points. Will be negative if player 1 has greater pts; 0 if tied.
	const int pt_diff = c2_points - c1_points;
	// sum of character integer values + 1 to avoid zero. Every combination of characters evaluates to a unique integer.
	const int characters_outcome = c1 + c2 + 1;
	// -1 if p1 wins, 1 if p2 wins, 0 if tie
	const int winner = (pt_diff != 0) + (pt_diff < 0) * -2;
	/* Used to calculate all possible outcomes.
	 * 1: Mage v Mage, 3: Fighter v Fighter, 7: Tank v Tank, 2: Mage v Fighter, 4: Mage v Tank, and 5: Fighter v Tank.
	 * Values are positive is p2 wins, negative if p1 wins.
	 * Value will be 8 if tied where a tie affects the match ie in Mage v Mage and Mage v Fighter outcomes.
	*/
	const enum ROUND_OUTCOME outcome = characters_outcome * winner +
		(winner == 0) * (TIE_MvM_OR_MvF * (characters_outcome < 3) + (characters_outcome >= 3) * characters_outcome);

	switch (outcome) {

		case TIE_MvM_OR_MvF:
			printf("Tie. Nothing happens.\n");
			break;
		case P2_WINS_MAGE_V_MAGE:
			*p2_total = *p2_total + c2_points;
			*p1_total = *p1_total - c1_points;
			printf("Player1 (MAGE) loses their current points.\nPlayer 2 (MAGE) wins their current points.\n");
			break;
		case P1_WINS_MAGE_V_MAGE:
			*p1_total = *p1_total + c1_points;
			*p2_total = *p2_total - c2_points;
			printf("Player 1 (MAGE) wins their current points.\nPlayer 2 (MAGE) loses their current points.\n");
			break;
		case P2_WINS_FIGHTER_V_FIGHTER:
			// same as -3
		case P1_WINS_FIGHTER_V_FIGHTER:
			*p1_total = *p1_total + c1_points;
			*p2_total = *p2_total + c2_points;
			printf("Both players gain their current points.\n");
			break;
		case P2_WINS_TANK_V_TANK:
			// Nothing happens same as case -7
		case P1_WINS_TANK_V_TANK:
			printf("Nothing happens. No penalty or reward.\n");
			break;
		case P2_WINS_MAGE_V_FIGHTER:
			*p1_total = *p1_total  + c1_points * -1 * (c1 == MAGE);
			*p2_total = *p2_total + c2_points * (c2 == MAGE);
			(c2 == MAGE && printf("Player 1 (FIGHTER) loses but with no penalty.\nPlayer 2 (MAGE) wins their current points.\n") ||
				printf("Player 1 (MAGE) loses their current points.\nPlayer 2 (FIGHTER) wins but gets no points.\n"));
			break;
		case P1_WINS_MAGE_V_FIGHTER:
			*p1_total = *p1_total + c1_points * (c1 == MAGE);
			*p2_total = *p2_total + c2_points * -1 * (c2 == MAGE);
			(c1 == MAGE && printf("Player 1 (MAGE) wins their current points.\nPlayer 2 (FIGHTER) but with no penalty.\n") ||
				"Player 1 (FIGHTER) wins but gets no points.\nPlayer 2 (MAGE) loses their current points.\n");
			break;
		case P2_WINS_MAGE_V_TANK:
			// Same as -4
		case P1_WINS_MAGE_V_TANK:
			*p1_total = (c1 == MAGE) * *p1_total + (c1 != MAGE) * -1 * c1_points;
			*p2_total = (c2 == MAGE) * *p2_total + (c2 != MAGE) * -1 * c2_points;
			(c1 == MAGE && printf("Player 1 (MAGE) wins and gains current points.\nPlayer 2 (TANK) loses their current points.\n") ||
			printf("Player 1 (TANK) loses their current points.\nPlayer 2 (MAGE) wins and gains current points.\n"));
			break;
		case P2_WINS_FIGHTER_V_TANK:
			// Same outcome regardless who wins -5
		case P1_WINS_FIGHTER_V_TANK:
			*p1_total = (c1 == FIGHTER) * (*p1_total + c1_points) + (c1 != FIGHTER) * *p1_total;
			*p2_total = (c2 == FIGHTER) * (*p2_total + c2_points) + (c2 != FIGHTER) * *p2_total;
			(c1 == FIGHTER && printf("Player 1 (FIGHTER) wins and gains current points.\nPlayer 2 (TANK) loses but with no penalty.\n") ||
				printf("Player 1 (TANK) loses but with no penalty.\nPlayer 2 (FIGHTER) wins and gains current points.\n"));
			break;
		default:
			printf("Unknown Result!");
	}

	printf("Player points at the end of the round -- P1 = %d        P2 = %d\n\n", *p1_total, *p2_total);

}

//