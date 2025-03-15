#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int getRandomNumber(const int min, const int max) {
    return (rand() % (max - min + 1)) + min;
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

void printChampion(enum CHAMPION champion) {

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

void playRound(int *p1_total, int *p2_total, enum CHAMPION c1, int c1_points, enum CHAMPION c2, int c2_points) {
	char message[30];

	printf("Player points at the start of the round -- p1 = %d        p2 = %d\n", *p1_total, *p2_total);
	printf("P1 : ");
	printChampion(c1);
	printf("-%d    vs    P2 : ", c1_points);
	printChampion(c2);
	printf("-%d\n", c2_points);

	// Difference in player champion points. Will be negative if player 1 has greater pts.
	const int pt_diff = c2_points - c1_points;
	// sum of points + 1 to not get zero
	const int round_sum = c1 + c2 + 1;
	// -1 if p1 wins, 1 if p2 wins, 0 if tie
	const int winner = (pt_diff != 0) + (pt_diff < 0) * -2;
	/* Used to calculate all possible turnouts.
	Will be 0 if tied, 1: Mage v Mage, 3: Fighter v Fighter, 7: Tank v Tank
	2: Mage v Fighter, 4: Mage v Tank, and 5: Fighter v Tank. Values are positive is p2 wins,
	negative if p1 wins.
	*/
	const int result = round_sum * winner;
	printf("Result: %d\n", result);

	switch (result) {

		case 0:
			break;
		case 1:
			*p2_total = *p2_total + c2_points;
			*p1_total = *p1_total - c1_points;
			printf("Player1 (MAGE) loses their current points.\nPlayer 2 (MAGE) wins their current points.\n");
			break;
		case -1:
			*p1_total = *p1_total + c1_points;
			*p2_total = *p2_total - c2_points;
			printf("Player 1 (MAGE) wins their current points.\nPlayer2 (MAGE) loses their current points.\n");
			break;
		case 3:
			// same as -3
		case -3:
			*p1_total = *p1_total + c1_points;
			*p2_total = *p2_total + c2_points;
		printf("Both players gain their current points.\n");
			break;
		case 7:
			// Nothing happens same as case -7
		case -7:
			printf("Nothing happens. No penalty or reward.\n");
			break;
		case 2:

			*p2_total = (*p2_total + c2_points*(c2 == MAGE)) * (c2 == MAGE);
			(c2 == MAGE && printf("Player 1 (FIGHTER) loses but with no penalty.\nPlayer2 (MAGE) wins their current points.\n") ||
				printf("Player 1 (MAGE) loses their current points.\nPlayer2 (FIGHTER) wins but gets no points.\n"));
			break;
		case -2:
			*p1_total = *p1_total + c1_points * (c1 == MAGE);
			*p2_total = *p2_total + c2_points * -1 * (c2 == MAGE);
			(c1 == MAGE && printf("Player 1 (MAGE) wins their current points.\nPlayer2 (FIGHTER) but with no penalty.\n") ||
				"Player 1 (FIGHTER) wins but gets no points.\nPlayer2 (MAGE) loses their current points.\n");
			break;
		case 4:
			// Same as -4
		case -4:
		// TODO
			*p1_total = (c1 == MAGE) * (*p1_total + c1_points);
			*p2_total = (c2 == MAGE) * (*p2_total + c2_points);
			break;
		case 5:
			// Same as -5
		case -5:
		// TODO
			*p1_total = (c1 == FIGHTER) * (*p1_total + c1_points) + (c1 != FIGHTER) * *p1_total;
			*p2_total = (c2 == FIGHTER) * (*p2_total + c2_points) + (c2 != FIGHTER) * *p2_total;
			break;
		default:
			printf("Unknown Result!");
	}

	printf("Player points at the end of the round -- P1 = %d        p2 = %d\n\n", *p1_total, *p2_total);

}