#include "functions.h"
#include <stdio.h>

int main(void) {
	int rounds;
	int p1_score = 0;
	int p2_score = 0;
	int i;
	printf("Enter the number of rounds: ");
	scanf("%d", &rounds);

	for (i=0; i < rounds; i++) {
		const enum CHAMPION champ1 = createChampion();
		const enum CHAMPION champ2 = createChampion();
		printf("\nRound %d\n--------\n", i+1);
		playRound(&p1_score, &p2_score, champ1, getChampionPoints(champ1), champ2, getChampionPoints(champ2));
	}

	(p1_score > p2_score && printf("GAME OVER!!\nP1 Won\n") ||
		p1_score < p2_score && printf("GAME OVER!!\nP2 Won\n") ||
		printf("GAME OVER!!\nTIE\n"));

}