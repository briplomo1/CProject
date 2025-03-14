#include "functions.h"

#include <stdio.h>
#include <stdlib.h>

int getRandomNumber(const int min, const int max) {
    return (rand() % (max - min + 1)) + min;
}

enum CHAMPION createChampion() {
	return getRandomNumber(0, 2);
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

	printf("Player points at the start of the round -- p1 = %d        p2 = %d", *p1_total, *p2_total);
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
	const int winner = (pt_diff != 0) + (pt_diff < 0) + 1;
	/* Used to calculate all possible turnouts.
	Will be 0 if tied, 1: Mage v Mage, 3: Fighter v Fighter, 7: Tank v Tank
	2: Mage v Fighter, 4: Mage v Tank, and 5: Fighter v Tank. Values are positive is p2 wins,
	negative if p1 wins.
	*/
	const int result = round_sum * winner;

	switch (result) {

		case 0:
			break;
		case 1:
			*p2_total = *p2_total + c2_points;
			break;
		case -1:
			*p1_total = *p1_total + c1_points;
			break;
		case 3:
			// Same as case -3
		case -3:
			*p1_total = *p1_total + c1_points;
			*p2_total = *p2_total + c2_points;
			break;
		case 7:
			// Nothing happens same as case -7
		case -7:
			break;
		case 2:
			*p2_total = (*p2_total + c2_points*(c2 == MAGE)) * (c2 == MAGE);
			break;
		case -2:
			*p1_total = (*p1_total + c1_points*(c1 == MAGE)) * (c1 == MAGE);
			break;
		case 4:
			// Same as -4
		case -4:
			*p1_total = (c1 == MAGE) * (*p1_total + c1_points);
			*p2_total = (c2 == MAGE) * (*p2_total + c2_points);
			break;
		case 5:
			// Same as -5
		case -5:
			*p1_total = (c1 == FIGHTER) * (*p1_total + c1_points) + (c1 != FIGHTER) * *p1_total;
			*p2_total = (c2 == FIGHTER) * (*p2_total + c2_points) + (c1 != FIGHTER) * *p1_total;
		default:
			printf("Unknown Result!");

	}

}